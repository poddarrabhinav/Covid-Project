/* In this project I have used an idea of adjaceny matrix to create a graph randomly two random numbers are generated
and  their respective matrix position is assigned 1 else 0 */
#include <stdio.h>
#include <time.h> // importing for generating random values 
#include <stdlib.h>
#include "Queues.h"  // importing for using function of queues 
#include "priority.h" // importing for using functions of priority queues 
#include <limits.h>
// variable required for simulation
struct Queue *S,*I,*R;  // lists storing information about the pandemic 
struct Time *times;  // for storing time 
struct arr *u; // copying data from graph 
Event *event,*Q;  // priority queue variables for storing events 
FILE *p;
//Function of the simulation
/* This function is implemented when the action is 'Transmission'.Basically this function helps to 
find people which are connected to the infected node.I used  adjacent matrix for implementing this function */
void process_trans_SIR(int n,struct node *a,int time,float tau,float gamma,struct Queue* S,struct Queue*I,struct Queue*R,int tmax);
/* this function add nodes to recovery list */
void process_rec_SIR(struct node *p, float time,struct Queue *S,struct Queue *I,struct Queue *R);
/*This is the function which helps to perform simulation of the pandemic this takes event from and implement 
other to functions (depends on the event)*/ 
void fast_SIR(int n,float tau,int intial_infected, float gamma,int tmax);

int main()
{	srand(time(NULL));
	int tmax,intial_infected;  // for storing how many days you want to run simulation
	float tau,gamma;  // rate of recovery and infection
	p=fopen("Covid19.txt","w");
	printf("Enter the number of days for which you want run the simulation\n");
	scanf("%d",&tmax);
	printf("Enter infection rate\n");
	scanf("%f",&tau);
	printf("Enter recovery rate\n");
	scanf("%f",&gamma);
	printf("Enter number of people you want to infect intially\n");
	scanf("%d",&intial_infected);
	printf("Creating matrix for establishing random connection in the population\n");
	create_graph();  // creating adjancey matrix
	printf("Starting Simulation\n"); 
	fast_SIR(n,tau,intial_infected,gamma,tmax); //performing simulation using the function
	printf("Output is in the Covid19.txt file and open the Covid19.py to get curves of the simulation \n");
    return 0; 
	
}
void process_trans_SIR(int n,struct node *a,int time,float tau,float gamma,struct Queue* S,struct Queue*I,struct Queue*R,int tmax)
{   	
		enQueue(S,(S->rear->key)-1);
		enQueue(I,(I->rear->key)+1);
		enQueue(R,R->rear->key);
		a->status='I';
		a->r=time+((1-gamma)*randm(1,tmax)); // generating random recovery time of the node
		if(a->r<tmax)	// if recovery time is less than tmax it will push to priority queue
		push(&Q,'R',a->r,a);	

		for(int j=1;j<=n;j++) // this part helps to find connection 
		{	 
			if(adj[a->index][j]==1)
			{	
				if(searchinQueue(Q,j)==NULL)  // check if nodes is already in the queue
				{
					struct node *target=search(u,j); // finding node in the graph
					if(target->status=='S')
					{   
						float inf_time=time+((tau)*randm(1,tmax)); // random generating infection time
						if(inf_time<tmax) 
						{ 
							push(&Q,'T',inf_time,target);
							target->t=inf_time;
						}
					}
				}
			}
		}
		pop(&Q); // removing the node from list 
}
void process_rec_SIR(struct node *p, float time,struct Queue *S,struct Queue *I,struct Queue *R)
{
		enQueue(S,(S->rear->key));
		enQueue(I,(I->rear->key)-1);
		enQueue(R,(R->rear->key)+1);
		p->status='R';
		pop(&Q);	
}
void fast_SIR(int n,float tau,int intial_infected, float gamma,int tmax)
{  
	/* allocating memory for queues */
	u=a();
	S=c();
	I=c();
	R=c();
	enQueue(I,0);
	enQueue(R,0);
	times=timeline(0,tmax);
	
	// entering data in graph 
	for(int i=1;i<=n;i++)
	u=append(&u,i,INT_MAX,'S');
	// adding number of nodes in the graph in susecptible list 
	enQueue(S,order(u));
	//generating random infection 
	for(int i=0;i<intial_infected;i++)
	{
		int k=randm(1,n);
		struct node *temp=u->front;
		for(int i=0;i<k;i++)
		temp=temp->next;
		push(&Q,'T',0,temp); // adding it to PQ
		temp->t=0;
	}
	
	while(Q!=NULL) 
	{     
	   	event=peek(&Q);  // taking most important event
		printf("%d\n",event->nwu->index);
	    while(event->time!=times->current_time)  // buiding timeline
	    {
			times->current_time++;
			 
			fprintf(p,"%d %d %d %d\n",times->current_time,S->rear->key,I->rear->key,R->rear->key);	
		   	fprintf(p,"\n");
		} 
	   if(event->Action=='T')  // it event is 'Transmission'
	  	{ 
		   if(event->nwu->status=='S') // node is 'Susecpitble'
		   process_trans_SIR(n,event->nwu,event->time,tau,gamma,S,I,R,tmax);   
		}
		 else if(event->Action=='R')
			process_rec_SIR(event->nwu,event->time,S,I,R);	
	}
	   while (times->current_time < times->total_time) //in case no other event occurs within the time frame
    	{	
       		times->current_time++;
      		fprintf(p,"%d %d %d %d\n",times->current_time,S->rear->key,I->rear->key,R->rear->key);
		   	fprintf(p,"\n");
    	}
	
}

