#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Graphs.h"  // importing graph data structure and adjacency matrix for the Adja.c
typedef struct point{
	char Action;
	int time;
	struct node* nwu;
	struct point *next;
}Event;

struct Time  // for storing time line
{
	int current_time;
	int total_time;
	Event *q;
};


Event * newEvent(char d, int p,struct node *r)    // for creating new event 
{
	  Event * temp = (Event *)malloc(sizeof(Event));
	  temp->Action = d;
	  temp->time= p;
	  temp->nwu=r;
	  temp->next = NULL;
	  return temp;
}
Event *peek(Event ** head)  // to get head element from priority queue
{
	return (*head);
}
// Removes the element with the
// highest time form the list
void pop(Event ** head)
{
	Event * temp = *head;
	(*head) = (*head)->next;
	free(temp);
}
// Function to push according to time
void push(Event ** head, char d,int p,struct node *r)
{
	Event * start = (*head);

	// Create new Event 
	Event * temp = newEvent(d,p,r);
	if( (*head)==NULL){
	(*head)=temp;
	return;
	}
	// Special Case: The head of list has lesser
	// time than new Event . So insert new
	// Event  before head Event  and change head Event .
	if ((*head)->time >p) {

		// Insert New Event  before head
		temp->next = *head;
		(*head) = temp;
	}
	else {
		// Traverse the list and find a
		// position to insert new Event 
		while (start->next != NULL &&
			start->next->time < p) {
			start = start->next;
		}
		// Either at the ends of the list
		// or at required position
		temp->next = start->next;
		start->next = temp;
	}
}
Event  *searchinQueue(Event *Q,int j)  // search in the priority queue for specific node
{
	Event*temp=Q;
	while(temp!=NULL)
	{
		if(temp->nwu->index==j)
		return temp;
		else
		temp=temp->next;
	}
	if(temp==NULL)
	return NULL;
}
struct Time *timeline(int d,int k) // to create time line node
{
	struct Time *temp=(struct Time *)malloc(sizeof(struct Time));
	temp->current_time=d;
	temp->total_time=k;
	return temp;	
}
// Printing Priority queue 
void Print(Event * head){
	Event * temp = head;
	while (temp!=NULL){
		printf("%c ",temp->Action);
		temp=temp->next;
	}
	printf("\n");
}
