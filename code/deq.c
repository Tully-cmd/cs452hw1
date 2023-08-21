#define __STDC_WANT_LIB_EXT2__ 1 
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

static void put(Rep r, End e, Data d) {
  if(e == Head) {
    if(r->len == 0) {
      struct Node * new = malloc(sizeof(struct Node));
      new->np[Head] = 0;
      new->np[Tail] = 0;
      new->data = d;
      r->len = r->len + 1;
      r->ht[Head] = new;
      r->ht[Tail] = new;
    } else { 
      struct Node * new = malloc(sizeof(struct Node));
      new->np[Tail] = r->ht[Head];
      new->np[Head] = 0;
      new->data = d;
      r->len = r->len + 1;
      r->ht[Head]->np[Head] = new;
      r->ht[Head] = new;
    }
  }
  if(e == Tail) {
    if(r->len == 0) {
      struct Node * new = malloc(sizeof(struct Node));
      new->np[Tail] = 0;
      new->np[Head] = 0;
      new->data = d;
      r->len = r->len + 1;
      r->ht[Head] = new;
      r->ht[Tail] = new;
    } else {
      struct Node * new = malloc(sizeof(struct Node));
      new->np[Tail] = 0;
      new->np[Head] = r->ht[Tail];
      new->data = d;
      r->len = r->len + 1;
      r->ht[Tail]->np[Tail] = new;
      r->ht[Tail] = new;
    } 
  }
}

static Data ith(Rep r, End e, int i)  { 
  if(i < 0 || i >= r->len) {
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

  return 0; 
}

static Data get(Rep r, End e) {
  if(e == Head) {
    return r->ht[Head]->data;
  }
  if(e == Tail) {
    return r->ht[Tail]->data;
  }
  return 0;
}

static Data rem(Rep r, End e, Data d) { return 0; }

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
