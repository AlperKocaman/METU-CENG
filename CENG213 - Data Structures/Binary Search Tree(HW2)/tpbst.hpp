#ifndef TWOPHASEBST_H
#define TWOPHASEBST_H

#include <iostream>
#include <string>
#include <stack>
#include <list>
// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class TwoPhaseBST {
private: //do not change
    struct SecondaryNode {
        std::string key;
        T data;
        SecondaryNode *left;
        SecondaryNode *right;

        SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r);
    };

    struct PrimaryNode {
        std::string key;
        PrimaryNode *left;
        PrimaryNode *right;
        SecondaryNode *rootSecondaryNode;

        PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn);
    };

public: // do not change.
    TwoPhaseBST();
    ~TwoPhaseBST();

    TwoPhaseBST &insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data);
    TwoPhaseBST &remove(const std::string &primaryKey, const std::string &secondaryKey);
    TwoPhaseBST &print(const std::string &primaryKey = "", const std::string &secondaryKey = "");
    T *find(const std::string &primaryKey, const std::string &secondaryKey);

private: // you may add your own utility member functions here.
    void destructNode(PrimaryNode * &root);
    void destructNode(SecondaryNode * &root);
    void insert_helper( const std::string &primaryKey, const std::string &secondaryKey, const T &data, PrimaryNode * &pNode ) ;
    void insert_helper2( const std::string &secondaryKey, const T &data, SecondaryNode * &sNode ) ;
    //find_pNode_helper( const std::string &primaryKey ,PrimaryNode * &pNode ) ;
    void print_helper1( SecondaryNode * &sNode , const std::string &secondaryKey ) ;
    void print_helper2( PrimaryNode * &pNode , const std::string &primaryKey)   ;
    T *find_helper1( const std::string &primaryKey, const std::string &secondaryKey, PrimaryNode * &pNode ) ;
    T *find_helper2( const std::string &secondaryKey, SecondaryNode * &sNode ) ;
    void remove_helper1( const std::string &primaryKey, const std::string &secondaryKey, PrimaryNode * &pNode ) ;
    void remove_helper2( const std::string &secondaryKey, SecondaryNode * &sNode, SecondaryNode * &sNode_parent , PrimaryNode * &pNode) ;
    void remove_helper3( SecondaryNode * &sNode , SecondaryNode * &sNode2 , SecondaryNode * &sNode_parent , PrimaryNode * &pNode  ) ;

private: // do not change.
    PrimaryNode *root; //designated root.

    // do not provide an implementation. TwoPhaseBST's are not copiable.
    TwoPhaseBST(const TwoPhaseBST &);
    const TwoPhaseBST &operator=(const TwoPhaseBST &);
};

template <class T>
TwoPhaseBST<T>::SecondaryNode::SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r)
        : key(k), data(d), left(l), right(r) {}

template <class T>
TwoPhaseBST<T>::PrimaryNode::PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn)
        : key(k), left(l), right(r), rootSecondaryNode(rsn) {}

template <class T>
TwoPhaseBST<T>::TwoPhaseBST() : root(NULL) {}

template <class T>
TwoPhaseBST<T>::~TwoPhaseBST() {
    destructNode(root);
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data) {
    /* IMPLEMENT THIS */
    insert_helper( primaryKey, secondaryKey, data, root) ;

    return *this ;
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::remove(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */

    if( primaryKey == "" || secondaryKey == "" ) return *this ;

    remove_helper1( primaryKey , secondaryKey , root ) ;

    return *this ;
}

template <class T>
TwoPhaseBST<T> &TwoPhaseBST<T>::print(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */

    if( root == NULL || root->key == "") {

        std::cout<<"{}"<<std::endl ;

        return *this ;
    }

    if( primaryKey == "" && secondaryKey != "" ) return *this ;

    if( primaryKey != "" && secondaryKey == "" ) {

        PrimaryNode *temp = root ;

        while( temp != NULL && temp->key != "" && temp->key != primaryKey ) {

            if( temp->key > primaryKey) temp = temp->left ;

            else if( temp->key < primaryKey) temp = temp->right ;
        }

        if( temp == NULL ) {

            std::cout<<"{}"<<std::endl ;

            return *this ;
        }

        SecondaryNode *temp2 = temp->rootSecondaryNode ;

        std::cout<<"{\""<<primaryKey<<"\" : {" ;

        if(temp2 != NULL) {

            while( temp2->left != NULL) temp2 = temp2->left ;

            print_helper1( temp->rootSecondaryNode , temp2->key ) ;

            std::cout<<"}}"<<std::endl ;

            return *this ; }

        std::cout<<"}}"<<std::endl ;

        return *this ;

    }

    if( primaryKey != "" && secondaryKey != "" ) {

        PrimaryNode *temp = root ;

        while( temp != NULL && temp->key != "" && temp->key != primaryKey ) {

            if( temp->key > primaryKey) temp = temp->left ;

            else if( temp->key < primaryKey) temp = temp->right ;
        }

        if( temp == NULL ) {

            std::cout<<"{}"<<std::endl ;

            return *this ;
        }

        SecondaryNode *temp2 = temp->rootSecondaryNode ;

        while( temp2 != NULL && temp2->key != "" && temp2->key != secondaryKey ) {

            if( temp2->key > secondaryKey) temp2 = temp2->left ;

            else if( temp2->key < secondaryKey) temp2 = temp2->right ;
        }

        if( temp2 == NULL ) {

            std::cout<<"{}"<<std::endl ;

            return *this ;
        }

        std::cout<<"{\""<<primaryKey<<"\" : {"<< "\""<<secondaryKey<<"\" : \""<<temp2->data<<"\""<<"}}"<<std::endl ;

        return *this ;             

    }

    PrimaryNode *temp = root ;

    if(temp != NULL) 

        while( temp->left != NULL) temp = temp->left ;

    std::cout<<"{" ;

    print_helper2( root , temp->key) ;

    std::cout<<"}" ;

    std::cout<<std::endl ;

    return *this ;
}

template <class T>
T *TwoPhaseBST<T>::find(const std::string &primaryKey, const std::string &secondaryKey) {
    /* IMPLEMENT THIS */

    return find_helper1(primaryKey, secondaryKey, root) ;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::PrimaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    destructNode(root->rootSecondaryNode);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::SecondaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::insert_helper( const std::string &primaryKey, const std::string &secondaryKey, const T &data, PrimaryNode * &pNode ) {

    if( pNode == NULL || pNode->key == "") {        

        pNode = new PrimaryNode( primaryKey, NULL, NULL, NULL ) ;

        SecondaryNode *rsn = new SecondaryNode( secondaryKey, data, NULL, NULL ) ;

        pNode->rootSecondaryNode = rsn ;

        return ;
    }

    else if( pNode->key > primaryKey ) {       

        insert_helper( primaryKey , secondaryKey , data , pNode->left ) ;
    }

    else if( pNode->key < primaryKey ) {

        insert_helper( primaryKey , secondaryKey , data , pNode->right ) ;
           
    }

    else if( pNode->key == primaryKey ) {

        insert_helper2( secondaryKey, data, pNode->rootSecondaryNode ) ;
             
    }
}

template <class T>
void TwoPhaseBST<T>::insert_helper2( const std::string &secondaryKey, const T &data, SecondaryNode * &sNode ) {

    if( sNode == NULL || sNode->key == "" ) {

        sNode = new SecondaryNode( secondaryKey, data, NULL, NULL ) ;

        return ;
    }

    else if(sNode->key > secondaryKey ) { 

        insert_helper2( secondaryKey, data, sNode->left) ;
    }

    else if(sNode->key < secondaryKey ) {

        insert_helper2( secondaryKey, data, sNode->right) ;
    }
}

template <class T>
void TwoPhaseBST<T>::print_helper1( SecondaryNode * &sNode , const std::string &secondaryKey ) {

    if( sNode ) print_helper1( sNode->left , secondaryKey) ;

    if( sNode && sNode->key == secondaryKey ) {

        std::cout<<"\""<<sNode->key<<"\" : \""<<sNode->data<<"\"" ;
    }

    else if( sNode ) {

        std::cout<<", \""<<sNode->key<<"\" : \""<<sNode->data<<"\"" ;
    }

    if( sNode ) print_helper1( sNode->right , secondaryKey ) ;
}

template <class T>
void TwoPhaseBST<T>::print_helper2( PrimaryNode * &pNode , const std::string &primaryKey ) {

    if( pNode && pNode->key != "" ) print_helper2( pNode->left , primaryKey ) ;

    if( pNode && pNode->key == primaryKey) {

        std::cout<<"\""<<pNode->key<<"\" : {" ;

        SecondaryNode *temp2 = pNode->rootSecondaryNode ;

        if(temp2 != NULL) {

            while( temp2->left != NULL) temp2 = temp2->left ;

            print_helper1( pNode->rootSecondaryNode , temp2->key ) ;

            std::cout<<"}" ;
        } 

        else 

            std::cout<<"}" ;
    }

    else if( pNode ) {

        std::cout<<", \""<<pNode->key<<"\" : {" ;

        SecondaryNode *temp2 = pNode->rootSecondaryNode ;

        if(temp2 != NULL) {

            while( temp2->left != NULL) temp2 = temp2->left ;

            print_helper1( pNode->rootSecondaryNode , temp2->key ) ;

            std::cout<<"}" ;
        } 

        else 

            std::cout<<"}" ;
    }

    if(  pNode && pNode->key != "" ) print_helper2( pNode->right , primaryKey ) ;
}

template <class T>
T *TwoPhaseBST<T>::find_helper1( const std::string &primaryKey, const std::string &secondaryKey, PrimaryNode * &pNode ) {

    if( pNode == NULL || pNode->key == "") {        

        return NULL;
    }

    else if( pNode->key > primaryKey ) {       

        find_helper1( primaryKey , secondaryKey , pNode->left ) ;
    }

    else if( pNode->key < primaryKey ) {

        find_helper1( primaryKey , secondaryKey , pNode->right ) ;
           
    }

    else if( pNode->key == primaryKey ) {

        find_helper2( secondaryKey, pNode->rootSecondaryNode ) ;
             
    }
}

template <class T>
T *TwoPhaseBST<T>::find_helper2( const std::string &secondaryKey, SecondaryNode * &sNode ) {

    if( sNode == NULL || sNode->key == "" ) {

        return NULL ;
    }

    else if(sNode->key > secondaryKey ) { 

        find_helper2( secondaryKey, sNode->left) ;
    }

    else if( sNode->key < secondaryKey ) {

        find_helper2( secondaryKey, sNode->right) ;
    }

    else if( sNode->key == secondaryKey )

        return   &(sNode->data) ;
}

template <class T>
void TwoPhaseBST<T>::remove_helper1( const std::string &primaryKey, const std::string &secondaryKey, PrimaryNode * &pNode ) {

    if( pNode == NULL || pNode->key == "") {        

        return ;
    }

    else if( pNode->key > primaryKey ) {       

        remove_helper1( primaryKey , secondaryKey , pNode->left ) ;
    }

    else if( pNode->key < primaryKey ) {

        remove_helper1( primaryKey , secondaryKey , pNode->right ) ;
           
    }

    else if( pNode->key == primaryKey ) {

        remove_helper2( secondaryKey, pNode->rootSecondaryNode, pNode->rootSecondaryNode , pNode ) ;
             
    }
}

template <class T>
void TwoPhaseBST<T>::remove_helper2( const std::string &secondaryKey, SecondaryNode * &sNode, SecondaryNode * &sNode_parent , PrimaryNode * &pNode ) {

    if( sNode == NULL || sNode->key == "" ) {

        return ;
    }

    else if(sNode->key > secondaryKey ) { 

        remove_helper2( secondaryKey, sNode->left, sNode , pNode) ;
    }

    else if( sNode->key < secondaryKey ) {

        remove_helper2( secondaryKey, sNode->right, sNode , pNode ) ;
    }

    else if( sNode->key == secondaryKey ) {

        if( sNode->right == NULL && sNode->left == NULL ) {

            destructNode( sNode ) ;
        }

        else if( sNode->right == NULL && sNode->left != NULL ) {
            
            if( pNode->rootSecondaryNode == sNode ) {

                SecondaryNode *temp = sNode ;

                pNode->rootSecondaryNode = sNode->left ;

                temp->left = NULL ; 

                destructNode( temp ) ;
            }

            else {

                SecondaryNode *temp = sNode ;

                if( sNode_parent->left == sNode ) sNode_parent->left = sNode->left ;

                else if( sNode_parent->right == sNode ) sNode_parent->right = sNode->left ;
                    
                temp->left = NULL ; 

                destructNode( temp ) ;
            }
        }

        else {

            SecondaryNode *newNode = sNode->right ;

            SecondaryNode *newNode_parent = sNode ;

            while( newNode->left ) {

                newNode_parent = newNode ; 

                newNode = newNode->left ;

            }

            if( newNode_parent != sNode ) {

                newNode->left = sNode->left ;

                newNode_parent->left = newNode->right ;

                newNode->right = sNode->right ;

                SecondaryNode *temp = sNode ;

                if( sNode_parent == sNode ) pNode->rootSecondaryNode = newNode ;

                else if( sNode_parent->left == sNode )  sNode_parent->left = newNode ;

                else if( sNode_parent->right == sNode )  sNode_parent->right = newNode ;

                temp->left = NULL ;

                temp->right = NULL ;

                destructNode( temp ) ;  

            }

            else {

                newNode->left = sNode->left ;

                SecondaryNode *temp = sNode ;

                if( pNode->rootSecondaryNode == sNode ) pNode->rootSecondaryNode = newNode ;

                else if( sNode_parent->left == sNode )  sNode_parent->left = newNode ;

                else if( sNode_parent->right == sNode )  sNode_parent->right = newNode ;

                temp->left = NULL ;

                temp->right = NULL ;

                destructNode( temp ) ;                

            }

        }
        
    }
}   

#endif //TWOPHASEBST_H
