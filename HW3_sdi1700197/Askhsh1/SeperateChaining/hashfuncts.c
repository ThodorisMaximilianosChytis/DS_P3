#include <stdio.h>
#include <stdlib.h>
#include "hashfuncts.h"
#include <string.h>


int M = 7;						//array size

HashTable HTCreate(void){			//Creating the Hashtable
	int i; 
	HashTable HT  = malloc(sizeof(HTNode) * M);		//Dynamic memory allocation 
	for (i=0 ; i< M ; i ++){
		HT[i] = NULL;								//Initialize Hash
	} 
	return HT;
}

int HTSize(HashTable HT){			//Get Hash size
	int i, count = 0 ; 
	HTNode temp; 
	for (i = 0 ; i < M ; i++){			//Access Hashtable
		temp = HT[i]; 
		while (temp != NULL){			//Access Nodes in the Chain-List (seperate chaining)
			count ++ ; 
			temp = temp->next; 			//next
		}
	}
	return count; 
}

int HashFunction(char * key ){				//My Hashfunction
	int a=M+1, i ;
	int hash = 0;
	for (i=0 ; i <=strlen(key) ; i++ ){
		hash = (a * hash + (unsigned int) key[i] ) % M;		//get an hash code deriving from each character of the string (the position is the power)
	}
	return (hash % M); 		//get an allowed code 
}


HashTable HTInsert(HashTable HT,char * Key,HTitem Item ){			//Insert new item into the hash
	HTNode tbinserted = malloc (sizeof(HTHash));		
	tbinserted->key = Key;
	tbinserted->item = Item;
	tbinserted->next = NULL;
	int index = HashFunction(Key);			//get hash code - index
	printf("index is  %d\n", index);
	if (HT[index]==NULL){			//NO Collision
		HT[index] = tbinserted;		//Insert
		HT[index]->next = NULL;
	}
	else{ 			//Collision
		HTNode temp =  HT[index];
			while (temp->next!=NULL && strcmp(temp->key,Key)!=0){			//Iterate the List of this index 
				temp = temp ->next;
			}
		if (strcmp(temp->key,Key)==0){				//Item already exist just update it
			temp->item = Item;
			free (tbinserted);
		}else{
			temp->next = tbinserted;			//Seperate chaining // Insert into the list
		}
	} 
	int N = HTSize(HT);
	if ((float)N/M >= 0.9)	{
		printf("rehashing\n");			//The load factor is the number of keys stored in the hash table divided by the capacity. 
		HTRehashing(&HT);				//rehash the table
	}
	return HT;						
}

void HTRehashing(HashTable *HT){
	M = M << 1;			//multiply by 2
	HashTable NHT = HTCreate();
	M = M >> 1;			//get half
	
	int i=0, count=0;
	int size = HTSize(*HT);
	HTNode temp;
	while (i < M && count < size){
		temp = (*HT)[i];
		while (temp!=NULL){
			count++;
			M = M << 1;
			HTInsert(NHT,temp->key,temp->item);			//Copy into new Hash
			M = M >> 1;
			temp = temp -> next;
		}	
		i++;
	}
	HTDestroy(*HT);					//Destroy - Delete old HashTable
	*HT = NHT;
	M = M << 1 ;
}	
	


int HTGet(HashTable HT , char * Key, HTitem * pitem){			//Get the item of a Node with a gine key
	int i= 0 , count = 0;
	HTNode temp;
	int index = HashFunction(Key);						//Get index
	temp = HT[index];	
	while (temp!= NULL){
		if (strcmp(temp->key,Key)==0){				//If found in the Chain
			* pitem = temp->item;			//updte pitem
			return 1;						//succesful search
		}
		temp = temp->next;
		count++ ;
	}
	return 0;			//unsuccesful search
}



void HTRemove(HashTable HT, char * Key ){				//Remove a single Node from the Hash
	int i= 0 , count = 0;
	HTNode temp, problemsolver;						
	int index = HashFunction(Key);
	if (HT[index] != NULL ){
		count++;
		problemsolver = HT[index] ->next;				//always keep the Node next so that you can Link
		if (strcmp(HT[index]->key,Key)==0){
				free(HT[index]);						//delete Node
				HT[index] = problemsolver;				//Link Chain
		}
		else{
		temp = HT[index];
			while (temp->next!= NULL){								//Iterate to find the Node
				count++ ;
				if (strcmp(temp->next->key,Key)==0){	
					problemsolver = temp->next->next;	
					free(temp->next);				//delete Node
					temp->next = problemsolver;		//Link Chain
					break;
				}
				temp = temp->next;
			}
		}
	}
}



void HTDestroy(HashTable HT){				//Delete te whole Hash
	int i= 0 , count = 0;
	HTNode  temp;	
	int size = HTSize(HT);
	for (i = 0 ; i < M ; i++){
		if (HT[i]!=NULL){
			temp = HT[i];
			while (temp!=NULL){
				HTRemove(HT,temp->key);
				temp = temp->next;	
			}
		}
	}
}


void HTVisit(HashTable HT, void  (*Visit)(HashTable  HT, char * Key, HTitem Item))	{		// Does what the *visit demands for all Nodes
	int i=0, count=0;
	int size = HTSize(HT);
	HTNode temp;
	while (i < M && count < size){
		temp = HT[i];
		while (temp!=NULL){
			count++;
			Visit(HT,temp->key,temp->item);				//Call visit which is passed as an argument
			temp = temp -> next;
		}	
		i++;
	}
}

void HTPrintItemValues(HashTable HT, char* Key, HTitem Item ){			//Prints the Key
	printf("This node's item value is %s\n",Key);
}



