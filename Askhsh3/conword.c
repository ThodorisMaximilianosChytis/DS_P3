#include <stdio.h>
#include <stdlib.h>
#include "conword.h"
#include <string.h>
#include <limits.h>


int M = 7;

HashTable HTCreate(void){
	int i; 
	HashTable HT  = malloc(sizeof(HTNode) * M);
	for (i=0 ; i< M ; i ++){
		HT[i] = NULL;
	} 
	return HT;
}

int HTSize(HashTable HT){
	int i, count = 0 ; 
	HTNode temp; 
	for (i = 0 ; i < M ; i++){
		temp = HT[i]; 
		while (temp != NULL){
			count ++ ; 
			temp = temp->next; 
		}
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


HashTable HTInsert(HashTable HT,char * Key,HTitem Item ){
	HTNode tbinserted = malloc (sizeof(HTHash));
	tbinserted->key = Key;
	tbinserted->item = Item;
	tbinserted->next = NULL;
	int index = HashFunction(Key);
	printf("index is %d\n",index);
	if (HT[index]==NULL){
		HT[index] = tbinserted;
		HT[index]->next = NULL;
	}
	else{ 
		HTNode temp =  HT[index];
			while (temp->next!=NULL && strcmp(temp->key,Key)!=0){
				temp = temp ->next;
			}
		if (strcmp(temp->key,Key)==0){
			temp->item = Item;
			free (tbinserted);
		}else{
			temp->next = tbinserted;
		}
	} 
	int N = HTSize(HT);
	if ((float)N/M >= 0.9)	{
		printf("rehashing\n");			//The load factor is the number of keys stored in the hash table divided by the capacity. 
		HTRehashing(&HT);
	}
	return HT;						
}

void HTRehashing(HashTable *HT){
	M = M << 1;
	HashTable NHT = HTCreate();
	M = M >> 1;
	
	int i=0, count=0;
	int size = HTSize(*HT);
	HTNode temp;
	while (i < M && count < size){
		temp = (*HT)[i];
		while (temp!=NULL){
			count++;
			M = M << 1;
			HTInsert(NHT,temp->key,temp->item);
			M = M >> 1;
			temp = temp -> next;
		}	
		i++;
	}
	HTDestroy(*HT);
	*HT = NHT;
	M = M << 1 ;
}	
	


int HTGet(HashTable HT , char * Key, HTitem * pitem){
	int i= 0 , count = 0;
	HTNode temp;
	int index = HashFunction(Key);
	temp = HT[index];	
	while (temp!= NULL){
		if (strcmp(temp->key,Key)==0){
			* pitem = temp->item;
			return 1;
		}
		temp = temp->next;
		count++ ;
	}
	return 0;
}



void HTRemove(HashTable HT, char * Key ){
	int i= 0 , count = 0;
	HTNode temp, problemsolver;
	int index = HashFunction(Key);
	if (HT[index] != NULL ){
		count++;
		problemsolver = HT[index] ->next;
		if (strcmp(HT[index]->key,Key)==0){
				free(HT[index]);				
				HT[index] = problemsolver;
		}
		else{
		temp = HT[index];
			while (temp->next!= NULL){
				count++ ;
				if (strcmp(temp->next->key,Key)==0){
					problemsolver = temp->next->next;
					free(temp->next);
					temp->next = problemsolver;
					break;
				}
				temp = temp->next;
			}
		}
	}
}



void HTDestroy(HashTable HT){
	int i= 0 , count = 0;
	HTNode  problemsolver;
	int size = HTSize(HT);
	while (i < M && count < size ){
		if (HT[i] != NULL ){
			count++;
			problemsolver = HT[i] ->next;
			free(HT[i]);				
			HT[i] = problemsolver;
			i--;
		}
		i++;
	}
}


void HTVisit(HashTable HT, void  (*Visit)(HashTable  HT, char * Key, HTitem Item))	{
	int i=0, count=0;
	int size = HTSize(HT);
	HTNode temp;
	while (i < M && count < size){
		temp = HT[i];
		while (temp!=NULL){
			count++;
			Visit(HT,temp->key,temp->item);
			temp = temp -> next;
		}	
		i++;
	}
}

void HTPrintItemValues(HashTable HT, char* Key, HTitem Item ){
	printf("This node's item value is %s\n",Key);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



NodePointer Create(void){
	NodeType *N;
	N=(NodeType *)malloc(sizeof(NodeType));
	char  * A= "!!!";
	strcpy(N->item,A);
	N->Linknext=NULL;
}


void Delete(NodeType * L){
	NodeType * N, *temp;
	N=L;
	while(N!=NULL){
		temp=N->Linknext;
		free(N);
		N=temp;
	}
}


void InsertNewLastNode(LItemType A, NodeType *L)
{
    NodeType *N, *P;

    N=(NodeType *)malloc(sizeof(NodeType));
    strcpy(N->item,A);
    N->Linknext=NULL;

    while (L->Linknext != NULL) L=L->Linknext;
    L->Linknext=N;
}




void PrintList(NodeType *L, char *format)
{
      NodeType *N;
      N=L->Linknext;
      if (N==NULL)
      	return;
      printf("(");
      while(N != NULL) {
         printf(format , N->item);
         N=N->Linknext;
         if (N!=NULL) printf(",");
      }
      printf(")\n");
}



void DeleteLastNode(NodeType *L)
{
      NodeType *PreviousNode, *CurrentNode;
		
		PreviousNode=L;
     	L=L->Linknext;
     	if (L!=NULL){
	         if (L->Linknext == NULL){
	            PreviousNode->Linknext=NULL;
	            free(L);
	     	}
	        else {
	            PreviousNode=L;
	            CurrentNode=L->Linknext;
	            
	            while (CurrentNode->Linknext != NULL){
	               PreviousNode=CurrentNode;
	               CurrentNode=CurrentNode->Linknext;
	            }
	            PreviousNode->Linknext=NULL;
	            free(CurrentNode);
	        }
	    }
}


void DeleteNode(NodeType *L, NodeType * N)
{
	NodeType *PreviousNode, *CurrentNode;
	if (L->Linknext!=NULL){
		PreviousNode=L;
	    CurrentNode=L->Linknext;
		while (CurrentNode != N && CurrentNode!=NULL){
	    	PreviousNode=CurrentNode;
	        CurrentNode=CurrentNode->Linknext;
	    }
	    if (CurrentNode!=NULL){
	    	PreviousNode->Linknext=CurrentNode->Linknext;
			free(N);
		}
		else printf("Node was not found so could not be deleted\n");
	}
}



void InsertAfterNode (NodeType *L, LItemType A, NodeType *P)
{
	if (P!=NULL){
	    NodeType *N, *temp;
	    N=(NodeType *)malloc(sizeof(NodeType));
	    strcpy(N->item, A);
	    if (P->Linknext!=NULL){
	    	N->Linknext=P->Linknext;
			P->Linknext=N;
		}else{
		 	free(N);
			InsertNewLastNode(A,L);
		}
 	}
}



NodeType * ListSearch(LItemType A, NodeType *L)
{
      NodeType *N;
	  
	      N=L->Linknext;
	      while (N != NULL){
	        if (strcmp(N->item,A)==0){
	           return N;
	        } else {
	           N=N->Linknext;
	        }
	      }
	      return N;
	  
	  
}


		





			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






UGGraph UGCreate(void){
	UGGraph GR = HTCreate();
	return GR;
}




void UGAddVertex(UGGraph *GR,char * vertex){
	HTitem hitem = malloc(sizeof(HTitem*));
	hitem -> list = Create();
	
	*GR = HTInsert(*GR,vertex,hitem);
	int i;

}





void UGAddEdge(UGGraph GR,char * vertex1,char * vertex2){
	HTitem list1, list2;
	if (HTGet(GR, vertex1, &list1)==1 && HTGet(GR, vertex2, &list2)==1 ){
		InsertNewLastNode(vertex1, list2->list);
		InsertNewLastNode(vertex2, list1->list);
	}
}	


void UGRemoveEdge(UGGraph GR,char * vertex1,char *vertex2){
	HTitem list1, list2;
	if (HTGet(GR, vertex1, &list1)==1 && HTGet(GR, vertex2, &list2)==1 ){
		NodePointer TBDeleted = ListSearch(vertex1,list2->list);
		if (TBDeleted!=NULL) DeleteNode(list2->list,TBDeleted);
		TBDeleted = ListSearch(vertex2,list1->list);
		if (TBDeleted!=NULL) DeleteNode(list1->list,TBDeleted);
	}
}

NodePointer UGGetAdjacent(UGGraph GR,char * vertex){
	HTitem item;
	if (HTGet(GR, vertex, &item)==1){
		if (item->list->Linknext!=NULL)
		return item->list;
	}
	return NULL;
}

void UGRemoveVertex(UGGraph GR, char* vertex){
	NodePointer list;
	list = UGGetAdjacent(GR,vertex);
	if (list!=NULL){
		NodePointer TBDeleted , temp = list->Linknext;
		while(temp!=NULL){
			UGRemoveEdge(GR,vertex,temp->item);
			temp = temp->Linknext;
		}
	}
	HTRemove(GR,vertex);
}

char* MinDistance(HashTable GR){
	int i, min = INT_MAX;
	char * mintag = NULL;
	HTitem item;
	HTNode temp;
	for (i=0 ; i < M ; i++){
		if (GR[i]!=NULL){
			temp = GR[i];
			while (temp!=NULL){
				HTGet(GR,temp->key,&item);
				if (temp->item->W!=1){
					if (item->dist<min){
						min = temp->item->dist;
						mintag = temp->key; 
					}
				}
			temp = temp->next;
			}
			
		}
	}
	return mintag;
}




NodePointer UGShortestPath(UGGraph GR,char *vertex1, char * vertex2){		//all distances tha einai 1;

	int i;
	HTitem item;
	HTNode temp;
	for (i = 0 ; i < M ; i++){
		if (GR[i]!=NULL){
			temp = GR[i];
			while (temp!=NULL){
				temp->item->dist = INT_MAX;
				temp->item->prev = NULL;
				temp->item->W = 0;
				temp = temp->next;	
			}
		}
	}
	
	HTGet(GR,vertex1,&item);
	item->dist = 0;
	char * u = NULL;
	char * v = NULL;
	NodePointer vlist,tempvlist;
	HTitem adjitem;
	int alt;
	
	
	while(1){
		u = MinDistance(GR);
		HTGet(GR,u,&item);
		item->W = 1;
		if (strcmp(u,vertex2)==0){
			break;
		}
		vlist = item->list ;
		if (vlist!=NULL){
			tempvlist = vlist->Linknext;
			while (tempvlist!=NULL){
				HTGet(GR,tempvlist->item,&adjitem);
				if (adjitem->W!=1){
					alt = item->dist +1;
					
					if (alt < adjitem->dist){
						adjitem->dist = alt;
						adjitem->prev = u;
						
					} 
				}
				tempvlist = tempvlist->Linknext;
			}
		}
	}
	vlist = NULL;
	vlist = Create();
	u = vertex2;
	while (u!=vertex1){
		InsertNewLastNode(u,vlist);
		HTGet(GR,u,&item);
		u = item->prev;
	}
	HTGet(GR,vertex2,&item);
	printf("The cost of the shortest path is %d\n",item->dist);
	
	
	return vlist;
	
}


void UGDestroy(UGGraph GR){
	int i;
	HTNode temp;
	for (i = 0 ; i < M ; i++){
		if (GR[i]!=NULL){
			temp = GR[i];
			while (temp!=NULL){
				Delete(temp->item->list);
				free(temp->item);
				temp = temp->next;	
			}
		}
	}
	HTDestroy(GR);
}






HashTable DictionaryCreate(char * word){
	FILE *pfile=fopen("words.txt","r");
	int count=0;
	char str[18];
	if (pfile==NULL){
		printf("Error opening file\n");
	}
	while (fgets(str,18,pfile)!=NULL){
		count++;
	}
	printf("words has %d words \n", count);
	rewind(pfile);
	
	
	int l;
	UGGraph dictionary = UGCreate();
	while (fgets(str,18,pfile)!=NULL){
		l = strlen(str);
		 
		if (strlen(word)+1==strlen(str)){
			printf("%s",str);
			//str[l-1] = 'a';
			UGAddVertex(&dictionary,str);
		}
	}
	HTVisit(dictionary,HTPrintItemValues);
	if (dictionary == NULL){
		printf("the dictionary is NULL");
		return NULL;
	}
	return dictionary;
}









NodeType * Similar(char * word ){
	FILE *pfile=fopen("words.txt","r");
	int count=0;
	char str[18];
	NodeType * L = Create();
	if (pfile==NULL){
		printf("Error opening file\n");
		return L;
	}
	while (fgets(str,18,pfile)!=NULL){
		count++;
	}
	printf("words has %d words \n", count);
	rewind(pfile);
	char ** dictionary;
	dictionary = (char **)malloc(count * sizeof(char *));
	int i=0;
	while (fgets(str,18,pfile)!=NULL){
		dictionary[i] = strdup(str); 
		i++;
	}
	sort(dictionary,count);
	int j;
	char  k;
	j=0 ;
	int found , l=strlen(word)+2;
	strcpy(str,word);
	while (j<strlen(word)){
		str[l-2]='\n';
		str[l-1]='\0';
		for (k = 'a' ; k <= 'z' ; k++){
			str[j]=k;
				if  ((found=binsearch(str,count,dictionary))!=0){
					strcpy(str,word);
					str[l-2]='\n';
					str[l-1]='\0';
					if (strcmp(str,dictionary[found])!=0){
						InsertNewLastNode(dictionary[found],L);
					}
				}
		}
		j++;
		strcpy(str,word);
		}
	for (i=0; i<count ; i++)
		free (dictionary[i]);
	free(dictionary);
	return L;
}




int myCompare( const void* a,  const void* b) 
{ 
  
    return strcmp(*(const char**)a, *(const char**)b); 
} 

void sort(char* arr[], int n) 
{ 
    qsort(arr, n, sizeof( char*), myCompare); 
} 


int binsearch(char *w, int n, char **x){
	int cond, low, high, mid;
	low = 0; 
	high = n-1; 
	while (low <= high) { 
		mid = (low+high)/2; 
		if ((cond = strcmp(w, x[mid])) < 0) 
			high = mid-1; 
		else if (cond > 0)
			low = mid+1; 
		else {
			return mid;
		}
	} 
	return 0; 
	
}

void Split(NodeType *L, NodeType * A , NodeType * B){
	NodeType * fast, * slow;
	 fast=L;
	 slow=L;
	 while (fast != NULL) 
    { 
    	fast = fast->Linknext; 
    	if (fast != NULL) 
    	{ 
        	slow = slow->Linknext; 
        	fast = fast->Linknext; 
    	} 
    } 
	A->Linknext = L->Linknext;
	B->Linknext = slow->Linknext;
	slow->Linknext = NULL;
}

void MergeSort (NodeType ** L ){
	if ((*L)->Linknext==NULL || (*L)->Linknext->Linknext ==NULL ){
		return;
		
	}
	NodeType * L1 = Create();
	NodeType * L2 = Create();
	Split(*L,L1,L2);
	
	MergeSort (&L1);
	MergeSort (&L2);
	*L=SortedMerge(L1,L2);
}

NodeType * SortedMerge( NodeType * A , NodeType * B){
	NodeType * Ntemp,  *temp  , * N ;  
	NodeType * HEAD;
			if (A->Linknext->item < B->Linknext->item){
				N = A;
				Ntemp=B;
				HEAD = A;
			}else{
				N = B;
				Ntemp=A;
				HEAD= B;
			}
			while (1){
				while(N->Linknext->item <= Ntemp->Linknext->item ){
					N = N->Linknext;
					if (N->Linknext==NULL)
						break;
				}
				if (N->Linknext!=NULL){
					temp=N->Linknext;
					N->Linknext=Ntemp->Linknext;
					Ntemp->Linknext=temp;
				}
				else{
					N->Linknext=Ntemp->Linknext;
					break;
				}
			}
			if (A->Linknext->item < B->Linknext->item){
				free(B);
			}else{
				free(A);
			}
			return  HEAD;
}
