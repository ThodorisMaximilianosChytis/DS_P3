#include <stdio.h>



typedef int HTitem;
typedef struct HashTag {
	char * key;
	HTitem item;
} HTHash;

typedef HTHash* HTNode;
typedef HTNode * HashTable;
//typedef (*Visit)(HashTable HT, char * Key, HTitem Item)  Visit; 

























