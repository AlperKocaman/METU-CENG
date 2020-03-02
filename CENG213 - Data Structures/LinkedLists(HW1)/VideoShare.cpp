#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */

VideoShare::VideoShare() {

	users = LinkedList<User >();
    videos = LinkedList<Video >();
}

VideoShare::~VideoShare() {
	
}


void VideoShare::createUser(const string & userName, const string & name, const string & surname) {
	if(userName!=""){

		//user1(userName,name,surname) ;

		users.insertNode(users.getHead(),User(userName,name,surname)) ;
	}
}

void VideoShare::loadUsers(const string & fileName) {

	ifstream file;
	file.open(fileName.c_str());

	string line;
	string userName;
    string Name;
    string surName;
	if (!file.good())
        return;

    while(file.good()) {

    	getline(file,line,';') ;

    	if(line == "") continue ;

    	userName = line ;

    	getline(file,line,';') ;

    	Name = line ;

    	getline(file,line) ;

    	surName = line ;

    	users.insertNode(users.getHead(),User(userName,Name,surName)) ;
    	//createUser(userName,Name,surName) ;

    }

    file.close() ;
}

void VideoShare::createVideo(const string & title, const string & genre) {

	Video video1(title,genre) ;

	videos.insertNode(videos.getHead(),video1) ;
}

void VideoShare::loadVideos(const string & fileName) {

	ifstream file;
	file.open(fileName.c_str());

	string line;
	string Title;
    string Genre;

	if (!file.good())
        return;

    while(file.good()) {

    	getline(file,line,';') ;

    	Title = line ;

    	getline(file,line) ;

    	Genre = line ;

    	videos.insertNode(videos.getHead(),Video(Title,Genre)) ;
}

}

void VideoShare::addFriendship(const string & userName1, const string & userName2) {

	if(&userName1 == NULL || &userName2 == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getData().getUsername() == userName1) 

			break;

		temp = temp->getNext() ;
	}

	if(temp == NULL) return ;

	Node<User> * temp2 = users.first() ;

	while(temp2) {

		if(temp2->getData().getUsername() == userName2) 

			break;

		temp2 = temp2->getNext() ;
	}

	if(temp2 == NULL) return ;

	temp->getDataPtr()->addFriend(temp2->getDataPtr()) ;

	temp2->getDataPtr()->addFriend(temp->getDataPtr()) ;
	 
}
    
void VideoShare::removeFriendship(const string & userName1, const string & userName2) {

	if(&userName1 == NULL || &userName2 == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName1) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(temp == NULL) return ;

	Node<User> * temp2 = users.first() ;

	while(temp2) {

		if(temp2->getDataPtr()->getUsername() == userName2) 

			break;

		temp2 = temp2->getNext() ;
	}

	if(temp2 == NULL) return ;

	temp->getDataPtr()->removeFriend(temp2->getDataPtr()) ;

	temp2->getDataPtr()->removeFriend(temp->getDataPtr()) ;

}

void VideoShare::updateUserStatus(const string & userName, Status newStatus) {

	if(&userName == NULL ) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(temp == NULL) return ;

	temp->getDataPtr()->updateStatus(newStatus) ;
}

void VideoShare::subscribe(const string & userName, const string & videoTitle) {

	if(&userName == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(temp == NULL || temp->getDataPtr()->getStatus() == SUSPENDED) return ;

	if(&videoTitle == NULL) return ;

	Node<Video> * temp2 = videos.first() ;

	while(temp2) {

		if(temp2->getDataPtr()->getTitle() == videoTitle) //getdata mi ptr mi 

			break;

		temp2 = temp2->getNext() ;
	}

	if(temp2 == NULL ) return ;

	temp->getDataPtr()->subscribe(temp2->getDataPtr()) ;	

}

void VideoShare::unSubscribe(const string & userName, const string & videoTitle) {

	if(&userName == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(temp == NULL || temp->getDataPtr()->getStatus() == SUSPENDED) return ;

	if(&videoTitle == NULL) return ;

	Node<Video> * temp2 = videos.first() ;

	while(temp2) {

		if(temp2->getDataPtr()->getTitle() == videoTitle) //getdata mi ptr mi 

			break;

		temp2 = temp2->getNext() ;
	}

	if(temp2 == NULL ) return ;

	temp->getDataPtr()->unSubscribe(temp2->getDataPtr()) ;

}

void VideoShare::deleteUser(const string & userName) {

	if(&userName == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(!temp) return ;

	temp->getDataPtr()->~User() ;

}

void VideoShare::sortUserSubscriptions(const string & userName) {

	if(&userName == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(!temp) return ;

	Node< Video*>* p = temp->getDataPtr()->getSubscriptions()->getHead() ;

	Node< Video*>* p2 = p->getNext() ;

	//cout<<p2->getNext()->getData()->getTitle() << endl;

	int i1 = 0 ;

	int i2 = 1 ;	

	if(p2 == NULL) return;

	while(p->getNext()) {

		while(p2->getNext()) {

			cout<<p2->getData()->getTitle()<<endl ;

			cout<<p2->getNext()->getData()->getTitle()<<endl ;

			if(p2->getData()->getTitle() > p2->getNext()->getData()->getTitle()) {

				cout<<"IN"<< endl ;

				temp->getData().getSubscriptions()->swap(i1,i2) ;

				p2 = p ;	
			}

			else cout<<"OUT"<< endl ;

			i1++ ;
			i2++;
		}

		p = p->getNext() ;

		

	}

}

void VideoShare::printUserSubscriptions(const string & userName) {

	if(&userName == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(!temp) return ;	

	temp->getDataPtr()->printSubscriptions() ;
}

void VideoShare::printFriendsOfUser(const string & userName) {

	if(&userName == NULL) return ;

	Node<User> * temp = users.first() ;

	while(temp) {

		if(temp->getDataPtr()->getUsername() == userName) //getdata mi ptr mi 

			break;

		temp = temp->getNext() ;
	}

	if(!temp) return ;

	temp->getDataPtr()->printFriends() ;
}

void VideoShare::printCommonSubscriptions(const string & userName1, const string & userName2) {

}

void VideoShare::printFriendSubscriptions(const string & userName) {


}

bool VideoShare::isConnected(const string & userName1, const string & userName2) {

	
}

/*Node<User>* VideoShare::findUser(const string & userName) {

	Node<User>* temp = users.first() ;

    while(temp) {

        if(temp->getData().getUsername() == userName) 
        
            return temp ;

        temp = temp->getNext() ;        
    }

    return NULL ;
}	

*/