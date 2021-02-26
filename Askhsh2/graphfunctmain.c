#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphfuncts.h"




int main(void){
	
 //HashTable hash = HTCreate();

	UGGraph GR = UGCreate();
	UGAddVertex(&GR, "floo");
	UGAddVertex(&GR, "what");
	
	UGAddVertex(&GR, "just another");
	UGAddVertex(&GR, "please have some patience");
	UGAddVertex(&GR, "hello");
	UGAddVertex(&GR, "there");
	UGAddVertex(&GR, "mister");
	
	
	UGAddEdge(GR, "floo", "what");
	UGAddEdge(GR, "what", "just another");
	UGAddEdge(GR, "what", "hello");
	UGAddEdge(GR, "what", "mister");
//	
//	
	UGAddEdge(GR, "hello", "mister");
	UGAddEdge(GR, "mister", "please have some patience");
	UGAddEdge(GR, "just another","please have some patience");
	printf("size is %d\n", HTSize(GR));
//	
//	
//	
	HTVisit(GR,HTPrintItemValues);
//	
	NodePointer path = UGShortestPath(GR,"floo","please have some patience");
	printf("path is 	");
	PrintList(path,"%s");
	
	
	UGRemoveEdge(GR,"floo","what");
	NodePointer list;
	list = UGGetAdjacent(GR,"floo");
	if (list!= NULL) {
		printf("adjacent verteces are\n");
		PrintList(list,"%s");
	}
	

	UGRemoveVertex(GR,"mister");
	list = UGGetAdjacent(GR,"please have some patience");
	if (list!= NULL) {
		printf("adjacent verteces are\n");
		PrintList(list,"%s");
	}
	
	HTVisit(GR,HTPrintItemValues);
	
	UGRemoveVertex(GR,"please have some patience");
	list = UGGetAdjacent(GR,"hello");
	if (list!= NULL) {
		printf("adjacent verteces are\n");
		PrintList(list,"%s");
	}
	
	UGRemoveEdge(GR,"floo","what");
	
	HTVisit(GR,HTPrintItemValues);
	
	
	list = UGGetAdjacent(GR,"what");
	if (list!= NULL) {
		printf("adjacent verteces are\n");
		PrintList(list,"%s");
	}	
	else printf("error\n");



	
	UGDestroy(GR);
	
	return 0;
}
