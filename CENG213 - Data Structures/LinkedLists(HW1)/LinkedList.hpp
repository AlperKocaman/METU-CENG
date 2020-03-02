#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head; 
    int length;  
public:

    LinkedList();
    LinkedList(const LinkedList<T>& ll);
    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data); 
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};

template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */

template <class T>
LinkedList<T>::LinkedList() { 

    head = new Node<T>;

    ///head->setNext(NULL) ; 

    length = 0 ;
} 

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll) {

    head = new Node<T>;

    //head->setNext(NULL) ; 

    length = 0 ;

    *this  = ll ;//hata olabilir bir daha bak!!!!!!!!!!!

}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll) {

    if(this == &ll) return *this ;

    clear() ;

    Node<T> * temp = ll.first() ;

    if(!temp) return *this ;

    Node<T>* firstNode = new Node<T>(temp->getData()) ; 

    Node<T> * temp2 = firstNode ;

    head->setNext(firstNode) ;

    length = 1 ;

    while(temp->getNext()){

        temp = temp->getNext() ;

        Node<T> * newNode = new Node<T>(temp->getData()) ;

        temp2->setNext(newNode) ;

        temp2 = newNode ; 

        length ++ ;       

    }

    return *this ;
}

template<class T>
LinkedList<T>::~LinkedList() {

    Node<T>* temp = first() ;

    while(temp) {

        head->setNext(temp->getNext()) ;

        delete temp ;

        temp = first() ;

    }

    delete head ;

    length = 0  ;    
}

template <class T>
Node<T>* LinkedList<T>::getHead() const {

    return head ;
}

template <class T>
Node<T>* LinkedList<T>::first() const {
        
        return head->getNext() ;
}


template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const {

    Node <T>* temp = getHead() ;

    while(temp->getNext()) {

        if(temp->getNext()->getData() == data)

            return temp ;

        temp = temp->getNext() ;
    }

    return NULL ;
}

template <class T>  
Node<T>* LinkedList<T>::findNode(const T& data) const {

    Node<T>* temp ;

    temp = first() ;

    while(temp) {

        if(temp->getData() == data) 
        
            return temp ;

        temp = temp->getNext() ;        
    }

    return NULL ;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data) {

    Node<T>* newNode = new Node<T>(data) ;

    newNode->setNext(prev->getNext()) ;

    prev->setNext(newNode)            ;

}

template <class T>    
void LinkedList<T>::deleteNode(Node<T>* prevNode) {

    length -- ;

    Node<T>* temp  = prevNode->getNext() ;

    prevNode->setNext(temp->getNext())   ;

    delete temp ;   

}

template <class T>
void LinkedList<T>::clear() {

    Node<T>* temp = first() ;

    while(temp) {

        head->setNext(temp->getNext()) ;

        delete temp ;

        temp = first() ;

    }

    length = 0 ;

}

template <class T>
size_t LinkedList<T>::getLength() const {

    return length ;
}

template <class T>
void LinkedList<T>::swap(int index1, int index2){
    
    if(index2 < index1) {

        index1 = index1 + index2 ;

        index2 = index1 - index2 ;

        index1 = index1 - index2 ;
    }

    if( index1 == index2 ) return ;

    int i1,i2 ;

    i1 = i2 = -1 ;

    Node<T>* temp_prev = getHead()   ;

    Node<T>* temp ;

    while(i1 < (index1-1)) {

        temp_prev = temp_prev->getNext() ;

        i1 ++ ;
    }

    i1 ++ ;

    temp = temp_prev->getNext() ;

    Node<T>* temp2_prev = temp ;

    Node<T>* temp2 = temp2_prev->getNext() ;

    i2 = i1 ;

    while(i2 < (index2-1)) {

        temp2_prev = temp2_prev->getNext() ;

        i2 ++ ;
    }

    temp2 = temp2_prev->getNext() ;

    Node<T> * p1 = temp->getNext() ;

    Node<T> * p2 = temp2->getNext() ;

    if((index2 - index1) == 1) {

        temp_prev->setNext(temp2) ;

        temp->setNext(p2) ;

        temp2->setNext(temp) ;

        return ;
    }

    temp_prev->setNext(temp2) ;

    temp2->setNext(p1) ;

    temp2_prev->setNext(temp) ;

    temp->setNext(p2) ;

    return ;

}

/* end of your implementations*/
#endif  

