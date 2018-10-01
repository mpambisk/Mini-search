#include "newlist.h"


List_node::List_node(char * to_data,int len){
	data = new char[32];
	strncpy(data,to_data,len);
	data[len] = '\0';
	next = NULL;
	prev = NULL;
	//cout<<"List_node const"<<endl;
}

List_node::~List_node(){
	//if (data!=NULL)
	//	delete[] data;
	//cout<<"List_node dest"<<endl;
}

CLista::CLista(){
	head = NULL;
	tail = NULL;
	size = 0;
	//cout<<"CLista const"<<endl;
}

CLista::~CLista(){
	char * temp;
	while (size > 0){
    		temp = pop();
    		//cout<<"temp "<<temp<<endl;
    		if (temp!=NULL)
    			delete [] temp;
    }
   // cout<<"CLista dest"<<endl;
}

List_node * CLista::push(char * to_data, int len){
	if(head == NULL){ //if our list is currently empty
        	size = 1;
            head = new List_node(to_data,len);
            tail = head;
    }
    else { //if not empty add to the end and move the tail
        	inc_size();
            List_node * temp = new List_node(to_data,len);
            tail->set_next(temp);
            temp->set_prev(tail);
            tail = tail->get_next();
        }
        return tail;
}

char * CLista::pop(){
	if(head == NULL){ //if our list is currently empty
        //EMPTY LIST
        return NULL;
    }
	dec_size();
	List_node* temp = head;
	char *  ret = temp->get_data();
	head = head->get_next();
	delete temp;
	return ret;
}

void CLista::print(){
	List_node * cur = head;
    while (cur!=NULL){
    	cur->print();
    	cur = cur->get_next();
    }
}
