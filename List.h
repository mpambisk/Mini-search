
#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <stdint.h>

using namespace std;
/*
    REMEMBER TO USE POPALL2 WITH 
    STD TYPES DATA.
*/
template <class T> class Node
{
    T* data; 		//the object information
    long long int priority;
    Node* next; 	//pointer to the next node element
    Node* prev;     //pointer to the previous node element

public:
	Node(){            
		data = NULL;
		next = NULL;
		prev=NULL;
		priority =0;
        //cout<<"node const"<<endl;
	}
	~Node(){           
		next = NULL;
        if(data!=NULL)
            delete data;
		data = NULL;
		//cout<<"node dest"<<endl;
	}
	void set_priority(long long int to_set){
		priority = to_set;
	}
	long long int get_priority(){return priority;}
	void setData(T* info){
		data = info;
	}
	void setNext(Node * n){
		next = n;
	}
	void setPrev(Node * n){
		prev= n;
	}
	T* getData(){
		return data;
	}
	Node* getNext(){
		return next;
	}
	Node * getPrev(){
		return prev;
	}
	void print(){
        data->print();		
	}
    void dumpNode(char * filen,FILE * dfile){
         data->dump(filen,dfile);
    }
    void dataNULL(){
        data=NULL;
    }
};


//-----------------------Lista-----------------------//
template <class T> class Lista
{
    Node<T> *head, *tail;       //pointers to start and end of the list
    uint64_t counter;           //number of nodes in the list

public:

    Lista(){
    	counter = 0;
        head = NULL;
        tail = NULL;
        //cout<<"Lista const"<<endl;
    }
    ~Lista(){
    	while (counter > 0){
    		pop();
    	}
    	//cout<<"list destr"<<endl;
    }
    Node<T> * getHead(){return head;}
    Node <T> * get_tail(){return tail;}
    uint64_t get_counter(){return counter;}
    void deleteLista(){
        T* temp;
		while (counter > 0){
    		temp = pop();
    		delete temp;
    	}
    }
    //Method adds info to the end of the list
    Node<T> * push(T* info){
        if(head == NULL) //if our list is currently empty
        {
        	counter = 1;
            head = new Node<T>; //Create new node of type T
            head->setData(info);
            tail = head;
        }
        else //if not empty add to the end and move the tail
        {
        	counter++;
            Node<T>* temp = new Node<T>;
            temp->setData(info);
            tail->setNext(temp);
            temp->setPrev(tail);
            tail = tail->getNext();
        }
        return tail;
    }
    Node<T> * push_priority(T* info,long long int prio){
        if(head == NULL) //if our list is currently empty
        {
        	counter = 1;
            head = new Node<T>; //Create new node of type T
            head->setData(info);
            head->set_priority(prio);
            tail = head;
        }
        else //if not empty add to the end and move the tail
        {
        	counter++;
            Node<T>* temp = new Node<T>;
            temp->setData(info);
            temp->set_priority(prio);
           	Node<T>* temp2 = head;
           	while(temp2!=NULL){
           		if(prio>temp2->get_priority()){
           			Node<T> * prev =temp2->getPrev();
           			Node<T> * nex = temp2->getNext();
           			prev->setNext(temp);
           			temp->setNext(temp2);
           			temp->setPrev(prev);
           			temp2->setPrev(temp);
           			break;
           		}
           		temp2=temp2->getNext();
           	}
           	if(temp2==NULL){
           		tail->setNext(temp);
           		temp->setPrev(tail);
           		tail=temp;
           	}
           
        }
        return tail;
    }
/*
    This function will delete all nodes and the objects
    that they point at.
*/
    void popall(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return;
        }
		while (counter > 0){
    		pop();
    	}
    }
    /*
        This function will delete all nodes but it will not
        destroy the pointed objects.
    */
    void popall2(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return;
        }
		while (counter > 0){
    		pop2();
    	}
    }
    /*
        pops the first object out of the lists and destroys the node.
        Probably also destroys data. Use pop2 not to destroy data.
        Return value probably NULL.
    */
    T* pop(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return NULL;
        }
		
		counter--;
		Node<T>* temp = head;
		T* ret = temp->getData();
		head = head->getNext();
		delete temp;
		return ret;
    }
/*
    pop2 sets data pointer to NULL
    in order not to destroy this object.
    Returns data* of the deleted node.
    !!!!!!USE THIS WITH STD TYPES!!!!!
*/
    
    T* pop2(){
       if(head == NULL){ //if our list is currently empty
            //EMPTY LIST
            return NULL;
        }
        
        counter--;
        Node<T>* temp = head;
        T* ret = temp->getData();
        head = head->getNext();
        temp->dataNULL();
        delete temp;
        return ret;    
    }
    
    void print(){
    	Node<T>* cur = head;
    	while (cur!=NULL){
    		cur->print();
    		cur = cur->getNext();
    	}
    }

    void writefile(FILE * fptr2){
    	Node<T>* cur = head;
    	T* data2;
    	while (cur!=NULL){
    		data2 = cur->getData();
    		fprintf(fptr2,"(%d,%d) (%d,%d) \n",data2->start_x,data2->start_y,data2->end_x,data2->end_y);
    		cur = cur->getNext();
    	}
    }
    /*
        Search list for specific info
        if found return specific list node
        else rerurns NULL.
        Used by Hashtable
    */
    Node<T> * search(T* info){
       Node<T>* cur = head;
        while (cur!=NULL){                  //parse list
            if(info == cur->getData()){
                return cur;
            }
            cur = cur->getNext();           //step
        }
        return NULL;
    }
/*
	Add ndlist info to the end of current list
*/
    void concat(Lista<T> * ndlist){
    	Node<T> * temp_node;
    	temp_node = ndlist->getHead();
    	T* info;
    	while(temp_node!=NULL){
    		info = temp_node->getData();
    		this->push(info);
    		temp_node = temp_node->getNext();
    	}
    }

};
#endif