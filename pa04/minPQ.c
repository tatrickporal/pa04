/*
Patrick Toral
ptoral
*/

//ALL INFORMATION IN MY minPQ.h FILE
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#include <math.h>
#include "minPQ.h"

struct MinPQNode{
	//MINPQ DATA STRUCTURE
	int *status;
 	int *parent;
 	double *fringeWgt;
 	int numVertices;
 	int numPQ;
 	int minVertex;
 	double oo;
} ;

//POINTER TO MINPQ TO BE USED IN PQ
typedef struct MinPQNode * MinPQ;


/**   ACCESS FUNCTIONS    **/


int isEmptyPQ(MinPQ pq){
	if(pq->numPQ != 0){
		return 0;
	} 
	return 1;
}

int getMin(MinPQ pq){
	
	double minWgt;
	minWgt = pq->oo;
 
  if(pq->minVertex == -1){

  		for(int v = 1; v <= pq->numVertices; v++){
	

			if(getStatus(pq,v) == FRINGE){


				if(getPriority(pq,v) < minWgt){
					pq->minVertex = v;
					minWgt = pq->fringeWgt[v];
				}

			}

		}		

   }

	return pq->minVertex;
}

int getStatus(MinPQ pq, int id){
	return pq->status[id];
}

int getParent(MinPQ pq, int id){
	return pq->parent[id];
}

double getPriority(MinPQ pq, int id){
	return pq->fringeWgt[id];
}

/**   MANIPULATION PROCEDURES    **/

void delMin(MinPQ pq){

	int oldMin = getMin(pq);

	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ-=1;

}

void insertPQ(MinPQ pq, int id, double priority, int par){

     pq->parent[id] = par;
     pq->fringeWgt[id] = priority;
     pq->status[id] = FRINGE;
     pq->minVertex = -1;
     pq->numPQ+=1;


}

void decreaseKey(MinPQ pq, int id, double priority, int par){
	pq->parent[id] = par;
	pq->fringeWgt[id] =  priority;
	pq->minVertex = -1;

}

/**   CONSTRUCTORS   **/

MinPQ createPQ(int n, int status[], double priority[], int parent[]){

	MinPQ pq = (MinPQ)calloc(n + 1, sizeof(MinPQ));
	pq->parent = parent;
	pq->fringeWgt = priority;
	pq->status = status;
	pq->oo = INFINITY;
	for(int i = 1; i <= n; i++){
		status[i] = UNSEEN;
	}
	pq->numVertices = n;
	pq->numPQ = 0;
	pq->minVertex = -1;
	return pq;
}















