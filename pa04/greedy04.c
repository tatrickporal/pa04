/*
Patrick Toral
ptoral
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#include "loadWgtGraph.h"
#include "adjWgtVec.h"
#include "minPQ.h"






//Edge structs to and from with a weight
typedef struct{
     int from;
     int to;
     double weight;
} Edge;


/*
This function is called after the first line has been processed
It will return an edge where the to and from int's defined in the struct 
are used in the parameters for intVedPush 
*/
Edge parseEdge(char * line, int lineSize, int linenumber,AdjWgtVec *adjwgtlist, int n, int flag, char task){
    int digit;
    Edge newEdge;
    int from;
    int to;
    double weight;
    char garbage;
  
    int items = sscanf(line, "%d %d %lf %c", &from, &to, &weight, &garbage);
     newEdge.from = from;
     newEdge.to = to;
     newEdge.weight = weight;
     //if Items are only equal to two overwrite the ones given above
    if(items == 2){
     newEdge.from = from;
     newEdge.to = to;
     newEdge.weight = 0.0;       
    }

    //error checking of more than 3 elements
    if( (items <= 1) || (items > 3) ){

     fprintf(stderr,"--------- \n");
     fprintf(stderr, "BAD LINE: %d  \n",linenumber ); 
     fprintf(stderr,"--------- \n");
     exit(EXIT_FAILURE);

  } 

  //NExt two if statements check if the inputted number is greater than n
  if(from > n ){

    fprintf(stderr,"--------- \n");
    fprintf(stderr,"BAD LINE: %d  \n", linenumber);
    fprintf(stderr,"%d is > %d\n", from, n); 
    fprintf(stderr,"BAD LINE: %d  \n", linenumber);
    fprintf(stderr,"--------- \n");
    exit(EXIT_FAILURE);

  }
   //IMPORTANT
         AdjWgt adjwgt;
   //Pushing the edges to the adjlist 
   //intVecPush(adjlist[newEdge.from], newEdge.to);
   //If the -U is called
         adjwgt.to =  newEdge.to;
         adjwgt.wgt = newEdge.weight;
         adjWgtVecPush(adjwgtlist[from], adjwgt);

         if(task == "p"){
          adjWgtVecPush(adjwgtlist[to], adjwgt);
         }

     return newEdge;
}

/*
*
FUNCTION THAT DISTGUINISHED BETWEEN THE GIVEN COMMAND LINE ARGUMENTS
*
*/
double calcPriority(char*task, int v, MinPQ pq, AdjWgt wInfo){
  double dijWgt = getPriority(pq,v);
  if(task == "d"){
    return (dijWgt + wInfo.wgt);
  } 
  return wInfo.wgt;
}


/*
*
FUNCTION THAT 
*
*/
void updateFringe(MinPQ pq, AdjWgtVec adjwgt, int v, char* task){

    AdjWgtVec remAdj = adjwgt;
    int k = 0; 
    // CYCLE THROUGH THE GIVEN ADJWGTVEC STARTING AT 0
    while(k < adjWgtSize(remAdj)){

      AdjWgt wInfo = adjWgtData(remAdj,k);
      int w = wInfo.to;
      //LINE DISTINGUISHING FOR DIJKSTRAS ALGORITHM
      double newWgt = calcPriority(task,v,pq, wInfo);

      //IF THE STATUS OF THE ONE WE'RE GOING TO IS UNSEEN THEN INSERT IT IN FRINGE 
      if(getStatus(pq,w) == UNSEEN){
        insertPQ(pq,w,newWgt,v);
        //ELSE IF ITS ALREADY ON THE FRINGE CHECK THE WEIGHT 
      } else if(getStatus(pq,w) == FRINGE){
        if(newWgt < getPriority(pq,v)){
          //IF THE WEIGHT IS LESS THAN THE WEIGHT FOUND THEN DECREAS THE KEY
          decreaseKey(pq,w,newWgt,v);
        }
      } 
      k++;
    }
}



/*
*
MY PRINT FUNCTION THAT PRINTS WHAT YOU SEE ON THE TERMINAL
*
*/
void printPRIMS(int n, int s, MinPQ pq, int * parent, int * status, char *task ){
  for(int i = 0; i <=  4; i++){
    printf(".........");
  }
  printf("\n");
  printf("Start Vertex at %d\n", s );
  if(task == "p"){
    printf("PRIMS Algorithm\n");
  } else if(task == "d"){
    printf("DIJKSTRAS Algorithm\n");
  }
  for(int i = 0; i <=  4; i++){
    printf(".........");
  }
 printf("\n");
  for(int i = 0; i <=  4; i++){
    printf("==============");
  }
  printf("|");
  printf("\n");
  printf("v          |satus|          |parent|          |fringeWgt|\n");
  for(int i = 1; i <= n; i++){
    printf("%3d|           %c            %3d              %8lf               |\n", i, getStatus(pq,i), getParent(pq,i), getPriority(pq,i));

  }
    for(int i = 0; i <=  4; i++){
    printf("==============");
  }
  printf("\n");
}


void greedyTree(AdjWgtVec *adjwgtlist,int n, int s,int * status , int* parent, double* fringeWgt, char *task){
    //INITALZE ALL THE ARRAYS THAT ARE PUT INTO THE PQ
    int * stat = status;
    int * par = parent;
    double * fWgt = fringeWgt;
    //CREATING THE PQ
    MinPQ pq = createPQ(n, stat, fWgt, par);

    //INSERTING THE SOURCE PQ IN THE PQ
    insertPQ(pq,s,0,-1);

    //GOING THROUGH THE PQ
    while(isEmptyPQ(pq) != 1){
      int v = getMin(pq);
      delMin(pq);

      //BY THIS TIME THE SOURCE VERTEX IS IN THE TREE AND GOING IN THE FRINGE
      updateFringe(pq,adjwgtlist[v],v, task);
    }    

    printf("\n\n");

    //PASSING EVERYTHING THAT HAS BEEN MANIPULATED TO MY PRINT FUNCTION
    printPRIMS(n, s, pq, par, stat, task);

} 


int main(int argc, char *argv[])
{

  char *task;
  int flag = 0;
  char *file = argv[1];
   FILE* fp = fopen( "out_file.txt", "w" );


	//The amount of Command line args must be 2 (1:Program name, 2:Input file)
	if((argc != 4)){
		fprintf(stderr,"--------- \n");
     fprintf(stderr, "%s\n","NEED AT LEAST TWO COMMAND LINE ARGUMENTS AND AT MOST 3" );
     fprintf(stderr,"--------- \n"); 
     exit(EXIT_FAILURE);

	}
	//Open the file that is defined by the second command line argument

     //Checking for the flag and setting input file to the third argument if it is true
     if(strncmp(argv[1],"-D",3 ) == 0){
       task = "d";
       file = argv[3];
     }

     if(strncmp(argv[1],"-P",3) == 0){
       task = "p";
       file = argv[3];
     }
     if(strncmp(argv[1],"-U",3) == 0){
        flag = 1;
        file = argv[2];
     }



  FILE *input = fopen(file,"r");
	
	if(input == 0){
      //File could not be found
  fprintf(stderr,"--------- \n");
      fprintf(stderr, "%s '%s' %s\n", "File:", argv[1], "not found" ); 
      fprintf(stderr,"--------- \n");
      exit(EXIT_FAILURE);

      
	} else {
		//File found
    if(flag == 0){


	  printf("%s '%s' %s\n", "Opened", argv[1], "for input :)");
   } else {
    printf("%s '%s' %s\n", "Opened", argv[3], "for input :)");
   }
	}


   char line[1000];
   char first[1000];
   int digit = 0;
   int linenum = 1;
   int n = 0;
   int m = 0;
  

   fgets(first, sizeof(first), input);
   char garbage;
   int check = sscanf(first, "%d %c", &n, &garbage);


   //Checking if the first item has a digit in it 
   if(check != 1){
   fprintf(stderr,"--------- \n");
     fprintf(stderr, "TOO MANY NUMBERS ON LINE: 1 => %s \n", first  );
     fprintf(stderr,"--------- \n");
    exit(EXIT_FAILURE);
   }

//MAKING THE ADJECENCYWGTLIST TO CONNECT TO EDGES WITH LENGTH n
   AdjWgtVec *adjwgtlist = (calloc(n+1 , sizeof(AdjWgtVec)));
   for(int i = 0; i<=n; i++){
     adjwgtlist[i] = adjWgtMakeEmptyVec();
   }



  //STARTING AT THE SECOND LINE
    while (fgets(line, sizeof(line), input)) { 
   linenum++;
        if(linenum > 1){

         //INCREASE THE CONNECTION EDGES m AND caling the functions 

         Edge this = parseEdge(line, strlen(line), linenum, adjwgtlist, n, flag, task);
    
         if(flag == 0){
          m++;
         } else {

          //if undirected graph
          m+=2;
         }
         
       }
    digit = 0;
   } 

int s = atoi(argv[2]);

if(s > n){
    fprintf(stderr,"START VERTEX IS GREATER THAN N\n");
    exit(EXIT_FAILURE);
}

printf("%d\n",s );
int * status = calloc(n+1, sizeof(int));
int *parent = calloc(n+1, sizeof(int));
double *fringeWgt = calloc(n+1, sizeof(double));

greedyTree(adjwgtlist, n, s, status,parent, fringeWgt, task);

}















