#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"


HashTable  HTCreate(void);
int HTSize(HashTable);
HashTable HTInsert(HashTable ,char *, HTitem );
int HashFunction(char * );
int HTGet(HashTable, char * , HTitem *);
void HTRemove(HashTable , char *  );
void HTPrintItemValues(HashTable, char* , HTitem );
void HTDestroy(HashTable);
void HTRehashing(HashTable *);
void HTVisit(HashTable HT, void  (*Visit)(HashTable , char * , HTitem ));





void InsertNewLastNode(LItemType, NodeType *);
void DeleteLastNode(NodeType *);
NodeType *ListSearch(LItemType  , NodeType *);
void PrintList(NodeType *, char *);
NodeType * Create(void);
void DeleteNode(NodeType *, NodeType* );
void InsertAfterNode (NodeType *, LItemType , NodeType *);
NodeType * Merge( NodeType * , NodeType *);
void Delete(NodeType *);




UGGraph UGCreate(void);
void UGAddVertex(UGGraph * ,char * );
void UGAddEdge(UGGraph , char *,char * );
void UGRemoveEdge(UGGraph,char *,char *);
NodePointer UGGetAdjacent(UGGraph, char *);
void UGRemoveVertex(UGGraph, char*);
void UGDestroy(UGGraph);
NodePointer UGShortestPath(UGGraph GR,char *, char *);
char* MinDistance(HashTable );
