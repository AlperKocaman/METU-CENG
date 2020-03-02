#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "ext2.h"

#define BASE_OFFSET 1024
#define EXT2_BLOCK_SIZE 1024
#define IMAGE "image.img"

typedef unsigned char bmap;
#define __NBITS (8 * (int) sizeof (bmap))
#define __BMELT(d) ((d) / __NBITS)
#define __BMMASK(d) ((bmap) 1 << ((d) % __NBITS))
#define BM_SET(d, set) ((set[__BMELT (d)] |= __BMMASK (d)))
#define BM_CLR(d, set) ((set[__BMELT (d)] &= ~__BMMASK (d)))
#define BM_ISSET(d, set) ((set[__BMELT (d)] & __BMMASK (d)) != 0)

unsigned int block_size = 0;
#define BLOCK_OFFSET(block) (block*block_size)

//###############################GLOBALS#######################################

unsigned int inodeSize = 128 ;

int readSuperBlock(int fd, struct ext2_super_block* super){

	lseek(fd, BASE_OFFSET, SEEK_SET) ;
	read(fd, super, sizeof(*super)) ;

	return super->s_magic == EXT2_SUPER_MAGIC;
}

unsigned int readGroupDesc(int fd, struct ext2_group_desc* group, unsigned int groupNum) {

	unsigned int place = BLOCK_OFFSET(1) + groupNum*sizeof(*group);

	if(block_size == EXT2_BLOCK_SIZE)
		place += EXT2_BLOCK_SIZE ;

	lseek(fd, place, SEEK_SET) ;
	read(fd, group, sizeof(*group)) ;

	return place;
}

void readBitmap(int fd, bmap *bitmap, unsigned int place){

	lseek(fd, place, SEEK_SET);
	read(fd, bitmap, block_size);
}

unsigned int pathOrInode(char *arg){

	return atoi(arg);
}

void readInode(int fd,struct ext2_inode *inode, unsigned int place){

    lseek(fd, place, SEEK_SET);
    read(fd, inode, inodeSize);
}

void readBlock(int fd, void *block, unsigned int blockNum){

	lseek(fd, BLOCK_OFFSET(blockNum), SEEK_SET) ;
	read(fd, block, block_size) ;
}

unsigned int findInBlockEntry(void *block, unsigned char *input){

	unsigned int i = 0 ;
	unsigned int currInode = 2 ;
	unsigned short recLen ;
	unsigned char nameLen ; 
	unsigned char *name = malloc(255*sizeof(unsigned char));

	while(i < block_size){

		recLen  = *(unsigned short*)(block+4) ;
		nameLen = *(unsigned char *)(block+6) ;

		memcpy((void *)name, (block+8), nameLen);
		name[nameLen] = '\0' ;

		if(!strcmp(name, input)){
			currInode = *(unsigned int *)(block) ;
			return currInode ;
		}

		i += recLen ;
		block += recLen ;
	}

	return currInode ;

}

unsigned int findDirEntryInode(int fd, struct ext2_inode *inode, unsigned char *input){

	unsigned int i=0, dataBlock, foundInode = 0 ;
	void *block = malloc(block_size) ;

	while(i < 12){

		dataBlock = inode->i_block[i] ;

		readBlock(fd, block, dataBlock) ;

		foundInode = findInBlockEntry(block, input) ;

		if(foundInode)
			return foundInode ;

		i++;
	}

	return foundInode ;
}

unsigned int convertPathtoInode(int fd, char *arg, unsigned int s_inodes_per_group){

	unsigned int currGroup=0, currInode=2, i=0, j=0, inputLen = 0;

	inputLen = strlen(arg) ;

	char input[inputLen+1];
	unsigned char temp[inputLen] ;
	struct ext2_group_desc group ;
	struct ext2_inode inode;	

	strcpy(input, arg) ;

	while(input[i] != '\0'){

		if(input[i] == '/')
			i++ ;

		if(input[i] == '\0')
			return currInode ;

		for(j=0; (input[i] != '/') && (input[i] != '\0') ; j++){
			temp[j] = input[i++];
		}

		temp[j] = '\0';

		readGroupDesc(fd, &group, currGroup) ;
		readInode(fd, &inode, BLOCK_OFFSET(group.bg_inode_table)+((currInode-1)%s_inodes_per_group)*inodeSize) ;
		
		currInode = findDirEntryInode(fd, &inode, temp) ;
		currGroup = (currInode-1)/s_inodes_per_group ;
	}

	return currInode ;  
}

unsigned int findFirstFreeInode(int fd, unsigned int s_inodes_per_group, unsigned int s_inodes_count){

	struct ext2_group_desc group ;
	unsigned int freeInode = 1, currGroup = 0, upTo = 1;
	bmap inodeBitmap[block_size] ;

	if((s_inodes_count/s_inodes_per_group)>1)
		upTo = s_inodes_count/s_inodes_per_group ;

	while(currGroup<upTo){

		readGroupDesc(fd, &group, currGroup) ;
		readBitmap(fd, inodeBitmap, BLOCK_OFFSET(group.bg_inode_bitmap)) ;

		for( ; freeInode < (currGroup+1)*s_inodes_per_group ; freeInode++){
			if(!BM_ISSET((freeInode%s_inodes_per_group), inodeBitmap))
				return freeInode+1 ;
		}

		currGroup ++ ;
	}

}

unsigned int *findFreeBlocks(int fd, unsigned int s_blocks_count, unsigned int s_blocks_per_group, unsigned int neededBlocks){

	struct ext2_group_desc group ;
	unsigned int freeBlock = 1, currGroup = 0, allocatedBlocks = 0, upTo = 1 ;
	bmap blockBitmap[block_size];
	unsigned int *blocks = malloc(sizeof(unsigned int) * neededBlocks) ;

	if((s_blocks_count/s_blocks_per_group)>=1)
		upTo = s_blocks_count/s_blocks_per_group +1 ;

	while(currGroup<upTo){

		readGroupDesc(fd, &group, currGroup) ;
		readBitmap(fd, blockBitmap, BLOCK_OFFSET(group.bg_block_bitmap)) ;

		for( ; freeBlock < (currGroup+1)*s_blocks_per_group ; freeBlock++){
			if(!BM_ISSET((freeBlock%s_blocks_per_group), blockBitmap)){
				if(allocatedBlocks<neededBlocks){

					blocks[allocatedBlocks] = freeBlock+1 ;
					allocatedBlocks++ ;

				}
				else return blocks ;
			}
		}

		currGroup ++ ;
	}

	return blocks ;
}

unsigned int *correctFreeBlocks(unsigned int *freeBlocks, unsigned int neededBlocks){

	unsigned int i = 0 ;

	for(; i < neededBlocks ; i++)
		freeBlocks[i]-- ;

	return freeBlocks ;
}


unsigned int calcNeededBlocks(unsigned int fileSize){

	if((fileSize/block_size+1)>11)
		return 12 ;

	return (fileSize/block_size)+1 ;
}

unsigned int calcEntrySize(char *arg){

	unsigned int size = 0 , nameSize;

	nameSize = strlen(arg) ;

	if(nameSize%4)
		nameSize += 4-(nameSize%4) ;

	size = 8 + nameSize ;

	return size ;
}

unsigned int fillMetadata(int fd, char *arg, struct ext2_inode *inode, unsigned int place){

	struct stat sb;

	if (stat(arg, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    inode->i_mode   = sb.st_mode   ;
    inode->i_uid    = sb.st_uid    ;
    inode->i_size   = sb.st_size   ;
    inode->i_atime  = sb.st_atime  ;
    inode->i_ctime  = sb.st_ctime  ;
    inode->i_mtime  = sb.st_mtime  ;
    inode->i_blocks = calcNeededBlocks(sb.st_size)*(block_size/512) ;
    inode->i_gid    = sb.st_gid    ;
    inode->i_links_count = 1;

    lseek(fd, place, SEEK_SET) ;
    write(fd, inode, inodeSize) ;

    return sb.st_size ;
}

void setBlocks(int fd, char *arg, unsigned int *freeBlocks, unsigned int neededBlocks){

	int fd2, i=0 ;
	
	fd2 = open(arg, O_RDONLY) ;

	while(i < neededBlocks) {

		void *block = malloc(block_size);

		lseek(fd2, i*block_size, SEEK_SET) ;	
		read(fd2, block, block_size) ;
		
		lseek(fd, BLOCK_OFFSET(freeBlocks[i]), SEEK_SET) ;
		write(fd, block, block_size) ;

		i ++ ;

		block = NULL ;
		free(block);
	}

	close(fd2) ;

	return ;	
}

void setNewInodePointers(int fd, struct ext2_inode *inode, unsigned int place, unsigned int *freeBlocks, unsigned int neededBlocks){

	unsigned int i = 0 ;

	while(i < neededBlocks){

		inode->i_block[i] = freeBlocks[i] ;

		i++ ;
	}

	lseek(fd, place, SEEK_SET) ;
	write(fd, inode, inodeSize) ;
	
	return ;
}

unsigned char indentNameLen(unsigned char nameLen){

	if(nameLen%4)
		nameLen += 4 - (nameLen%4) ;

	return nameLen ;
}

unsigned int *findDirEntryPlace(int fd, unsigned int place, unsigned int entrySize){

	unsigned int i=0, sizeLeft, place2, recLen, entryPlace ; 
	unsigned int *blockNum = malloc(sizeof(unsigned int));
	unsigned int *res = malloc(3*sizeof(unsigned int)) ;
	void *block = malloc(block_size) ;
	unsigned char nameLen ;	

	while(i < 12){

		place2 = place + i*4 ;

		lseek(fd, place2 ,SEEK_SET) ;
		read(fd, blockNum, sizeof(unsigned int));

		readBlock(fd, block, *blockNum);

		entryPlace = (*blockNum)*block_size ;

		sizeLeft = block_size ;

		while(sizeLeft>0){

			recLen  = *(unsigned short*)(block+4) ;	

			if(sizeLeft == recLen){

				if(sizeLeft > entrySize){

					nameLen = *(unsigned char *)(block+6) ;
					nameLen = indentNameLen(nameLen) ;

					sizeLeft -= (8+(unsigned int)nameLen) ;
					entryPlace += 8+nameLen ;

					res[0] = entryPlace ;
					res[1] = sizeLeft ;
					res[2] = 8+nameLen ;

					return res ;
				}

			}

			sizeLeft -= recLen ;
			block += recLen ;
			entryPlace += recLen ;		
		}

		i++ ;
	}

}

void setDirEntry(int fd, char *arg, unsigned int freeInode, unsigned int *dirEntryPlace ){

	struct ext2_dir_entry entry ;

	void *ptr = &dirEntryPlace[2] ;

	char *ptr2 = malloc(block_size); 

	lseek(fd, dirEntryPlace[0]-dirEntryPlace[2]+4,SEEK_SET );
	write(fd, ptr, 2) ;

	entry.inode = freeInode ;
	entry.rec_len = dirEntryPlace[1] ; 
	entry.name_len = strlen(arg);
	entry.file_type = 1 ;

	lseek(fd, dirEntryPlace[0], SEEK_SET) ;
	write(fd, &entry, 8) ;

	write(fd, arg, strlen(arg) ) ;

	return ;
}

void setInodeStats(int fd, struct ext2_super_block *super, struct ext2_group_desc *group, unsigned int groupPlace, unsigned int index2){

	bmap inodeBitmap[block_size] ;

	super->s_free_inodes_count -- ;
	lseek(fd, BASE_OFFSET, SEEK_SET) ;
	write(fd, super, EXT2_BLOCK_SIZE) ;

	group->bg_free_inodes_count --;
	lseek(fd, groupPlace, SEEK_SET) ;
	write(fd, group, sizeof(*group)) ;

	readBitmap(fd, inodeBitmap, BLOCK_OFFSET(group->bg_inode_bitmap)) ;
	BM_SET(index2, inodeBitmap) ;
	lseek(fd, BLOCK_OFFSET(group->bg_inode_bitmap), SEEK_SET) ;
	write(fd, inodeBitmap, block_size) ;

}

void setDataStats(int fd, struct ext2_super_block *super, unsigned int neededBlocks, unsigned int *freeBlocks){

	struct ext2_group_desc group;
	unsigned int place, currGroup, groupPlace, i = 0, freeBlock;
	bmap blockBitmap[block_size] ; 

	super->s_free_blocks_count -= neededBlocks ; /* Free blocks count */
	lseek(fd, BASE_OFFSET, SEEK_SET) ;
	write(fd, super, EXT2_BLOCK_SIZE) ;

	while(i<neededBlocks){

		currGroup = (freeBlocks[i]-1)/super->s_blocks_per_group ;
		groupPlace = readGroupDesc(fd, &group, currGroup) ;

		group.bg_free_blocks_count --;
		lseek(fd, groupPlace, SEEK_SET) ;
		write(fd, &group, sizeof(struct ext2_group_desc)) ;

		readBitmap(fd, blockBitmap, BLOCK_OFFSET(group.bg_block_bitmap)) ;
		freeBlock = ((freeBlocks[i]-1) % super->s_blocks_per_group) ;
		BM_SET(freeBlock, blockBitmap) ;

		lseek(fd, BLOCK_OFFSET(group.bg_block_bitmap), SEEK_SET) ;
		write(fd, blockBitmap, block_size) ;

		i++ ;
	}

    return ;
}

int main(int argc, char *argv[])
{
    struct ext2_super_block super;
    struct ext2_group_desc group, group2, group3;
    struct ext2_inode inode, inode2, inode3;

    unsigned int inodeNum, groupNum, groupNum2, group2Place, index, index2, containingBlock, i=0, freeInode, fileSize, entrySize ;  
    unsigned int fd, neededBlocks, *freeBlocks, *dirEntryPlace ; 

    // Open Ext2 image file
	if ((fd = open(argv[1], O_RDWR)) < 0) { 
        perror(IMAGE); // error on opening image file
        exit(1);
    }

    // Read super block
    if(readSuperBlock(fd, &super) == 0) 
    	exit(1) ; //not an ext2 file system

    block_size = 1024 << super.s_log_block_size; // block size taken from super block
    inodeSize  = super.s_inode_size ;

    if(!pathOrInode(argv[3]))
    	inodeNum = convertPathtoInode(fd, argv[3], super.s_inodes_per_group); //fill this func

    else 
    	inodeNum = pathOrInode(argv[3]);

    groupNum = (inodeNum-1) / super.s_inodes_per_group ; // which group inode resides is decided
    readGroupDesc(fd, &group, groupNum) ;
    index = (inodeNum-1) % super.s_inodes_per_group ;

    readInode(fd, &inode, BLOCK_OFFSET(group.bg_inode_table)+index*inodeSize) ;

  	freeInode = findFirstFreeInode(fd, super.s_inodes_per_group, super.s_inodes_count) ;

  	groupNum2 = (freeInode-1) / super.s_inodes_per_group ;
  	group2Place = readGroupDesc(fd, &group2, groupNum2) ;
  	index2 = (freeInode-1) % super.s_inodes_per_group ;

  	readInode(fd, &inode2, BLOCK_OFFSET(group2.bg_inode_table)+index2*inodeSize) ;

  	setInodeStats(fd, &super, &group2, group2Place, index2) ;

	fileSize = fillMetadata(fd, argv[2], &inode2, BLOCK_OFFSET(group2.bg_inode_table)+index2*inodeSize) ;

    neededBlocks = calcNeededBlocks(fileSize) ;

    freeBlocks = findFreeBlocks(fd, super.s_blocks_count, super.s_blocks_per_group, neededBlocks) ; //blocksize 2048 icin 1 fazla donuyor!!!!

    if(block_size != EXT2_BLOCK_SIZE){

    	for(i=0; i< neededBlocks ; i++)
    		freeBlocks[i] -- ;
    }
    	
	setBlocks(fd, argv[2], freeBlocks, neededBlocks) ;
	
	setNewInodePointers(fd, &inode2, BLOCK_OFFSET(group2.bg_inode_table)+index2*inodeSize, freeBlocks, neededBlocks) ;

	entrySize = calcEntrySize(argv[2]) ;

	dirEntryPlace = findDirEntryPlace(fd, BLOCK_OFFSET(group.bg_inode_table)+index*inodeSize+40, entrySize) ; 

	setDirEntry(fd, argv[2], freeInode, dirEntryPlace ) ;

	if(block_size != EXT2_BLOCK_SIZE){

    	for(i=0; i< neededBlocks ; i++)
    		freeBlocks[i] ++ ;
    }

	setDataStats(fd, &super, neededBlocks, freeBlocks) ;

	if(block_size != EXT2_BLOCK_SIZE){

    	for(i=0; i< neededBlocks ; i++)
    		freeBlocks[i] -- ;
    }

	printf("%d ", freeInode);

	for(i=0; i < neededBlocks; i++){
		printf("%d",freeBlocks[i] );
		if(i!=neededBlocks-1 )
			printf(",");
	}
	
    close(fd) ;

    return 0;
}

