#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "newlist.h"
#include "Map.h"
#include "Trie.h"
#include <cmath>
#include "Heap.h"
#include "Utils.h"
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;


int main(int argc ,char * argv[]){
	//command line arguments
	char finput[32];			//var to store input files name
	int k;						//var to store max returned results
	if(argc != 5 ){
		cout<<"error wrong number of arguments "<<endl;
		return 1;
	}
	else{
		for (int i=1;i<argc;i++){
			if(strcmp(argv[i],"-i")==0){	//case -i 
				strcpy(finput,argv[i+1]);
			}
			if(strcmp(argv[i],"-K")==0){	//case -K
				k = atoi(argv[i+1]);
				if(k<0){
					cout<<"error k<0"<<endl;
					return 1;
				}
			}
		}
	}
	//end of command line arguments
	FILE * fptr = fopen(finput,"r");
	if(fptr==NULL){
		cout<<"ERROR opening file"<<endl;
		return 1;
	}
	Map new_map;				//Our map data structure
	Trie new_trie;				//Our trie data structure
	char*  buffer2=NULL;		//used by getline
	size_t len = 0;				//used by getline
	/*
		Read from file
	*/
	CLista * file_list;
	long int read;
	long long int number_of_lines=0;
	long long int total_words=0;
	while(read=getline(&buffer2,&len,fptr)!=-1){
		file_list = new CLista();
		parse_file(buffer2,file_list);
		total_words = total_words + file_list->get_size();
		if(file_list->get_size()!=0){						//+++++++++++++++++++
			number_of_lines++;								//+++++++++++++++++++
			if(new_map.add(buffer2,len,file_list)==NULL){	//insert to map
				cout<<"ids not in order"<<endl;
				free(buffer2);					//case ids not in order					
				fclose(fptr);					//free memory,close files
				free(file_list);
				return 1;						//and return 
			}
			new_trie.insert(file_list);					//inserto to trie
		}
		delete file_list;
	}
	free( buffer2);				//free space allocated from getline function
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

	//new_map.print();			//use to print map
	//new_trie.print();			//use to print trie

	CLista * word_list;			//used to store all words from a line
	char*  buffer=NULL;			//used by getline
	len = 0;					//used by getline
	char * popped;				//stores data popped from Clista
	Heap_array * new_heap;		//Our heap data structure
	double score;				//store score here
	double avgdl;				//store average number of words per id
	avgdl = double(total_words)/double(number_of_lines); //+++++++++++++++
/*
	READ FROM STDIN
*/
	cout<<"try /search, /df , /tf or /exit to leave"<<endl; 
	while(read=getline(&buffer,&len,stdin)!=-1){
		if(strcmp(buffer,"/exit\n")==0)			//exit case
			break;
		word_list = new CLista();
		parse_words(buffer,word_list);
		Lista<Score_node> * score_list;
		if(strcmp(word_list->get_head()->get_data(),"/search")==0){		//search case
			cout<<"search case "<<endl;
			popped = word_list->pop();			//pop "/search" from list
			if(popped!=NULL){
				delete [] popped;
			}
			score_list = new_trie.search(word_list);
			if(score_list!=NULL){
				new_heap = new Heap_array();
				Node<Score_node> * current_score;
				Node<Posting_node> * current_posting;
				int x= 0;
				current_score = score_list->getHead();
				while(current_score!=NULL){
					current_posting = current_score->getData()->posting_list->getHead();
					while(current_posting!=NULL){
						score = calc_score(number_of_lines,current_score->getData()->posting_list->get_counter(),
							current_posting->getData()->frequency,total_words,avgdl);//calculate score
						//cout<<"before insert heap key "<<current_posting->getData()->id<<" score "<<score<<endl;
						new_heap->insert(current_posting->getData()->id,score);	//insert to heap
						current_posting = current_posting->getNext();
					}
					current_score = current_score->getNext();
				}
				Heap_array_node * heap_max;
				long long int print_id;
				for (int i=0;i<k;i++){
					heap_max = new_heap->pop();
					if(heap_max == NULL){
						break;
					}
					print_id = heap_max->key;
					cout<<"("<<print_id<<") ";
					cout<<"["<<heap_max->score<<"] ";
					cout<<*new_map.get_array()[print_id].document;//+++++++++++++++++++++++++++++++++++++
					cout<<"\n\n\n";	
					delete heap_max;
				}
			}
			if(score_list!=NULL){
				//score_list->print();
				delete(score_list);
			}
			delete new_heap;

		}
		else if(strcmp(word_list->get_head()->get_data(),"/df")==0){	//df case
			cout<<"df case"<<endl;
			popped=word_list->pop();			//pop "/df" from list
			if(word_list->get_size()==0){		//print all words
				new_trie.print();
			}
			else{
				char * popped2;
				popped2 = word_list->pop();
				Lista<Posting_node> * posting = new_trie.word_search(popped2);
				cout<<popped2<<" "<<posting->get_counter()<<endl;
				delete[] popped2;

			}
			if(popped!=NULL){
				delete [] popped;
			}
		}
		else if(strcmp(word_list->get_head()->get_data(),"/tf")==0){ 	//tf case
			cout<<"tf case"<<endl;
			popped = word_list->pop();			//pop "/tf" from list
			if(popped!=NULL){
				delete [] popped;
			}
			char * popped2 = word_list->pop();
			if(popped2!=NULL){
				long long int to_id = atoll(popped2);
				delete [] popped2;
				char * popped3 = word_list->pop();
				if(popped3!=NULL){
					Lista<Posting_node> * posting = new_trie.word_search(popped3);
					if(posting !=NULL){
						Node<Posting_node> * posting_node = posting->getHead();
						while(posting_node!=NULL){
							if(posting_node->getData()->id == to_id){
								cout<<to_id<<" "<<popped3<<" "<<posting_node->getData()->frequency<<endl;
							}
							posting_node = posting_node->getNext();
						}
					}
					delete [] popped3;
				}
			}
		}
		else{
			cout<<"ERROR wrong input please try again"<<endl;
			cout<<"try /search, /df , /tf or /exit to leave"<<endl;
			continue;
		}
		cout<<"try /search, /df , /tf or /exit to leave"<<endl;
		//word_list->popall2();
		delete word_list;

	}
	free(buffer);
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
	fclose(fptr);
	return 0;
}