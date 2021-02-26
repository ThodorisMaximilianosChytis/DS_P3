#include <stdio.h>
#include <stdlib.h>
#include "hashfuncts.h"


int main(void){
 HashTable   HT = HTCreate();
 printf("size is %d \n",HTSize(HT) );	
 
  HT=HTInsert(HT,"kleidaki",500);
  HT=HTInsert(HT,"wpa",200);
  HT=HTInsert(HT,"b",100);
  HT=HTInsert(HT,"bbbba",100);
  HT=HTInsert(HT,"bbbbr",100);
 printf("size is %d \n",HTSize(HT) );	

  HT=HTInsert(HT,"kleidakio",500);
  HT=HTInsert(HT,"wpalakia",200);
  HT=HTInsert(HT,"broo",100);
  HT=HTInsert(HT,"bbbbat",100);
   printf("size is %d \n",HTSize(HT) );	

  HT=HTInsert(HT,"bbbbrex",100);
//  
// 
// 
 HTitem  Item ;
 printf(" found = %d \n", HTGet(HT,"wpa",&Item));
 if(HTGet(HT,"wpa",&Item))
	printf("Item is %d\n", Item); 
// 	
printf(" found = %d \n", HTGet(HT,"kleidaki",&Item));
 if(HTGet(HT,"kleidaki",&Item))
	printf("Item is %d\n", Item);
printf("size is %d \n", HTSize(HT) );	
//
//
HTVisit(HT , HTPrintItemValues);
//
//
printf("removing item with key bbbba\n");
HTRemove(HT,"bbbba");
printf("size is %d \n",HTSize(HT) );
HTRemove(HT,"wpa");
HTRemove(HT,"b");
HTRemove(HT,"kleidaki");
HTDestroy(HT);
//
printf("size is %d \n",HTSize(HT) );

 return 0;	
}









