/* minPQ.h (what is the purpose of this file? Replace this question with your comment.)
*/

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */

/*
 isEmpty
 pre conditions is inputs have to make sense and be initialized
*/

int isEmptyPQ(MinPQ pq); 

/*
 getMin 
 pre conditions is inputs have to make sense and be initialized
*/

int getMin(MinPQ pq);

/*
 getStatus 
 pre conditions is inputs have to make sense and be initialized
*/

int getStatus(MinPQ pq, int id);

/*
 getParent
 pre conditions is inputs have to make sense and be initialized
*/
int getParent(MinPQ pq, int id);

/*
 getPriority
 pre conditions is inputs have to make sense and be initialized
*/
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/*
 delMin 

 pre-condition{PQ is not empty, and it must have a min} 

 post-condition{PQ - 1, PQ  Tree grows by one}
*/
void delMin(MinPQ pq);

/*
 insertPQ

 pre-condition{PQ is not empty, and it must have parent, fringeWeight, and status initialized} 

 post-condition{PQ + 1, PQ  Fringe grows by one}
*/
void insertPQ(MinPQ pq, int id, double priority, int par);

/*
 decreaseKey 

 pre-condition{PQ is not empty, and it must have parent, fringeWeight, and status initialized}
 
 post-condition{Key is decreased}
*/
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/* 
 createPQ 

 pre-condition{NONE}

 pre-condition{PQ is made, statuse is unseen}
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif

