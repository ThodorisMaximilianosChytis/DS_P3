#include <stdio.h>
#include <stdlib.h>
#include "conword.h"
#include <string.h>



int main(void){
	
	
	UGGraph DR = DictionaryCreate("hey");
	UGDestroy(DR);
	HTVisit(DR,HTPrintItemValues);
	
}
