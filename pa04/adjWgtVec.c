/*
Patrick Toral
ptoral
*/
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>


#include "adjWgtVec.h"


struct AdjWgtVecNode{
 	AdjWgt * adjWgtData;
 	int sz;
 	int capacity ;
} ;

typedef struct AdjWgtVecNode * AdjWgtVec;



AdjWgt adjWgtTop(AdjWgtVec myVec){
   
	return myVec->adjWgtData[myVec->sz - 1];

}


AdjWgt adjWgtData(AdjWgtVec myVec, int i){

  	if( !(0<=i) || !(i < adjWgtSize(myVec)) ){
		exit(1);
	}

	return *(myVec->adjWgtData+i);

}


int adjWgtSize(AdjWgtVec myVec){

	return myVec->sz;

}


int adjWgtCapacity(AdjWgtVec myVec){

	return myVec->capacity;

}



AdjWgtVec adjWgtMakeEmptyVec(void){

	AdjWgtVec newVec = (AdjWgtVec)(malloc(sizeof(AdjWgt)));
	newVec->adjWgtData = malloc(adjWgtInitCap * sizeof(AdjWgt));
	newVec->sz = 0;
	newVec->capacity = adjWgtInitCap;
   
    return newVec;

}



void adjWgtVecPush(AdjWgtVec myVec, AdjWgt newE){
    int newCap;

//CHECKING THE PRECONDITIONS FOR ARRAY DOUBLING

		if( adjWgtSize(myVec) == adjWgtCapacity(myVec) ){


			int newCap = 2*myVec->capacity;
		
			AdjWgt *newData = realloc(myVec->adjWgtData, newCap * sizeof(AdjWgt));

			if(newData == NULL){
			} else if(newData != myVec->adjWgtData){
				myVec->adjWgtData = newData;
			}
			myVec->capacity = newCap;
		}
	// ADDING THE EDGE TO THE DATA ARRAY IN INTVECNODE

      myVec->adjWgtData[myVec->sz] = newE;
      myVec->sz++;

}



void adjWgtVecPop(AdjWgtVec myVec){

	    int newCap;

 
//CHECKING THE PRECONDITIONS FOR ARRAY DOUBLING
		if( myVec->sz == myVec->capacity ){
			
			
			int newCap = 2 * myVec->capacity;

			AdjWgt *newData = realloc(myVec->adjWgtData, newCap * sizeof(int));
			if(newData == NULL){
			} else if(newData != myVec->adjWgtData){
				myVec->adjWgtData = newData;
			}
			myVec->capacity = newCap;
		}

	myVec->adjWgtData[myVec->sz] = myVec->adjWgtData[myVec->sz - 1] ;
	myVec->sz--;

}







