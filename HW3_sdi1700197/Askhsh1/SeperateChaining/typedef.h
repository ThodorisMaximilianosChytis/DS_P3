#include <stdio.h>







typedef int HTitem;
typedef struct HashTag {
	char * key;
	HTitem item;
	struct HashTag * next ; 
} HTHash;

typedef HTHash* HTNode;
typedef HTNode * HashTable; 

























