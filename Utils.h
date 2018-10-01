#ifndef UTILS_H
#define UTILS_H
struct Word_positions{
	char* start;
	int size;
};
double calc_IDF(long long int,long long int);
double calc_score(long long int,long long int,long long int,long long int,double);
void parse_words(char *, CLista *);
int is_letter(char);
void parse_file(char *, CLista *);
Word_positions * find_pos(char *  ,char * );
void search_print(char * ,char * ,int,Lista<Score_node> *);

#endif