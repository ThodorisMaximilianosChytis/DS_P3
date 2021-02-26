#include <stdio.h>
#include <stdlib.h>
#include "hashfuncts.h"
#include <string.h>


int M = 9;

HashTable HTCreate(void){				//create hashtable
	int i; 
	HashTable HT  = malloc(sizeof(HTNode) * M);
	for (i=0 ; i< M ; i ++){
		HT[i] = NULL;
	} 
	return HT;
}

int HTSize(HashTable HT){			//get the size
	int i, count = 0 ; 
	HTNode temp; 
	for (i = 0 ; i < M ; i++){
		if (HT[i]!=NULL)
		count++;
	}
	return count; 
}

int HashFunction(char * key ){
	int a=M+1, i ;
	int hash = 0;
	for (i=0 ; i <=strlen(key) ; i++ ){
		hash = (a * hash + (unsigned int) key[i] ) % M;
	}
	return (hash % M); 
}


HashTable HTInsert(HashTable HT,char * Key,HTitem Item ){			//Insert a new Node into the HashTable with open adressing
	HTNode tbinserted = malloc (sizeof(HTHash));
	
	
	tbinserted->key = Key;
	tbinserted->item = Item;
	
	int index = HashFunction(Key);			//get hash code-index
	
	
	while (HT[index]!=NULL){			//Collision
		index += 1;
		if (index>=M) index = index - M ;			//Get correct position to avoid out of bounds
	}
		printf("index is  %d\n", index);

	
	HT[index] = tbinserted;			//Insert Node with Open adressing method
	
	
	int N = HTSize(HT);
	if ((float)N/M >= 0.5)	{
		printf("rehashing\n");			//The load factor is the number of keys stored in the hash table divided by the capacity. 
		HTRehashing(&HT);			//rehashing
	}
	return HT;						
}

void HTRehashing(HashTable *HT){
	M = M << 1;
	HashTable NHT = HTCreate();
	M = M >> 1;
	
	int i=0;
	int size = HTSize(*HT);
	for (i=0; i < M; i++){
		M = M << 1;
		if ((*HT)[i]!=NULL)
			HTInsert(NHT,(*HT)[i]->key,(*HT)[i]->item);			//Copy into new Hashtable
		M = M >> 1;
	}
	HTDestroy(*HT);
	*HT = NHT;
	M = M << 1 ;
}	
	


int HTGet(HashTable HT , char * Key, HTitem * pitem){			//Get item of a Node
	int i= 0, count=0 ;
	int size = HTSize(HT);
	int index = HashFunction(Key);
	while (size>count){
		if (HT[index]!=NULL){		//iterate Hash
			count++;
			if (strcmp(HT[index]->key,Key)==0){		//item found?
					* pitem = HT[index]->item;		//update pitem
					return 1;
			}
		}
		index += 1;		//search for item in the next array bracket
		if (index>=M) 			//get correct index avoiding to get out of bounds
			index = index - M ;
	}
	* pitem = -999;
	return 0;
}



void HTRemove(HashTable HT, char * Key ){				//Remove single item from the hash
	int i= 0, count=0 ;
	int size = HTSize(HT);
	int index = HashFunction(Key);
	while (size>count){
		if (HT[index]!=NULL){
			count++;
			if (strcmp(HT[index]->key,Key)==0){
					free(HT[index]);			//delete Node
					HT[index] = NULL;			//update to NULL
					return;
			}
		}
		index += 1;
		if (index>=M) 
			index = index - M ;
	}
}



void HTDestroy(HashTable HT){			//Destroy the whole HASH
	int i;
	for (i=0; i< M ; i++){
		if (HT[i]!=NULL){
			printf(" I is %d\n", i);	
			free(HT[i]);	///DELETE NODE
			HT[i]=NULL;	
		}
		free(HT);		//delete hash
	}
	
}


void HTVisit(HashTable HT, void  (*Visit)(HashTable , char * ,HTitem ))	{			//does a certain thing(Visit for eiach Node of the Hash
	int i;
	for (i=0; i< M ; i++){
		if (HT[i]!=NULL){
			Visit(HT,HT[i]->key,HT[i]->item);			//call visit
		}
	}
}
		
void HTPrintItemValues(HashTable HT, char* Key, HTitem Item ){			//Print item
	printf("This node's item value is %d\n",Item);
}
			
	

