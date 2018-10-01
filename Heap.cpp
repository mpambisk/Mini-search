#include "Heap.h"
#include <cmath>
#include <iostream>
#include <cstring>
#include "List.h"

using namespace std;

Heap_node::Heap_node(long long int tokey,double tovalue,Heap_node * toparent=NULL){
	left_child = NULL;
	right_child = NULL;
	parent = toparent;
	key =tokey;
	//cout<<"new heap node key = "<<key<<endl;
	value=tovalue;
	//cout<<"Heap node constructor"<<endl;
}

Heap_node::~Heap_node(){
	//cout<<"Heap node destructor"<<endl;
}

Heap::Heap(){
	root=NULL;
	height=-1;
	node_count=0;
//	cout<<"Heap constructor"<<endl;
}
Heap::~Heap(){
	if(root!=NULL)
		hdelete(root);
	//cout<<"Heap destructor"<<endl;
}



void Heap::hdelete(Heap_node * temp){
	if(temp->get_left_child()!=NULL)
		hdelete(temp->get_left_child());
	if(temp->get_right_child()!= NULL)
		hdelete(temp->get_right_child());
	delete temp;
}

/*
	Prints complete tree ending line when 
	height changes. At the top height 0
	to max height. | after nodes that have the same 
	parent
*/
void Heap::print(){
	cout<<"Height = "<<height<<endl;
	if(root==NULL)
		return;
	Lista<Heap_node> * mylist;
	mylist=new Lista<Heap_node >;
	Lista<Heap_node> * mylist2;
	mylist2=new Lista<Heap_node>;
	Heap_node * temp;
	mylist->push(root);
	temp=root;
	for(int i=0;i<=height;i++){
		int j=0;
		while(mylist->get_counter()>0){
			Heap_node * htemp=mylist->pop2();
			j++;
			if(htemp->get_left_child()!=NULL)
				mylist2->push(htemp->get_left_child());	
			if(htemp->get_right_child()!=NULL)
				mylist2->push(htemp->get_right_child());
			if(htemp!=NULL)
				cout<<" "<<(htemp->get_key())<<" ";
			if(j==2){
				cout<<"|";
				j=0;
			}
		}
		cout<<endl;
		Lista <Heap_node> * temp3;
		temp3=mylist;
		mylist=mylist2;
		mylist2=temp3;
	}
	delete mylist;
	delete mylist2;

}

void Heap::swap(Heap_node * child, Heap_node * par){
	if(par==NULL){
		return;
	}
	if(child==NULL){
		return;
	}
	Heap_node * child_left_child = child->get_left_child();
	Heap_node * child_right_child = child->get_right_child();
	Heap_node * par_parent=par->get_parent();
	Heap_node * par_left_child = par->get_left_child();
	Heap_node * par_right_child = par->get_right_child();
	if(par_parent!=NULL){
		if(par_parent->get_right_child()== par){
			par_parent->set_right_child(child);
			child->set_parent(par_parent);
		}
		else if(par_parent->get_left_child() == par){
			par_parent->set_left_child(child);
			child->set_parent(par_parent);
		}
	}
	else{
		root=child;
		child->set_parent(NULL);
	}
	if(child_left_child!=NULL)
		child_left_child->set_parent(par);
	if(child_right_child!=NULL)
		child_right_child->set_parent(par);
	// ta meataksi tous twra
	if(par->get_right_child() == child){			//					par
		par->set_left_child(child_left_child);		//par-right_c				 	child
		par->set_right_child(child_right_child);
		child->set_left_child(par_left_child);
		child->set_right_child(par);
		par->set_parent(child);
		if(par_left_child!=NULL){
			par_left_child->set_parent(child);
		}
	}
	else if(par->get_left_child() == child){
		par->set_left_child(child_left_child);
		par->set_right_child(child_right_child);
		child->set_right_child(par_right_child);
		child->set_left_child(par);
		par->set_parent(child);
		if(par_right_child!=NULL)
			par_right_child->set_parent(child);
	}
}

void Heap::sort(Heap_node * newnode){
	Heap_node * par = newnode->get_parent();
	if(par==NULL)
		return;
	if(newnode->get_value() > par->get_value()){
		swap(newnode,par);
		sort(newnode);
	}
}
/*
	Heap::insert adds nodes left to right top to bottom
*/
Heap_node * Heap::insert(long long int tokey,double tovalue){
	Heap_node * temp;
	if(root==NULL){									//empty tree
		temp = new Heap_node(tokey,tovalue);
		root=temp;
		height=0;
		node_count=1;
		return temp;
	}
	else{											//not empty
		Heap_node * temp2, *tempparent;
		uint32_t max_nodes = pow(2,height+1)-1;
		if(node_count==max_nodes){						//full tree
			temp2 = root;
			while(temp2->get_left_child()!=NULL){		//go to the bottom left node
				temp2=temp2->get_left_child();
			}
			temp = new Heap_node(tokey,tovalue,temp2);	//create node and set parent temp2 node
			temp2->set_left_child(temp);				//set  temp2 left child temp(new node)
			height++;									//new lvl
			//print();
			sort(temp);
			return temp;


		}
		else{
			temp2 = root;
			uint32_t max_lowest = pow(2,height);			//count max number of nodes at the lowest lvl
			uint32_t empty_lowest = max_nodes - node_count;      //nodes lowest = empty spaces for nodes
		 													//at the lowest level
			uint32_t curr_lowest = max_lowest / 2 ;			//to check left or right
			while(temp2!=NULL){					
				if(empty_lowest > curr_lowest){				//left case (more empty nodes) at
					tempparent = temp2;						//the lowest lvl than half 2^h
		 			temp2 = temp2->get_left_child();
		 			if(temp2==NULL){
		 				temp2 = new Heap_node(tokey,tovalue,tempparent);
		 				tempparent->set_left_child(temp2);
		 				break;
		 			}
		 			empty_lowest=empty_lowest-curr_lowest;	//change empty_lowest and curr_lowest
		 			curr_lowest=curr_lowest / 2;			//for half lowest lvl
				}
				else{										//right case
					tempparent = temp2;
					temp2 = temp2->get_right_child();
					if(temp2==NULL){
						temp2 = new Heap_node(tokey,tovalue,tempparent);
						tempparent->set_right_child(temp2);
						break;
					}
					curr_lowest=curr_lowest / 2;			//only need to change curr_lowest
				}
			}
			root->set_parent(NULL);							//???????
			Heap_node * tempn =root;
			sort(temp2);
		}

		node_count++;
		return temp2;
	}
}

Heap_node *  Heap_node::update(double toadd){
	value = value +toadd;
	return this;
}/*
Heap_node *Heap::pop(){
	if(root==NULL)
		return NULL;
	if(node_count==1){
		return root;
	}
	Heap_node * temp_root = root;
	Heap_node * root_left = root->get_left_child();
	Heap_node * root_right = root->get_right_child();

}*/

Heap_array_node::Heap_array_node(long long int to_key,double to_score){
	key = to_key;
	score = to_score;
}
Heap_array::Heap_array(){
	size = 0;
	counter= 0;
	height = -1;
	array = NULL;
	cout<<"Heap_array const"<<endl;
}
Heap_array::~Heap_array(){
	if(array!=NULL){
		for(int i=0;i<counter;i++)
			delete array[i];
		free(array);
 	}
 	cout<<"Heap_array dest"<<endl;
}

long long int Heap_array::search(long long int search_key){
	for(int i=0;i<counter;i++){
		if(array[i]->key==search_key)
			return i;
	}
	return -1;
}

void Heap_array::resize(){
	height++;
	size = size + pow(2,height);
	array = (Heap_array_node**)realloc(array,size * sizeof(Heap_array_node*));
}
void Heap_array::halve(){
	//cout<<"halve"<<endl;
	size = size - pow(2,height);
	array = (Heap_array_node**)realloc(array,size * sizeof(Heap_array_node*));
	height--;
}
void Heap_array::swap(long long int child,long long int parent){
	Heap_array_node * temp;
	temp = array[child];
	array[child] = array[parent];
	array[parent] = temp;
}
void Heap_array::sort(long long int temp_counter){
	if(temp_counter!=0){
		long long int parent_pos;
		parent_pos = (temp_counter-1)/2;
		if(array[parent_pos]->score< array[temp_counter]->score){
			swap(temp_counter,parent_pos);
			sort(parent_pos);
		}
	}
	return;
}
void Heap_array::update(long long int pos,double to_score){
	array[pos]->score = array[pos]->score + to_score;
	sort(pos);
}
void Heap_array::inv_sort(long long pos){
	long long int left_child_pos;
	long long int right_child_pos;
	left_child_pos = (pos*2) + 1;
	right_child_pos = left_child_pos + 1;
	if(left_child_pos >=counter)
		return;
	if(right_child_pos>=counter){
		if(array[left_child_pos]->score>array[pos]->score){
			swap(left_child_pos,pos);
			inv_sort(left_child_pos);
		}
		else
			return;
	}
	else{
		if(array[left_child_pos]->score>array[right_child_pos]->score){	
			if(array[left_child_pos]->score>array[pos]->score){
				swap(left_child_pos,pos);
				inv_sort(left_child_pos);
			}
			else
				return;
		}
		else{
			if(array[right_child_pos]->score>array[pos]->score){
				swap(right_child_pos,pos);
				inv_sort(right_child_pos);
			}
			else
				return;

		}
	}
}
void Heap_array::insert(long long int to_key, double to_score){
	int search_ret;
	search_ret = search(to_key);
	if(search_ret>-1){				//key already in heap
		update(search_ret,to_score);
		return;
	}
	if(counter == size){			//heap full
		this->resize();
	}
	array[counter] = new Heap_array_node(to_key,to_score);
	counter ++ ;
	sort(counter -1);
}

void Heap_array::print(){
	cout<<" heap start"<<endl;
	for (int i=0;i<counter;i++){
		cout<<" "<<array[i]->key<<" "<<array[i]->score<<endl;
	}
	cout<<"heap end"<<endl;
}

Heap_array_node * Heap_array::pop(){
	if(counter ==0)
		return NULL;
	if(counter !=1)
		swap(counter-1,0);
	Heap_array_node * to_return;
	to_return = array[counter-1];
	array[counter-1]=NULL;
	counter--;
	if(counter<= size-pow(2,height)){
		this->halve();
	}
	inv_sort(0);
	return to_return;
}