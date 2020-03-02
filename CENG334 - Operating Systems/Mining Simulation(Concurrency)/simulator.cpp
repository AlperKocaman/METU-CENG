#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>
#include "writeOutput.h"
#include <errno.h>


typedef unsigned int u_int ;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

sem_t *miner_full;
sem_t *miner_empty; 
sem_t miners_total ;
sem_t smutex ;
sem_t *sem_smelters ;
sem_t *smelter_two_ores ;
sem_t mutex_smelter ;
sem_t total_copper ;
sem_t total_iron ;
sem_t total_coal ;
sem_t *sem_foundries ;
sem_t *one_iron_coal ;
sem_t mutex_foundry ;

u_int i, miner_num=0, transporter_num=0, smelter_num=0, foundry_num=0 ;
u_int interval , capacity , total ;
u_int active_miners = 0;
u_int has_ore = 0 ;
u_int order = 0, order2 = 0, order3 = 0 ;
u_int waiting_one_smelter = 0, waiting_one_foundry = 0 ; 
u_int t_iron_smelters   = 0 ;
u_int t_iron_foundries   = 0 ;
u_int iron_lock = 0 , coal_lock = 0;

OreType oretype ;

//------ Miners ----------------//
typedef struct Miners {
    unsigned int ID;
    OreType oreType;
    unsigned int capacity;
    unsigned int current_count;
    unsigned int interval ;
    unsigned int total ;
} Miners;

Miners *miners ;
//-------------------------------//

//------ Transporters ----------------//
typedef struct Transporters {
    unsigned int ID;
    OreType *carry;
    unsigned int interval;
} Transporters;

Transporters *transporters ;
//-------------------------------//

//------ Smelters ----------------//
typedef struct Smelters {
    unsigned int ID;
    OreType oreType;
    unsigned int loading_capacity;
    unsigned int waiting_ore_count;
    unsigned int total_produce;
    unsigned int interval ;
    unsigned int finish_flag ;
    unsigned int smelter_lock ;
} Smelters;

Smelters *smelters ;
//-------------------------------//

//------ Foundries ----------------//
typedef struct Foundries {
    unsigned int ID;
    unsigned int loading_capacity;
    unsigned int waiting_iron;
    unsigned int waiting_coal;
    unsigned int total_produce;
    unsigned int interval ;
    unsigned int finish_flag ;
    unsigned int iron_lock ;
    unsigned int coal_lock ;

} Foundries;

Foundries *foundries ;
//-------------------------------//


//-------------------------TRANSPORTER MINER ROUTİNE -----------------------------------------------------------------------

void transporter_miner_routine( int related_miner , int related_transporter ){

	MinerInfo *miner = new MinerInfo ;
	TransporterInfo *transporter = new TransporterInfo ; 

	u_int interval = transporters[related_transporter].interval ;

	FillMinerInfo(miner, miners[related_miner].ID, (OreType)0, 0, 0) ;

	FillTransporterInfo(transporter, transporters[related_transporter].ID , NULL) ;
 
	WriteOutput(miner, transporter, NULL, NULL,TRANSPORTER_TRAVEL) ;

	usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for travel

	miners[related_miner].current_count -- ;

	transporters[related_transporter].carry = &(miners[related_miner].oreType) ;

	FillMinerInfo(miner, miners[related_miner].ID, miners[related_miner].oreType, miners[related_miner].capacity, miners[related_miner].current_count) ;

	FillTransporterInfo(transporter, transporters[related_transporter].ID , transporters[related_transporter].carry) ;

	WriteOutput(miner, transporter, NULL, NULL,TRANSPORTER_TAKE_ORE) ;

	usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for loading

	pthread_mutex_unlock( &mutex );

	sem_post(&smutex) ;

	sem_post(&miner_full[related_miner]) ;

	delete miner ;
	delete transporter ;

	return ;
}

//-------------------------TRANSPORTER SMELTER ROUTİNE -----------------------------------------------------------------------

void transporter_smelter_routine( int related_smelter , int related_transporter ) {

	SmelterInfo *smelter = new SmelterInfo ;
	TransporterInfo *transporter = new TransporterInfo ; 

	u_int interval = transporters[related_transporter].interval ;

	FillSmelterInfo(smelter, smelters[related_smelter].ID, (OreType)0, 0, 0, 0 ) ;

	FillTransporterInfo( transporter , transporters[related_transporter].ID , transporters[related_transporter].carry ) ;
	
	WriteOutput(NULL, transporter, smelter, NULL, TRANSPORTER_TRAVEL) ;

	usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for travel

	smelters[related_smelter].waiting_ore_count += 1 ;
	smelters[related_smelter].smelter_lock += 1 ;


	FillSmelterInfo(smelter, smelters[related_smelter].ID, smelters[related_smelter].oreType,
	 smelters[related_smelter].loading_capacity, smelters[related_smelter].waiting_ore_count, smelters[related_smelter].total_produce) ;
	
	FillTransporterInfo( transporter , transporters[related_transporter].ID , transporters[related_transporter].carry ) ;

	WriteOutput(NULL, transporter, smelter, NULL, TRANSPORTER_DROP_ORE) ;

	if( smelters[related_smelter].smelter_lock == 2 ) {

		sem_post(&sem_smelters[related_smelter]) ;
		sem_post(&smelter_two_ores[related_smelter]) ;

		smelters[related_smelter].smelter_lock -=2 ;
	}

	sem_post(&smutex) ;

	usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for unloading

	//Unloaded(Smelter ) ;



	//------------------------------------------------------------------------------------------

	return  ;
}

/*

Unloaded(Smelter )
Unloaded: Signals the smelters to inform that an ore has been unloaded to its storage.

*/

//-------------------------TRANSPORTER FOUNDRY ROUTİNE -----------------------------------------------------------------------

void transporter_foundry_routine( int related_foundry , int related_transporter ) {

	FoundryInfo *foundry = new FoundryInfo ;
	TransporterInfo *transporter = new TransporterInfo ;

	u_int interval = transporters[related_transporter].interval ;

	FillFoundryInfo(foundry, foundries[related_foundry].ID, 0, 0, 0, 0 ) ;

	FillTransporterInfo( transporter , transporters[related_transporter].ID , transporters[related_transporter].carry ) ;

	WriteOutput(NULL, transporter, NULL, foundry, TRANSPORTER_TRAVEL) ;

	usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for travel

	if( *(transporters[related_transporter].carry) == 0 ){
		foundries[related_foundry].waiting_iron ++ ;
		foundries[related_foundry].iron_lock ++ ;
	}

	else{
		foundries[related_foundry].waiting_coal ++ ;
		foundries[related_foundry].coal_lock ++ ;
	}

	FillFoundryInfo(foundry, foundries[related_foundry].ID, foundries[related_foundry].loading_capacity,
	 foundries[related_foundry].waiting_iron, foundries[related_foundry].waiting_coal, foundries[related_foundry].total_produce ) ; 

	FillTransporterInfo( transporter , transporters[related_transporter].ID , transporters[related_transporter].carry ) ;

	WriteOutput(NULL, transporter, NULL, foundry, TRANSPORTER_DROP_ORE) ;

	if( (foundries[related_foundry].iron_lock > 0) && (foundries[related_foundry].coal_lock > 0) ){

		foundries[related_foundry].iron_lock -- ;
		foundries[related_foundry].coal_lock -- ;

		sem_post(&sem_foundries[related_foundry]) ;
		sem_post(&one_iron_coal[related_foundry]) ;
	} 

	sem_post(&smutex) ;

	usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for unloading

	//Unloaded(Foundry) ;


	return ;

}

/*

Unloaded(Foundry)
Unloaded: Signals the foundry to inform that an ore has been unloaded to its storage.

*/

//----------------------------MINER ROUTİNE ----------------------------------------------------------------

void *miner_routine( void *ptr ) {

	u_int i = *((unsigned int *)ptr) ;

	u_int j = 0 ;

	u_int interval = miners[i].interval ;

	MinerInfo *miner = new MinerInfo ;

	FillMinerInfo(miner, miners[i].ID, miners[i].oreType, miners[i].capacity, miners[i].current_count ) ;

	WriteOutput(miner, NULL, NULL, NULL, MINER_CREATED) ;

	while( miners[i].total ) {

		//waitCanProduce() -> 1- if storage full , wait transporter / 2- reserve a storage to next ore??

		if(miners[i].current_count == miners[i].capacity){

			sem_wait(&miner_full[i]);
		}

		//--------------------------------------------------------------------------

		//pthread_mutex_lock( &miner_process );

		FillMinerInfo(miner, miner->ID, miner->oreType, miner->capacity, miners[i].current_count ) ;

		WriteOutput(miner, NULL, NULL, NULL, MINER_STARTED) ;

		usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; //for production

		miners[i].current_count += 1 ;

		miners[i].total -= 1 ;

		//minerProduced() -> informs available transporters that there is a newly created ore

		sem_wait(&miner_full[i])  ;

		sem_post(&miner_empty[i]) ; //maybe needless

		sem_post(&miners_total) ; 

		//-----------------------------------------------------------------------------------

		FillMinerInfo(miner, miner->ID, miner->oreType, miner->capacity, miners[i].current_count ) ;						 

		WriteOutput(miner, NULL, NULL, NULL, MINER_FINISHED) ;

		usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for next round		
	}

	// minerStopped() -> signal that this miner has stopped ->if ore exists in storage transporters can take -> if last miner terminate

	active_miners -- ;

	while(miners[i].current_count != 0){

		sem_post( &miner_empty[i] );
	}

	has_ore -- ;

	//------------------------------------------------------------------------------------------

	FillMinerInfo(miner, miner->ID, miner->oreType, miner->capacity, miners[i].current_count ) ;

	WriteOutput(miner, NULL, NULL, NULL, MINER_STOPPED) ;


	if(active_miners == 0){
		
		for(j = 0 ; j < transporter_num ; j++){
			sem_post(&miners_total) ;
			sem_post(&smutex) ;
		}
	}

	if(active_miners == 0)
		pthread_mutex_unlock( &mutex );

	return 0 ;
}

//--------------------------TRANSPORTER MAİN ROUTİNE-----------------------------------------------------------------------

void *transporter_routine( void *ptr) {

	u_int i = *((unsigned int *)ptr) ;

	u_int j = 0 , flag = 0, flag2 = 0;

	TransporterInfo *transporter = new TransporterInfo ;

	FillTransporterInfo( transporter , transporters[i].ID , NULL ) ;

	WriteOutput(NULL, transporter , NULL, NULL,TRANSPORTER_CREATED) ; 

	while( true ) {

		transporter->carry = NULL ;

		flag = j = 0 ;
		
	// waitNextLoad() -> waits next miner , if none has miner wait , else search in order	

		sem_wait(&miners_total) ;

		if( (! active_miners) && (! has_ore))
			break ;

		pthread_mutex_lock( &mutex );

		if((! active_miners) && (! has_ore) ) 
			break ;

		sem_wait(&smutex) ;

		if((! active_miners) && (! has_ore) ) 
			break ;

		order++ ;

		if(order >= miner_num)
			order = 0 ;

		while(miners[order].current_count <= 0){

			if( (! active_miners) && (! has_ore))
				break ;

				order++ ;

			if(order >= miner_num)
				order = 0 ;

		}

		//------------------------------------------------------------------------------------------

		if((! active_miners) && (! has_ore) ) 
			break ; 

		transporter_miner_routine( order , i ) ;

		//Producer = WaitProducer() ;

		if(*(transporters[i].carry) == COPPER) {

			sem_wait(&total_copper) ;

			sem_wait(&smutex) ;

			j=0 ;

			while(j < smelter_num){

				j++ ;

				if(order2 >= smelter_num-1)
					order2 = 0 ;

				else
					order2 ++ ;

				if( (smelters[order2].oreType == COPPER) && (smelters[order2].waiting_ore_count == 1) 
					&& (smelters[order2].loading_capacity > smelters[order2].waiting_ore_count) ) {

					flag = 1 ;
					break ;
				}

			}

			j = 0 ;

			while((flag == 0) && (j < smelter_num)) {

				j++ ;

				if(order2 >= smelter_num-1)
					order2 = 0 ;

				else
					order2 ++ ;

				if((smelters[order2].oreType == COPPER) && (smelters[order2].loading_capacity > smelters[order2].waiting_ore_count ) ){
					
					flag = 1 ;
					break ;
				}

			}	

			transporter_smelter_routine( order2, i) ;

		}

		else if(*(transporters[i].carry) == COAL) {

			sem_wait(&total_coal) ;

			sem_wait(&smutex) ;

			j=0 ;

			while(j < foundry_num){

				j++ ;

				if(order3 >= foundry_num-1)
					order3 = 0 ;

				else
					order3 ++ ;

				if( (foundries[order3].waiting_iron == 1) && 
					(foundries[order3].loading_capacity >  foundries[order3].waiting_coal)  ) {

					flag = 1 ;
					break ;
				}
 
			}

			j = 0 ;

			while((flag == 0) && (j < foundry_num)) {

				j++ ;

				if(order3 >= foundry_num-1)
					order3 = 0 ;

				else
					order3 ++ ;

				if((foundries[order3].loading_capacity > foundries[order3].waiting_coal) ){
					
					flag = 1 ;
					break ;
				}

			}

			if(foundries[order3].waiting_coal == 0 )	
				waiting_one_foundry ++ ;
 
			transporter_foundry_routine( order3, i) ;
		}


		else {

			sem_wait(&total_iron) ;

			sem_wait(&smutex) ;

			if( t_iron_smelters == 0 ) {
				
				if( waiting_one_foundry )
					flag2 = 2 ;
				else 
					flag2 = 4 ;
			}

			else if(t_iron_foundries == 0){
				
				if( waiting_one_smelter)
					flag2 = 1 ; 
				else
					flag2 = 3 ;
			}

			else if( ( waiting_one_smelter > 0 ) && (waiting_one_foundry > 0) ) {

				if( (rand() % 2 )== 0 ) flag2 = 1 ;

				else flag2 = 2 ;

			}

			else if( waiting_one_smelter > 0 )
				flag2 = 1 ;

			else if(waiting_one_foundry > 0)
				flag2 = 2 ;

			else if( (rand() % 2 )== 0 )
				flag2 = 3 ;
			
			else 
				flag2 = 4 ;

			if( flag2 == 1) {

				// put smelter

				waiting_one_smelter -- ;

				j = 0 ;

				while(j < smelter_num){

					j++ ;

					if(order2 >= smelter_num-1)
						order2 = 0 ;

					else
						order2 ++ ;

					if( (smelters[order2].oreType == IRON) && (smelters[order2].waiting_ore_count == 1) 
						&& (smelters[order2].loading_capacity > smelters[order2].waiting_ore_count) ) {

						break ;
					}

				}

				flag2 = 0 ;

				transporter_smelter_routine( order2, i) ;

				order2 ++ ;

			}	

			else if(flag2 == 2) {

				// put foundry

				waiting_one_foundry -- ;

				j = 0 ;

				while(j < foundry_num){

					j++ ;

					if(order3 >= foundry_num-1)
						order3 = 0 ;

					else
						order3 ++ ;

					if( (foundries[order3].waiting_coal == 1) 
						&& (foundries[order3].loading_capacity > foundries[order3].waiting_iron ) ) {

						break ;
					}

				}

				flag2 = 0 ;

				transporter_foundry_routine( order3, i) ;

				order3++ ;
			}

			else if( flag2 == 3 ) {

				waiting_one_smelter ++ ;

				//put smelter

				j = 0 ;

				while(j < smelter_num){

					j++ ;

					if(order2 >= smelter_num-1)
						order2 = 0 ;

					else
						order2 ++ ;

					if( (smelters[order2].oreType == IRON) 
						&& (smelters[order2].loading_capacity > smelters[order2].waiting_ore_count) ) {

						break ;
					}

				}

				flag2 = 0 ;

				transporter_smelter_routine( order2, i) ;

				order2++ ;
			}

			else if(flag2 == 4){

				//put foundry

				j = 0 ;

				while(j < foundry_num){

					j++ ;

					if(order3 >= foundry_num-1)
						order3 = 0 ;

					else
						order3 ++ ;

					if(foundries[order3].loading_capacity > foundries[order3].waiting_iron ) {

						break ;
					}

				}

				flag2 = 0 ;

				transporter_foundry_routine( order3, i) ;

				order3++ ;
			}

		}
				
	}

	FillTransporterInfo( transporter , transporters[i].ID , NULL ) ;

	WriteOutput(NULL, transporter, NULL, NULL,TRANSPORTER_STOPPED) ; 	

	return 0 ;	
} 

//-----------------------SMELTER ROUTİNE --------------------------------------------------------------------------------

void *smelter_routine( void *ptr) {

	struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
    	return 0;

    int s ;
	
	u_int i = *((unsigned int *)ptr) ;

	u_int interval = smelters[i].interval ;

	SmelterInfo *smelter = new SmelterInfo ;

	FillSmelterInfo(smelter, smelters[i].ID, smelters[i].oreType,
	 smelters[i].loading_capacity, smelters[i].waiting_ore_count, smelters[i].total_produce) ;

	WriteOutput(NULL, NULL, smelter, NULL, SMELTER_CREATED) ;

	ts.tv_sec += 5;

	while(true) {

		//WaitUntilTwoOres() ekle!!

		while ((s = sem_timedwait(&sem_smelters[i], &ts)) == -1 && errno == EINTR) 
               continue;       /* Restart if interrupted by handler */
		/* Check what happened */
		if (s == -1)
		{
		    if (errno == ETIMEDOUT)
		        break ;
		    else
		        perror("sem_timedwait");
		}

		//WaitUntilTwoOres()

		sem_wait(&smelter_two_ores[i]) ;

		if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
    		return 0;

    	ts.tv_sec += 5;

		//------------------------------------------------------------------------------------------ 

		FillSmelterInfo(smelter, smelters[i].ID, smelters[i].oreType,
	 	 smelters[i].loading_capacity, smelters[i].waiting_ore_count, smelters[i].total_produce) ;

		WriteOutput(NULL, NULL, smelter, NULL, SMELTER_STARTED) ;

		usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for production

		sem_wait(&mutex_smelter) ;		

		smelters[i].waiting_ore_count -= 2 ; 

		smelters[i].total_produce += 1 ;

		//SmelterProduced() ;

		if(smelters[i].oreType == COPPER) {
			sem_post(&total_copper) ;
			sem_post(&total_copper) ;
		}

		else if(smelters[i].oreType == IRON){ 
			sem_post(&total_iron) ;
			sem_post(&total_iron) ;
		}	

		//------------------------------------------------------------------------------------------ 

		FillSmelterInfo(smelter, smelters[i].ID, smelters[i].oreType,
	 	smelters[i].loading_capacity, smelters[i].waiting_ore_count, smelters[i].total_produce) ;

		WriteOutput(NULL, NULL, smelter, NULL, SMELTER_FINISHED) ; 

		sem_post(&mutex_smelter) ;

	}

	//SmelterStopped() ;

	smelters[i].finish_flag = 1 ;

	//------------------------------------------------------------------------------------------ 

	FillSmelterInfo(smelter, smelters[i].ID, smelters[i].oreType,
	 smelters[i].loading_capacity, smelters[i].waiting_ore_count, smelters[i].total_produce) ;	

	WriteOutput(NULL, NULL, smelter, NULL, SMELTER_STOPPED) ;

	return 0;
}

/*

WaitUntilTwoOres: Wait until two ores arrive at its storage and reserve the storage
spaces until the production is finished. If storage of smelter already have two ores,
thread will directly continue, otherwise it will block.

SmelterProduced: Signals available transporters that two storage spaces have been
opened in this smelter.

SmelterStopped: Marks the smelter out of simulation so that transporters no more
deliver to this smelter.

*/

//------------------------- FOUNDRY ROUTİNE ---------------------------------------------------------------------------------------

void *foundry_routine( void *ptr) {

	struct timespec ts1;
	if (clock_gettime(CLOCK_REALTIME, &ts1) == -1)
    	return 0;

    int s1 ;

	u_int i = *((unsigned int *)ptr) ;

	u_int interval = foundries[i].interval ;

	FoundryInfo *foundry = new FoundryInfo ;

	FillFoundryInfo(foundry, foundries[i].ID, foundries[i].loading_capacity, foundries[i].waiting_iron, foundries[i].waiting_coal,
	 foundries[i].total_produce) ;

	WriteOutput(NULL, NULL, NULL, foundry, FOUNDRY_CREATED) ;

	ts1.tv_sec += 5;

	while( true ) {

		while ((s1 = sem_timedwait(&sem_foundries[i], &ts1)) == -1 && errno == EINTR) 
               continue;       /* Restart if interrupted by handler */
		/* Check what happened */
		if (s1 == -1)
		{
		    if (errno == ETIMEDOUT)	
		        break ;
		    else
		        perror("sem_timedwait");
		}

		sem_wait(&one_iron_coal[i]) ;

		if (clock_gettime(CLOCK_REALTIME, &ts1) == -1)
    		return 0;

    	ts1.tv_sec += 5;

		FillFoundryInfo(foundry, foundries[i].ID, foundries[i].loading_capacity, foundries[i].waiting_iron, foundries[i].waiting_coal,
		foundries[i].total_produce) ;	

		WriteOutput(NULL, NULL, NULL, foundry, FOUNDRY_STARTED) ;

		usleep(interval - (interval*0.01) + (rand()%(int)(interval*0.02))) ; // for production

		sem_wait(&mutex_foundry) ;

		foundries[i].waiting_iron -= 1 ;
		foundries[i].waiting_coal -= 1 ;

		foundries[i].total_produce += 1 ;

		//FoundryProduced() ;

		sem_post(&total_iron) ;
		sem_post(&total_coal) ;

		FillFoundryInfo(foundry, foundries[i].ID, foundries[i].loading_capacity, foundries[i].waiting_iron, foundries[i].waiting_coal,
		foundries[i].total_produce) ;

		WriteOutput(NULL, NULL, NULL, foundry, FOUNDRY_FINISHED) ;

		sem_post(&mutex_foundry) ;
	}

	// FoundryStopped() ;

	foundries[i].finish_flag = 1 ;

	FillFoundryInfo(foundry, foundries[i].ID, foundries[i].loading_capacity, foundries[i].waiting_iron, foundries[i].waiting_coal,
	 foundries[i].total_produce) ;

	WriteOutput(NULL, NULL, NULL, foundry, FOUNDRY_STOPPED) ;

	return 0 ;
}

/*

WaitForOneIronOneCoal: Wait until one coal and one iron ore arrives at its storage
and reserve the storage spaces until the production is finished. If storage of foundry
already have these two ores, thread will directly continue, otherwise it will block.

FoundryProduced: Signals available transporters that storage spaces for an iron and a
coal ore have been opened in this foundry.

FoundryStopped: Marks foundry stopped so that transporters no more deliver to this
foundry.

*/

//------------------------------------------------------------------------------------------------------------------------------------------

int main( void ){

	// take inputs for miners

	u_int t_copper = 0 ;
	u_int t_coal   = 0 ;
	u_int t_iron   = 0 ;

	fscanf(stdin , "%u" , &miner_num ) ;

	active_miners = miner_num ;
	has_ore       = miner_num ;

	miners = new Miners[miner_num] ;

	miner_full = new sem_t[miner_num] ;
	miner_empty = new sem_t[miner_num] ;

	for(i=0 ; i < miner_num ; i++){

		fscanf(stdin , "%u" , &interval) ;
		fscanf(stdin , "%u" , &capacity) ;
		fscanf(stdin , "%u" , &oretype) ;
		fscanf(stdin , "%u" , &total) ;

		miners[i].ID = i+1 ;
		miners[i].oreType = oretype ;
		miners[i].capacity = capacity ;
		miners[i].current_count = 0 ;
		miners[i].interval = interval ;
		miners[i].total = total ;

	}

	// take inputs for transporters

	fscanf(stdin , "%u" , &transporter_num ) ;	

	transporters = new Transporters[transporter_num] ;

	for(i=0 ; i < transporter_num ; i++){

		fscanf(stdin , "%u" , &interval) ;

		transporters[i].ID = i+1 ;
		transporters[i].carry = NULL ;
		transporters[i].interval = interval ;

	}

	// take inputs for smelters

	fscanf(stdin , "%u" , &smelter_num ) ;

	smelters = new Smelters[smelter_num] ;
	sem_smelters = new sem_t[smelter_num] ;
	smelter_two_ores = new sem_t[smelter_num] ;

	for(i=0 ; i < smelter_num ; i++){

		fscanf(stdin , "%u" , &interval) ;
		fscanf(stdin , "%u" , &capacity) ;
		fscanf(stdin , "%u" , &oretype) ;

		smelters[i].ID = i+1 ;
		smelters[i].oreType = oretype ;
		smelters[i].loading_capacity = capacity ;
		smelters[i].waiting_ore_count = 0 ;
		smelters[i].total_produce = 0 ;
		smelters[i].interval = interval ; 
		smelters[i].finish_flag = 0 ;
		smelters[i].smelter_lock = 0 ;
 
		if(oretype == COPPER)
			t_copper += capacity ;

		else {
			t_iron+= capacity ;
			t_iron_smelters += capacity ;
		}
	}

	// take inputs for foundries

	fscanf(stdin , "%u" , &foundry_num ) ;

	foundries = new Foundries[foundry_num] ;
	one_iron_coal = new sem_t[foundry_num] ;
	sem_foundries = new sem_t[foundry_num] ;

	for(i=0 ; i < foundry_num ; i++){

		fscanf(stdin , "%u" , &interval) ;
		fscanf(stdin , "%u" , &capacity) ;
		
		foundries[i].ID = i+1 ;
		foundries[i].loading_capacity = capacity ;
		foundries[i].waiting_iron = 0 ;
		foundries[i].waiting_coal = 0 ;
		foundries[i].total_produce = 0 ;
		foundries[i].interval = interval ;
		foundries[i].finish_flag = 0 ;
		foundries[i].iron_lock = 0 ;
		foundries[i].coal_lock = 0 ;

		t_iron += capacity ;
		t_coal += capacity ; 

		t_iron_foundries += capacity ; 
 
	}

	pthread_t miner_threads[miner_num] ;
	pthread_t transporter_threads[transporter_num] ;
	pthread_t smelter_threads[smelter_num] ;
	pthread_t foundry_threads[foundry_num] ;

	u_int args1[miner_num] ;
	u_int args2[transporter_num] ;
	u_int args3[smelter_num] ;
	u_int args4[foundry_num] ;

	sem_init(&miners_total , 0 , 0) ;
	sem_init(&smutex , 0 , 1) ;
	sem_init(&mutex_smelter , 0 , 1) ;
	sem_init(&total_copper, 0 ,t_copper) ;
	sem_init(&total_iron, 0 ,t_iron) ;
	sem_init(&total_coal, 0 ,t_coal) ;
	sem_init(&mutex_foundry , 0 , 1) ;

	InitWriteOutput() ;

	for(i=0 ; i < miner_num ; i++){

		sem_init(&miner_full[i] , 0 , miners[i].capacity) ;
		sem_init(&miner_empty[i] , 0 , 0 ) ;

		args1[i] = i ;

		pthread_create( &miner_threads[i], NULL, miner_routine, (void *) &args1[i] );
	}
	

	for(i=0 ; i < transporter_num ; i++){

		args2[i] = i ;

		pthread_create( &transporter_threads[i], NULL, transporter_routine, (void *) (&args2[i]) );
	} 

	for(i=0 ; i < smelter_num ; i++){

		sem_init(&sem_smelters[i] , 0 , 0) ;
		sem_init(&smelter_two_ores[i] , 0 , 0) ;

		args3[i] = i ;

		pthread_create( &smelter_threads[i], NULL, smelter_routine, (void *) (&args3[i]) );
	} 

	for(i=0 ; i < foundry_num ; i++){

		sem_init(&sem_foundries[i] , 0 , 0) ;
		sem_init(&one_iron_coal[i] , 0 , 0) ;

		args4[i] = i ;

		pthread_create( &foundry_threads[i], NULL, foundry_routine, (void *) (&args4[i]) );
	} 


	for(i=0 ; i < miner_num ; i++){

		pthread_join( miner_threads[i], NULL ) ;
	}


	for(i=0 ; i < transporter_num ; i++){

		pthread_join( transporter_threads[i], NULL ) ;
	}


	for(i=0 ; i < smelter_num ; i++){

		pthread_join( smelter_threads[i], NULL ) ;
	}

	for(i=0 ; i < foundry_num ; i++){

		pthread_join( foundry_threads[i], NULL ) ;
	}

/*
	semclose lar !!!!!

	delete ler !!!!!!
	(malloc vs)
*/

	sem_close(&miners_total);
    sem_close(&smutex);

    for(i = 0 ; i < miner_num ; i--	){
		
		sem_close(&miner_empty[i]);
		sem_close(&miner_full[i]);
	}

	return 0 ;
}
