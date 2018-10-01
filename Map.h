#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "newlist.h"
using namespace std;
struct Map_node{
	long long int id;
	//CLista * words;
	char ** document;
};
class Map{
		long long int size;
		long long int counter;
		Map_node * array;
	public:
		Map();
		~Map();

		void set_size(long long int to_size){size = to_size;}
		void set_array(Map_node * to_array){array = to_array;}
		void set_counter(long long int to_counter){counter = to_counter;}
		long long int get_size(){return size;}
		Map_node * get_array(){return array;}
		long long int get_counter(){return counter;}
		Map_node* add(char *,long int,CLista *);
		void resize();
		void print();

};


#endif