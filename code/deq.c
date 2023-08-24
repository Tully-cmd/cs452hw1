#define __STDC_WANT_LIB_EXT2__ 1 //`Needed for asprintf on my machine
#define _GNU_SOURCE //Needed for asprintf on my machine 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

//Indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;	//Head = 0, Tail = 1. Ends unused

//Node type implementation. Array of Node pointers of neighbors and data ptr.
typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data; 				// data (pass data pointer)
} *Node; 				// Node is a pointer to Node Structure
					
//Deq type implementation. Array of Nodes of head and tail of Deq and int len. 
typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;				// int length of Deq
} *Rep; 				// Rep is a pointer to Deq Structure
					
//Check if pointer to Deq (doubly linked list) is valid and cast to Rep
static Rep rep(Deq q) { 		//Return: Rep (prt->Deq). Param: Deq q
  if (!q) ERROR("zero pointer");        //Throw error on NULL pointer
  return (Rep)q;	                 
}

//Put Element on the end of the deq on either end. 
static void put(Rep r, End e, Data d) { //Param: Rep (Deq) End (Head/Tail) Data
  Node new = malloc(sizeof(struct Node)); //24bytes 16 for neighbors 8 for Data
  if(r->len == 0) { //Add on Empty Deq
    new->np[Head] = 0; //No neighbors
    new->np[Tail] = 0; //No neighbors
    new->data = d; 
    r->len = r->len + 1;
    r->ht[Head] = new; //The new Head
    r->ht[Tail] = new; //The new Tail
    return;
  } 

  if(e == Head) { //Add on Head of Deq
    new->np[Head] = 0; //New Head so nothing before it
    new->np[Tail] = r->ht[Head]; //New Head points to old Head
    new->data = d;
    r->len = r->len + 1;
    r->ht[Head]->np[Head] = new; //Set old Head prev neighbor to new Head
    r->ht[Head] = new; //New Head is now the Head
    return;
  }
  
  if(e == Tail) { //Add on Tail of Deq
    new->np[Tail] = 0; //New Tail so nothing after it
    new->np[Head] = r->ht[Tail]; //New Tail previous set to current Tail
    new->data = d;
    r->len = r->len + 1;
    r->ht[Tail]->np[Tail] = new; //Set current Tail next to new Tail
    r->ht[Tail] = new; //New Tail is now the Tail
    return;
  }
  ERROR("Bad argument put(End e)\n");
}

static Data ith(Rep r, End e, int i)  { 
  if(i < 0 || i >= r->len) {
    printf("Error: Bad argument ith(int i)\n");
    return 0;
  }

  int curInd = 0;

  if(e == Head) {
    for(Node cur = r->ht[Head]; cur; cur = cur->np[Tail]) {
      if(curInd == i) {
        return cur->data;
      }
      curInd = curInd + 1;
    }
  }
  if(e == Tail) {
    for(Node cur = r->ht[Tail]; cur; cur = cur->np[Head]) {
      if(curInd == i) {
        return cur->data;
      }
      curInd = curInd + 1;
    }
  }
  printf("Error: Bad Argument ith(End e)\n");
  return 0; 
}

static Data get(Rep r, End e) {
  if(e == Head) {
    return r->ht[Head]->data;
  }
  if(e == Tail) {
    return r->ht[Tail]->data;
  }
  printf("Error: Bad Argument get(End e)");
  return 0;
}

static Data rem(Rep r, End e, Data d) { 
  Data ret;	
  if(e == Head) { 
    for(Node cur = r->ht[Head]; cur; cur = cur->np[Tail]) {
      if(cur->data == d) {
	ret = cur->data;
        if(cur->np[Head] != 0) { //Neighbor before is present
	  cur->np[Head]->np[Tail] = 0; //look on the other side?
	  cur->np[Head] = 0; //remove link
	}
	if(cur->np[Head] == 0) { //removing the head
	  r->ht[Head]  = cur->np[Tail];
	}
	if(cur->np[Tail] != 0) { //Neighbor after is present
	  cur->np[Tail]->np[Head] = 0; //look on the other side?
	  cur->np[Tail] = 0; //remove link
	}
	if(cur->np[Tail] == 0) { //removing the tail
	  r->ht[Tail] = cur->np[Head];
	}
	
        free(cur);
	return ret;
      }
    }
  }
  if(e == Tail) { 
    for(Node cur = r->ht[Tail]; cur; cur = cur->np[Head]) {
      if(cur->data == d) {
	ret = cur->data;
        if(cur->np[Head] != 0) {
	  cur->np[Head]->np[Tail] = 0;
	  cur->np[Head] = 0;
	}
	if(cur->np[Tail] != 0) {
	  cur->np[Tail]->np[Head] = 0;
	  cur->np[Tail] = 0;
	}
        //free(cur);
	return ret;
      }
    }
  }
  return 0; 
}

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

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

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
