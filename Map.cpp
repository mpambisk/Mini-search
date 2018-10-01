#include "Map.h"
#include <cstdlib>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
Map::Map(){
	size = 2;
	counter = 0;
	array = (Map_node*) malloc(size*sizeof(Map_node));
	cout<<"map const"<<endl;
 }

 Map::~Map(){
 	for(int i =0;i<counter;i++){
 		if(array[i].document!=NULL){
 			delete[] *(array[i].document);
 			delete array[i].document;
 		}
 	}
 	free(array);
 	cout<<"map dest"<<endl;
 }
Map_node * Map::add(char * buffer,long int bsize,CLista * to_words){
	if(counter == size){		//array is full
		this->resize();
	}
	long long int to_id;
	List_node * temp_head;
	temp_head = to_words->get_head();
	to_id = atoll(temp_head->get_data());
	if(to_id != counter){						//+++++++++++++++++++
		cout<<"ERROR ids not in correct order"<<endl;
		return NULL;
	}
	array[counter].id = to_id;
	array[counter].document = new char*;
	*(array[counter].document) = new char[bsize];
	strncpy(*(array[counter].document),buffer,bsize);
	counter ++;
	return &array[counter-1];
}

 void Map::resize(){
 	size = size * 2;
 	//cout<<"resize "<<size<<endl;
 	array = (Map_node*) realloc(array,size* sizeof(Map_node));
 }

 void Map::print(){
 	if(counter == 0){
 		cout<<"Empty map"<<endl;
 		return;
 	}
 	for(long long int i=0;i<counter;i++){
 		cout<<" "<<array[i].id<<" "<<*(array[i].document)<<"\n\n";
 	}
 }