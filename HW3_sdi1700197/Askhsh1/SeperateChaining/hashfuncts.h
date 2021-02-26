#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include <limits.h>

HashTable  HTCreate(void);
int HTSize(HashTable);
HashTable HTInsert(HashTable ,char *, HTitem);
int HashFunction(char * );
int HTGet(HashTable, char * , HTitem *);
void HTRemove(HashTable , char *  );
void HTPrintItemValues(HashTable, char* , HTitem );
void HTDestroy(HashTable);
void HTRehashing(HashTable *);
void HTVisit(HashTable HT, void  (*Visit)(HashTable , char * , HTitem));







