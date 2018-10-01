#ifndef NEWLIST_H
#define NEWLIST_H
#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
class List_node {
		List_node * next;
		List_node * prev;
		char *  data;
	public:
		List_node(char* to_data,int);
		~List_node();

		void set_next(List_node * to_next){next = to_next;}
		void set_data(char* to_data){data = to_data;}
		void set_prev(List_node * to_prev){prev = to_prev;}

		List_node * get_next(){return next;}
		char* get_data(){return data;}
		List_node * get_prev(){return prev;}

		void print(){cout<<data<<" ";}
};

class CLista{
		List_node * head;
		List_node * tail;
		long long int size;
	public:
		CLista();
		~CLista();

		void set_head(List_node* to_head){head = to_head;}
		void set_tail(List_node* to_tail){tail = to_tail;}
		void set_size(long long int to_size){size = to_size;}
		void inc_size(){size++;}
		void dec_size(){size--;}

		List_node * get_head(){return head;}
		List_node * get_tail(){return tail;}
		long long int get_size(){return size;}

		List_node * push(char * , int );
		char * pop();
		void print();
		
};


#endif