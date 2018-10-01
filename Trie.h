#ifndef TRIE_H
#define TRIE_H
#include "List.h"
#include "newlist.h"
class Trie_node;

struct Posting_node{
	long long int id;
	int frequency;
	void print(){cout<<"[id "<<id<<" frequency "<<frequency<<"]";}
};
struct Score_node{
	Lista<Posting_node> * posting_list;
	char * word;
	void print(){cout<<" word "<<word;posting_list->print();}
};
class Trie_list_node{
		char letter;
		Trie_node * children;
		Lista<Posting_node> * posting_list;
	public:
		Trie_list_node(char);
		~Trie_list_node();

		void set_letter(char to_letter){letter = to_letter;}
		void set_children(Trie_node * to_children){children = to_children;}
		void set_posting_list(Lista<Posting_node> * to_set){posting_list = to_set;}

		char get_letter(){return letter;}
		Trie_node * get_children(){return children;}
		Lista<Posting_node> * get_posting_list(){return posting_list;}
		Node<Posting_node> * search_p_list(long long int);
		//void print(char *,i);
};

class Trie_node{
		Lista<Trie_list_node> * lnode;
	public:
		Trie_node();
		~Trie_node();

		void set_lnode(Lista<Trie_list_node> * to_lnode){lnode = to_lnode;}

		Lista<Trie_list_node> * get_lnode(){return lnode;}

		Node<Trie_list_node> * search_let(char);
		void insert(char *,long long int);
		void print(char *,int);
	//	void print_word(char,Trie_node*);
		//void df();
};

class Trie{
		Trie_node * root;
	public:
		Trie();
		~Trie();

		void set_root(Trie_node * to_root){root = to_root;}

		Trie_node * get_root(){return root;}
		Lista<Posting_node> * word_search(char *);
		Lista<Score_node> * search(CLista *);
		void insert(CLista *);
		void print();
		//void df();
};

#endif