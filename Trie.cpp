#include "Trie.h"

using namespace std;
/*
	Trie_list_node class functions
*/

Trie_list_node::Trie_list_node(char to_letter){
	letter = to_letter;
	children = NULL;
	posting_list  = NULL;
	//cout<<"Trie_list_node const"<<endl;
}

Trie_list_node::~Trie_list_node(){
	if(children!=NULL){
		delete children;
	}
	if(posting_list!= NULL){
		delete posting_list;
	}
	//cout<<"Trie_list_node dest"<<endl;
}
/*
	Searches Posting list for specific id returns list node
	on success or else NULL 
*/
Node<Posting_node> * Trie_list_node::search_p_list(long long int to_id){
	if (posting_list == NULL)		//list is empty
		return NULL;			
	Node<Posting_node> * temp = posting_list->getHead();
	Posting_node * data;
	while(temp != NULL){			//parse list
		data = temp->getData();
		if(data->id == to_id){		//id found
			return temp;
		}
		temp=temp->getNext();		//step
	}
	return NULL;				//parsed all the list without
}								//finding id
/*
void Trie_list_node::print(char * word){
	cout<<letter;
	if(posting_list!= NULL){
		cout<<" "<<posting_list->get_counter()<<endl;
	}
	
	if(children!=NULL){
		//children->print("");
	}
}
*/
/*******************************************/
/*
	Trie Node class functions
*/

Trie_node::Trie_node(){
	lnode = NULL;
	//cout<<"trie_node const"<<endl;
}

Trie_node::~Trie_node(){
	if (lnode != NULL){
		delete lnode;
	}
	//cout<<"trie_node dest"<<endl;
}
/*
	Returns Node<Trie_list_node> which has the specific
	char let or Null on faillure
*/
Node<Trie_list_node> * Trie_node::search_let(char let){
	if(lnode==NULL)			//list is empty
		return NULL;
	Node<Trie_list_node> * temp = lnode->getHead();
	Trie_list_node * data;
	while(temp != NULL){			//parse list
		data = temp->getData();
		if(data->get_letter()== let){	//letter found
			return temp;
		}
		temp=temp->getNext();		//step
	}
	return NULL;				//parsed all the list without
}								//finding let
/*
	Insert a word with an id. This function always takes the first letter
	of the word and checks if it is found at the root of the trie.
	Then it calls itself for the children of the trie with next letter(word+1).

*/
void Trie_node::insert(char * word,long long int to_id){
	if(word[0]== '\0'){
		//end of word
		cout<<"\nERROR\n";
	}

	else{
		//cout<<"word "<<word<<endl;
		if(lnode == NULL){
			lnode = new Lista<Trie_list_node>();
		}
		//cout<<"word "<<word<<" word[0] "<<word[0]<<endl;
		Node<Trie_list_node> * temp;
		temp = this->search_let(word[0]);					//search the list for word[0]
		if(temp == NULL){								//Not found in this level
			Trie_list_node * new_letter;				//create a new Trie_list_node
			new_letter = new Trie_list_node(word[0]);	//++++++++++++++++++++++++++
			temp=lnode->push(new_letter);				//push this letter into the list
		}
		if(word[1]!='\0'){								//Not the end of word 
			if(temp->getData()->get_children()== NULL){
				Trie_node * temp_children;
				temp_children = new Trie_node();			//create new empty Trie_node
				temp->getData()->set_children(temp_children);//point to children to new empty Trie_node
				//temp_children->set_parent(this);
				//temp_children->set_parent_list_node(temp->getData());			
			}
			temp->getData()->get_children()->insert(word+1,to_id);
		}
		else{											//end of word
			Lista<Posting_node> * temp_p_list;
			temp_p_list = temp->getData()->get_posting_list();
			if(temp_p_list == NULL){							//not found before
				temp_p_list = new Lista<Posting_node>();
				temp->getData()->set_posting_list(temp_p_list);
				Posting_node * temp_p_node;
				temp_p_node = new Posting_node;
				temp_p_node->id = to_id;					
				temp_p_node->frequency = 1;
				temp_p_list->push(temp_p_node); 
			}
			else{//found before search if id already exists
				Node<Posting_node> * spec_node;				//spec_node(specific node) of posting list
				spec_node = temp->getData()->search_p_list(to_id);//where id was found or NULL else
				if(spec_node == NULL){					//list is not empty but id wasnt found
					//this means that this word has been previously found but not with this id.
					Posting_node * temp_p_node;
					temp_p_node = new Posting_node;
					temp_p_node->id = to_id;
					temp_p_node->frequency = 1;
					temp_p_list->push(temp_p_node);
				}
				else{//case multiple same words with same id
					//increase frequency only.
					Posting_node * data = spec_node->getData();
					data->frequency = data->frequency + 1;
				}
			}
		}
	}
}

void Trie_node::print(char * word,int i){
	//cout<<"i "<<i<<endl;
	Node<Trie_list_node> * cur =lnode->getHead();
	while(cur!=NULL){
		word[i] = cur->getData()->get_letter();
		if(cur->getData()->get_posting_list()!=NULL){
			word[i+1] = '\0';
			cout<<word;
			cout<<" "<<cur->getData()->get_posting_list()->get_counter()<<endl;	
		}
		if(cur->getData()->get_children()!=NULL){
			cur->getData()->get_children()->print(word,i+1);
		}
		//cout<<"here"<<endl;
		cur= cur->getNext();	//step
	}
}

/*******************************************/
/*
	Trie class functions
*/

Trie::Trie(){
	root = NULL;
	//cout<<"trie const"<<endl;
}

Trie::~Trie(){
	delete root;
	//cout<<"trie dest"<<endl;
}

void Trie::insert(CLista * clist){
	if(root == NULL){			//empty trie
		root = new Trie_node();
	}
	List_node* temp;
	temp = clist->get_head();
	if(temp==NULL)
		return;
	long long int to_id;
	to_id = atoll(temp->get_data());
	temp=temp->get_next();
	while(temp!= NULL){
		//cout<<"Trie::insert "<<temp->get_data()<<endl;
		root->insert(temp->get_data(),to_id);
		temp=temp->get_next();
	}
	
}

void Trie::print(){
	char * word;
	word = new char[128];
	root->print(word,0);
	delete[] word;
}

Lista<Posting_node> * Trie::word_search(char *word){
	int i =0;
	Trie_node * temp_node = root;
	Node<Trie_list_node> * temp_list_node;
	while(word[i]!='\0'){
		temp_list_node = temp_node->search_let(word[i]);
		if(temp_list_node==NULL)
			return NULL;
		temp_node = temp_list_node->getData()->get_children();
		i++;
	}
	return temp_list_node->getData()->get_posting_list();
}

Lista<Score_node> * Trie::search(CLista * words_list){
	if(words_list == NULL)
		return NULL;
	List_node * temp_node = words_list->get_head();
	int temp_counter = 1;
	Lista<Posting_node> * plist;
	Lista<Score_node> * return_list;
	return_list = new Lista<Score_node>();
	Score_node * temp_score_node;
	//delete return_list;
	while(temp_node!=NULL&&temp_counter<=10){		//parse <=10 list nodes
		plist = word_search(temp_node->get_data());
		if(plist!=NULL){
			temp_score_node = new Score_node;
			temp_score_node->word = temp_node->get_data();
			temp_score_node->posting_list = plist;
			return_list->push(temp_score_node);
		}
		temp_node = temp_node->get_next();			//step
		temp_counter ++;									//step
	}
	return return_list;
}