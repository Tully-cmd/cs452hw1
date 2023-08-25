//Implementation of Deq. A Deq contains nodes and a pointer to the ends.
//CS452 Operating Systems Fall 2023. Professor Buffenbarger.
//Author: Tully Martin.

#define __STDC_WANT_LIB_EXT2__ 1 //Needed for asprintf on my machine.
#define _GNU_SOURCE //Needed for asprintf on my machine. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

//Indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;	// Head = 0, Tail = 1. Ends unused.

//Node type implementation. Array of Node pointers of neighbors and data ptr.
typedef struct Node {
  struct Node *np[Ends];		// Next/prev neighbors.
  Data data; 				// Data (pass data pointer).
} *Node; 				// Node is a pointer to Node Structure.
					
//Deq type implementation. Array of Nodes of head and tail of Deq and int len. 
typedef struct {
  Node ht[Ends];			// Head/Tail nodes.
  int len;				// int length of Deq.
} *Rep; 				// Rep is a pointer to Deq Structure.
					
//Check if pointer to Deq (doubly linked list) is valid and CAST to a Rep
static Rep rep(Deq q) { 		//Return: Rep (prt->Deq). Param: Deq q.
  if (!q) {
    ERROR("zero pointer\n");  // Throw error on NULL pointer and exit.
    exit(1);
  }
  return (Rep)q;	                 
}

//Put Element on the end of the deq on either end. 
static void put(Rep r, End e, Data d) { //Param: Rep (Deq) End (Head/Tail) Data
  Node new = malloc(sizeof(struct Node)); //24bytes 16 for neighbors 8 for Data
  if(new == NULL) { //malloc failed.
    ERROR("Failed to allocate memory for new Node!\n");
    exit(1);
  }
  if(r->len == 0) { //Add on Empty Deq
    new->np[Head] = 0; //No neighbors
    new->np[Tail] = 0; //No neighbors
    new->data = d; 
    r->len = r->len + 1;
    r->ht[Head] = new; //The new Head
    r->ht[Tail] = new; //The new Tail
    return;
  } 

  if(e == Head) { //Add on Head of Deq.
    new->np[Head] = 0; //New Head so nothing before it.
    new->np[Tail] = r->ht[Head]; //New Head points to old Head.
    new->data = d;
    r->len = r->len + 1;
    r->ht[Head]->np[Head] = new; //Set old Head prev neighbor to new Head.
    r->ht[Head] = new; //New Head is now the Head.
    return;
  }
  
  if(e == Tail) { //Add on Tail of Deq.
    new->np[Tail] = 0; //New Tail so nothing after it.
    new->np[Head] = r->ht[Tail]; //New Tail previous neighbor set to cur Tail.
    new->data = d;
    r->len = r->len + 1;
    r->ht[Tail]->np[Tail] = new; //Set current Tail next neighbor to new Tail.
    r->ht[Tail] = new; //New Tail is now the Tail.
    return; 
  }
  ERROR("Bad argument put(End e) Expected either Head or Tail\n");
  exit(1);
}

//Return ith Data from Deq from Head or Tail.
//Params: Rep (Deq), End (Head/Tail), int (valid index 0 through len-1).
//Return: Data void * 
static Data ith(Rep r, End e, int i)  { 
  if(i < 0 || i >= r->len) {  //Check if valid index.
    ERROR("Bad argument ith(int i) Expected a valid list index\n");
    exit(1);
  }

  int curInd = 0;

  if(e == Head) {
    for(Node cur = r->ht[Head]; cur; cur = cur->np[Tail]) { //Start from Head.
      if(curInd == i) {
        return cur->data;
      }
      curInd = curInd + 1;
    }
    WARN("Could not find the Node to return ith(%d)\n",i); //Data not found.
    ERROR("Node not found\n");
    exit(1);
  }
  if(e == Tail) {
    for(Node cur = r->ht[Tail]; cur; cur = cur->np[Head]) { //Start from Tail.
      if(curInd == i) {
        return cur->data;  //Data found
      }
      curInd = curInd + 1;
    }
    WARN("Could not find the Node to return ith(%d)\n",i);
    ERROR("Node not found\n");
    exit(1);
  }
  ERROR("Bad argument ith(End e) Expected either Head or Tail\n");
  exit(1);
  return 0; 
}

// Pop and remove the last node from the deq.
// Params: Rep (deq) End (Head or Tail).
// Return Data void *
static Data get(Rep r, End e) {
  Data ret = 0;
  if(r->ht[Head] == 0 || r->ht[Tail] == 0) {
    ERROR("Get on empty Deq\n");
    exit(1);
  }
 
  if(r->ht[Head] == r->ht[Tail]) { //Last element
    ret = r->ht[Head]->data;
    free(r->ht[Tail]);
    r->ht[Head] = 0;
    r->ht[Tail] = 0;
    r->len = r->len - 1;
    return ret;
  }

  if(e == Head) {
    ret = r->ht[Head]->data;
    r->ht[Head] = r->ht[Head]->np[Tail];  //Set Head to the next Node.
    free(r->ht[Head]->np[Head]);
    r->ht[Head]->np[Head] = 0;  //Set new Head previous Node to null.
    r->len = r->len - 1;
    return ret;
  }
  if(e == Tail) {
    ret = r->ht[Tail]->data;
    r->ht[Tail] = r->ht[Tail]->np[Head]; //Set Tail to the prev Node.
    free(r->ht[Tail]->np[Tail]);
    r->ht[Tail]->np[Tail] = 0;  //Set new Tail next to null.
    r->len = r->len - 1;
    return ret;
  }
  ERROR("Bad argument get(End e) Expected either Head or Tail\n");
  exit(1);
  return 0;
}

//Remove Deq Node from List. Matching the pointer of the Data.
static Data rem(Rep r, End e, Data d) { //Params: Rep (Deq), End (0|1), Data *
					//Return: Data void * (static)
  Data ret = 0;	
  if(e == Head) { 
    for(Node cur = r->ht[Head]; cur; cur = cur->np[Tail]) { //Start from Head.
      if(cur->data == d) {
	ret = cur->data;
	
	//Set the removed nodes next/prev pointers to NULL.
	
        if(cur->np[Head] != 0) { //Neighbor before is present.
	  cur->np[Head]->np[Tail] = 0;
	  cur->np[Head] = 0;
	} else {  //No neighbor before. Removing Tail.
	  r->ht[Head]  = cur->np[Tail];
	}
	if(cur->np[Tail] != 0) { //Neighbor after is present.
	  cur->np[Tail]->np[Head] = 0;
	  cur->np[Tail] = 0;
	} else { //No neighbor after. Removing Tail.
	  r->ht[Tail] = cur->np[Head];
	}
        free(cur);
	r->len = r->len - 1;
	return ret;
      }
    }
    WARN("Could not find the Node to remove rem(%p)\n",d);
    ERROR("Node not found\n");
    exit(1);
  }
  if(e == Tail) { 
    for(Node cur = r->ht[Tail]; cur; cur = cur->np[Head]) { //Start from Tail.
      if(cur->data == d) {
	ret = cur->data;
	
	//Set the removed nodes next/prev pointers to NULL.
	
        if(cur->np[Head] != 0) { //Neighbor before is present.
	  cur->np[Head]->np[Tail] = 0;
	  cur->np[Head] = 0;
	} else {  //No neighbor before. Removing Tail.
	  r->ht[Head]  = cur->np[Tail];
	}
	if(cur->np[Tail] != 0) { //Neighbor after is present.
	  cur->np[Tail]->np[Head] = 0;
	  cur->np[Tail] = 0;
	} else { //No neighbor after. Removing Tail.
	  r->ht[Tail] = cur->np[Head];
	}
        free(cur);
	return ret;
      }
    }
    WARN("Could not find the Node to remove rem(%p)\n",d);
    ERROR("Node not found\n");
    exit(1);
  }
  ERROR("Bad argument rem(End e) Expected either Head or Tail\n");
  exit(1);
  return 0; 
}

//Malloc and return a new Deq.
//Return: Deq
//Head pointer, Tail pointer, and Deq length.
extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) {
    ERROR("malloc() failed\n");
    exit(1);
  }
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

//Header prototypes.
extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

//Run a function on every Data in Deq. Params: Deq, DeqMapF (Function pointer).
extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

//Free the Deq. Optionally run deq_map on Deq Data.
//Params: Deq, DeqMapF (Function pointer).
extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

//Print all strings in a Deq.
//Assume the caller calls free.
//If printing data that can't be printed as a string you are in for a bad time.
extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup(""); //Malloc.
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data; //If not a string make it a string.
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d); //Format malloc print.
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
