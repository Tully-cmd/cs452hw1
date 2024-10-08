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
typedef enum {Head,Tail,Ends} End;  // Head = 0, Tail = 1. Ends unused.

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

  new->data = d;
  new->np[Head] = new->np[Tail] = 0; // Initialize both pointers to 0

  if(r->len == 0) { //Add on Empty Deq
    r->ht[Head] = r->ht[Tail] = new; //The new node is both Head and Tail
  } else {
    new->np[!e] = r->ht[e]; //New node points to old end
    r->ht[e]->np[e] = new; //Old end points to new node
    r->ht[e] = new; //New node becomes the new end
  }

  r->len++; // Increment length after successful addition

  if(e != Head && e != Tail) {
    WARN("Bad argument put(End e) Expected either Head or Tail\n");
  }
}

//Return ith Data from Deq from Head or Tail.
//Params: Rep (Deq), End (Head/Tail), int (valid index 0 through len-1).
//Return: Data void * 
static Data ith(Rep r, End e, int i)  { 
  //if(i < 0 || i >= r->len) {  //Check if valid index.
  //  ERROR("Bad argument ith(int i) Expected a valid list index\n");
  //  exit(1);
  //}

  int curInd = 0;

  for(Node cur = r->ht[e]; cur; cur = cur->np[!e]) { //End to end. 
    if(curInd == i) {
      return cur->data;
    }
    curInd = curInd + 1;
  }
  //ERROR("Bad argument ith(End e) Expected either Head or Tail\n");
  //exit(1);
  WARN("Bad argument ith(End e) Expected either Head or Tail\n");
  return 0; 
}

// Pop and remove the last node from the deq.
// Params: Rep (deq) End (Head or Tail).
// Return Data void *
static Data get(Rep r, End e) {
  // Check if the deque is empty
  if (r->len == 0) {
    // Warn if trying to get from an empty deque
    WARN("Get on empty Deq\n");
    // Return 0 (null) for empty deque
    return 0;
  }

  // Get the node at the specified end
  Node node = r->ht[e];
  // Store the data from the node to be returned
  Data ret = node->data;

  // Check if this is the last element in the deque
  if (r->len == 1) { // Last element
    // Set both Head and Tail to null for empty deque
    r->ht[Head] = r->ht[Tail] = 0;
  } else {
    // Set the new end to the next (for Head) or previous (for Tail) node
    r->ht[e] = node->np[!e];
    // Set the new end's opposite pointer to null
    r->ht[e]->np[e] = 0;
  }

  // Free the memory of the removed node
  free(node);
  // Decrement the length of the deque
  r->len--;

  // Return the data from the removed node
  return ret;
}

//Remove Deq Node from List. Matching the pointer of the Data.
static Data rem(Rep r, End e, Data d) { //Params: Rep (Deq), End (0|1), Data *
                    //Return: Data void * (static)
  // Loop through the deque from the specified end
  for(Node cur = r->ht[e]; cur; cur = cur->np[!e]) { //Start from given end.
    // Check if the current node's data matches the target data
    if(cur->data == d) {
      // Store the data to be returned
      Data ret = cur->data;

      //Fix node next/prev pointers for the remove.
      // Check if the node has both neighbors (i.e., it's not at an end)
      if(cur->np[Head] && cur->np[Tail]) { //Neighbors are present.
        // Link the previous node to the next node
        cur->np[Head]->np[Tail] = cur->np[Tail];
        // Link the next node to the previous node
        cur->np[Tail]->np[Head] = cur->np[Head];
      } else {
        // Removing head or tail
        End removeEnd;
        // Check if the node has a neighbor in the opposite direction
        if(cur->np[!e]) {
          // If so, we're removing the current end
          removeEnd = e;
        } else {
          // If not, we're removing the last node, so the other end becomes 
		  // the new removeEnd
          removeEnd = !e;
        }
        // Update the deq's end pointer
        r->ht[removeEnd] = cur->np[!removeEnd];
        // If the new end exists, update its pointer
        if(r->ht[removeEnd]) {
          r->ht[removeEnd]->np[removeEnd] = 0; //nothing before a head or 
		  									   //after a tail
        }
      }
     
      // Free the memory of the removed node
      free(cur);
      // Decrease the length of the deque
      r->len--;
      // Return the data from the removed node
      return ret;
    }
  }

  // If the loop completes without finding the node, warn and return 0
  WARN("Could not find the Node to remove rem(%p)\n", d);
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
