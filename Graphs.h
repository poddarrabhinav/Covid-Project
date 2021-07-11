#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define max 1005 // for storing 10000 by 10000 matrix for simulation
int n;
int **adj;
struct node  // struct of node of the graph
{
	char status ;
	int index;  // index of node
	int t;  // infection time
	int r;  // recovery time 
	struct node *next;
};


// The queue, front stores the front node of LL and rear stores the 
// last node of LL 
struct arr { 
	struct node *front, *rear; 
}; 

// A utility function to create a new linked list node. 
struct node* f(int k,int t,char s) 
{ 
	struct node* temp = (struct node*)malloc(sizeof(struct node)); 
	temp->status = s;
	temp->t=t;
	temp->r=0;
	temp->index=k;
	temp->next = NULL; 
	return temp; 
} 

// A utility function to create an empty arr 
struct arr* a() 
{ 
	struct arr* q = (struct arr*)malloc(sizeof(struct arr)); 
	q->front = q->rear = NULL; 
	return q; 
} 

// The function to add a key k to q 
struct arr* append(struct arr** q, int k,int t,char s) 
{ 
	// Create a new LL node 
	struct node* temp = f(k,t,s); 
	// If arr is empty, then new node is front and rear both 
	if ((*q)->rear == NULL) { 
		(*q)->front = (*q)->rear = temp; 
		return *q;
	} 

	// Add the new node at the end of arr and change rear 
	(*q)->rear->next = temp; 
	(*q)->rear = temp; 
	return *q;
} 

int order(struct arr * A)   // numbers of nodes in the graph
{
	struct node *temp=A->front;
	int i=0;
	while(temp!=NULL){
	temp=temp->next;
	i++;
	}
	return i;
}

int randm(int x,int y)  // to generated random number between (x,y)
{  int i,k=0;
	while(k<50000){
	i=(rand()%(y-x+1))+x;
	k++;
	}
	return i;
}
/* this function helps to create a adjacency matrix randomly */
void create_graph()
{
    int i, max_edges, origin, destin;
	printf("Enter the population size.\n");
	scanf("%d",&n);
	adj = (int **)malloc((n+1)*sizeof(int *));
	for(int i =1;i<=n;i++)
		adj[i] = (int *)malloc((n+1)*sizeof(int));
	memset(adj,0,sizeof(adj));
    max_edges =2*n;  // max edges are is so large because to decreasing  the chance generating same random numbers in the loop as it depends on time its approx generates around 3000 edges max. 
 
    for (i = 1; i <= max_edges; i++) {
		
		origin=randm(1,n);
        destin=randm(1,n);
		if(origin == destin)
			continue;
		
        adj[origin][destin] = 1;
    }
}
 
struct node * search(struct arr *u,int j)  // search element in the queue
{
	struct node *temp;
	temp=(u)->front;
	while(temp!=NULL)
	{
		if(temp->index==j)
		return temp;
		else
		temp=temp->next;
	}
	if(temp==NULL)
	return NULL;
}

float min(float x,float y)  // finding minimum value between two numb
{
	if(x<=y)
	return x;
	else 
	return y;
}
