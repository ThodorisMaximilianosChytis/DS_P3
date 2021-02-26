#include <stdio.h>





typedef char * LItemType;
typedef struct NodeTag {
                        LItemType item;
                        struct NodeTag *Linknext;
                } NodeType;
typedef NodeType * NodePointer;
typedef struct {
	NodePointer list;
	int dist;
	int W;
	char * prev;	
} *HTitem;
//typedef int * HTitem;
typedef struct HashTag {
	char * key;
	HTitem  item;
	struct HashTag * next ; 
} HTHash;

typedef HTHash* HTNode;
typedef HTNode * HashTable;


typedef HashTable UGGraph;

 





















