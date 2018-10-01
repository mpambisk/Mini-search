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
using namespace std;


double calc_IDF(long long int N,long long int nqi){
	double IDF;
	IDF = log10((N-nqi+0.5)/(nqi+0.5));
	return IDF;
}
double calc_score(long long int N,long long int nqi,long long int frequency,long long int D,double avgdl){
	double score;
	score = calc_IDF(N,nqi);
	score = score * (frequency * 2.2)/(frequency + 1.2*(0.25+0.75*(D/avgdl)));
	return score;
}
void parse_words(char * buffer, CLista * word_list){
	int start_point =0;
	char * new_word;
	for(int i=0; i<strlen(buffer);i++){
		if (buffer[i] == ' '||buffer[i] == '\t' || buffer[i] == '\n' ){
			if((i!=0) && (buffer[i-1]==' ' || buffer[i-1] == '\t'))
				continue;
			new_word = new char[32];
			strncpy(new_word,buffer+start_point,i-start_point);
			word_list->push(new_word,i-start_point);
			delete [] new_word;
			//word_list->print();
			start_point =i+1;
		}
		else if(i==strlen(buffer)-1){
			new_word = new char[32];
			strncpy(new_word,buffer+start_point,(i-start_point)+1);
			word_list->push(new_word,i-start_point+1);
			delete [] new_word;
			//word_list->print();
			start_point =i+1;
		}
	}
}
int is_letter(char let){
	if(let==' '|| let == '\t')//+++++++++++++++++++
		return 0;				//+++++++++++++++++
	return 1;						//++++++++++++++++
	if(let>='A'&&let<='Z')
		return 1;
	if(let>='a'&&let<='z')
		return 1;
	if(let>='0' && let<='9')
		return 1;
	//if(let ==39){			//ASCII CODE FOR '
		//return 1;
	//}
	return 0;
}
void parse_file(char * buffer, CLista *word_list){
	int start_point = -1;
	int end_point = 0;
	int j=0;
	char * temp_word;
	for (int i=0;i<strlen(buffer);i++){
		if (is_letter(buffer[i])==1){
			if(i==0)
				start_point = 0;
			else{
				if(is_letter(buffer[i-1])==0){
					start_point =i;
				}
			}
		}
		else{
			if(start_point == -1){
				continue;
			}
			else{
				if(is_letter(buffer[i-1])==1){
					end_point = i;
					temp_word = new char[32];
					strncpy(temp_word,buffer+start_point,end_point-start_point);
					temp_word[end_point-start_point] = '\0';
					word_list->push(temp_word,end_point-start_point);
					delete [] temp_word;
				}
			}
		}
	}
}
Word_positions * find_pos(char * buffer ,char * to_search){
	Word_positions * new_word_pos;
	new_word_pos = new Word_positions;
	new_word_pos->start = strstr(buffer,to_search);
	if (new_word_pos->start ==NULL){
		cout<<"ERROR"<<endl;
		delete new_word_pos;
		return NULL;
	}
	new_word_pos->size = strlen(to_search);
	return new_word_pos;
}
void search_print(char * buffer ,char * doc ,int col,Lista<Score_node> * score_list){
	char pows[64];
	strcpy(pows,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\0");
	char * temp;
	int step=0;
	while(step<=strlen(doc)){
	temp = new char[col*2];
		Node<Score_node> * cur;
		cur = score_list ->getHead();
		strncpy(temp,doc+step,col);
		//Lista<Word_positions> * pos_list;
		//pos_list = new Lista<Word_positions>();
		Word_positions * temp_pos;
		while(cur!=NULL){
			temp_pos = find_pos(temp,cur->getData()->word);
			if(temp_pos !=NULL){
				strncpy(temp_pos->start + col,pows,temp_pos->size);
				cout<<"temp_pos "<<temp_pos->start+col<<endl;
				delete temp_pos;
			}
			cur = cur->getNext();
		}
		strncpy(buffer+step,temp,col*2);
		delete temp;
		step = step + col;
	}

}