#define _GNU_SOURCE //Needed for asprintf on my machine. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"

//Indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;  // Head = 0, Tail = 1. Ends unused.

//Node type implementation. Array of Node pointers of neighbors and data ptr.
typedef struct Node {
  struct Node *np[Ends];                // Next/prev neighbors.
  Data data;                            // Data (pass data pointer).
} *Node;                                // Node is a pointer to Node Structure.

//Deq type implementation. Array of Nodes of head and tail of Deq and int len. 
typedef struct {
  Node ht[Ends];                        // Head/Tail nodes.
  int len;                              // int length of Deq.
} *Rep;                                 // Rep is a pointer to Deq Structure.

//Check if pointer to Deq (doubly linked list) is valid and CAST to a Rep
static Rep rep(Deq q) {                 //Return: Rep (prt->Deq). Param: Deq q.
  if (!q) {
    ERROR("zero pointer\n");  // Throw error on NULL pointer and exit.
    exit(1);
  }
  return (Rep)q;
}

extern void printDeqString(Deq q) {
  printf("\nDeq:\t");
  char *s1 = deq_str(q,0); //print list toString.
  printf("%s\ndeq_len(q):\t%d\n\n",s1,deq_len(q));
  free(s1);
}
extern void testPutTailString(Deq q, Str s) {
  printf("deq_tail_put\t%s\n",s);
  deq_tail_put(q,(void*) s); 
  if(rep(q)->ht[Tail]->data != s) {
    ERROR("deq_tail_put\t%s Failed!\n",s);
  } else {
    printf("deq_tail_put\t%s Passed\n",s);
  }
}
extern void testPutHeadString(Deq q, Str s) {
  printf("deq_head_put\t%s\n",s);
  deq_head_put(q,(void*) s); 
  if(strcmp(rep(q)->ht[Head]->data,s) != 0) {
    ERROR("deq_head_put\tFailed!\n");
  } else {
    printf("deq_head_put\t%s\tPassed\n",s);
  }
}

extern void testGetHeadString(Deq q) {
  if(rep(q)->len == 0) {
    WARN("Attempting Pop off of empty list. deq_head_get\n");
    return;
  }
  char * head = rep(q)->ht[Head]->data;
  printf("Pop Head deq_head_get\n");
  if(strcmp(deq_head_get(q),head) != 0) {
    ERROR("deq_head_get\tFailed!\n");
  } else {
    printf("deq_head_get\t%s\tPassed\n",head);
  }
}

extern void testGetTailString(Deq q) {
  if(rep(q)->len == 0) {
    WARN("Attempting Pop off of empty list. deq_tail_get\n");
    return;
  }
  char * tail = rep(q)->ht[Tail]->data;
  printf("Pop Tail deq_tail_get\n");
  if(strcmp(deq_tail_get(q),tail) != 0) {
    ERROR("deq_tail_get\tFailed!\n");
  } else {
    printf("deq_tail_get\t%s\tPassed\n",tail);
  }
}

extern void testIthHeadString(Deq q, int i) { 
  if(i < 0 || i >= rep(q)->len) {
    WARN("Attempting ith on bad index deq_tail_ith\n");
    return;
  }
  printf("deq_head_ith(%d)\n",i);
  int curInd = 0;
  for(Node cur = rep(q)->ht[Head]; cur; cur = cur->np[Tail]) {
    if(curInd == i) {
      if(strcmp(cur->data,deq_head_ith(q,i)) == 0) {
        printf("deq_head_ith(%d)    %s\tPassed\n",i,(char *)cur->data);
	return;
      }
    }
    curInd = curInd + 1;
  }
  ERROR("deq_head_ith()\tFailed!\n");
}

extern void testIthTailString(Deq q, int i) {
  if(i < 0 || i >= rep(q)->len) {
    WARN("Attempting ith on bad index deq_tail_ith\n");
    return;
  }
  int curInd = 0;
  printf("deq_tail_ith(%d)\n",i);
  for(Node cur = rep(q)->ht[Tail]; cur; cur = cur->np[Head]) {
    if(curInd == i) {
      if(strcmp(cur->data,deq_tail_ith(q,i)) == 0) {
        printf("deq_tail_ith(%d)    %s\tPassed\n",i,(char *)cur->data);
	return;
      }
    }
    curInd = curInd + 1;
  }
  ERROR("deq_tail_ith()\tFailed!\n");
}

extern void testRemHeadString(Deq q, Str s) {
  printf("deq_head_rem\t%s\n",s);
  for(Node cur = rep(q)->ht[Head]; cur; cur = cur->np[Tail]) {
    if(strcmp(s,cur->data) == 0) {
      if(strcmp(deq_head_rem(q,s),s) == 0) {
	printf("deq_head_rem\t%s\tPassed\n",s);
	return;
      }
    }
  }
  ERROR("deq_head_rem\tFailed!\n");
}

extern void testRemTailString(Deq q, Str s) {
  printf("deq_tail_rem\t%s\n",s);
  for(Node cur = rep(q)->ht[Tail]; cur; cur = cur->np[Head]) {
    if(strcmp(s,cur->data) == 0) {
      if(strcmp(s,deq_tail_rem(q,s)) == 0) {
        printf("deq_tail_rem\t%s\tPassed\n",s);
	return;
      }
    }
  }
  ERROR("deq_tail_rem\tFailed!\n");
}

extern int testString() {
  Deq q=deq_new();

  //malloc strings 
  Str str1 = strdup("62345\0"); 
  Str str2 = strdup("Item\0");
  Str str3 = strdup("293832\0");
  Str str4 = strdup("aticReprep(Deqq){return(Rep)q;}staticvoidput(Re,Ende,Data"
  "d){if(e==Head){if(r->len==0){structNode*new=malloc(sizeof(structNode));new-"
  ">np[Head]0;new->np[Tail]=0;new->data=d;r->len=r->len+r->ht[Head]=new}else{s"
  "tructNode*new=malloc(sizeof(structNode))new->np[Tail]=r->ht[Head]new->np[He"
  "ad]new->data=r->len=r->len+1;r->ht[Head]->np[Head]=new;r->ht[Head]=new}}\0")
  ;
  Str str5 = strdup("aticReprep(Deqq){return(Rep)q;}staticvoidput(Re,Ende,Data"
  "d){if(e==Head){if(r->len==0){structNode*new=malloc(sizeof(structNode));new-"
  ">np[Head]0;new->np[Tail]=0;new->data=d;r->len=r->len+r\0");
  Str str6 = strdup("777777\0");
  Str str7 = strdup("wtf is this?\0");
  Str str8 = strdup("Quicksilver KEKW\0");
  Str str9 = strdup("KEHK DOUBLE YOU\0");
  Str str10 = strdup("if it aint Magic the Gathering it\0");
  Str str11 = strdup("The duel results are kinda anit climatic.\0");
  Str str12 = strdup("whens exodia?\0");
  Str str13 = strdup("GG\0");
  Str str14 = strdup("Whats the bounty do we need to do anythi\0");
  Str str15 = strdup("yeah I assume this is a good game being \0");
  Str str16 = strdup("Stark Tower POG\0");
  
  //Test put
  printf("\nTesting put\n\n");
  testPutTailString(q,str1);
  testPutHeadString(q,str2);
  testPutHeadString(q,str3);
  testPutHeadString(q,str4);
  testPutHeadString(q,str5);
  testPutTailString(q,str6);
  testPutTailString(q,str7);
  testPutTailString(q,str8);
  testPutHeadString(q,str9);
  testPutTailString(q,str10);
  testPutHeadString(q,str11);
  testPutHeadString(q,str12);
  testPutTailString(q,str13);
  testPutTailString(q,str14);
  testPutTailString(q,str15);
  testPutHeadString(q,str16);

  printDeqString(q);

  //Test Pop Head and Tail
  printf("Testing Pop get(Head|Tail)\n\n");
  testGetHeadString(q);
  testGetTailString(q);
  testGetTailString(q);
  testGetHeadString(q);
  printDeqString(q);

  printf("Testing ith\n\n");
  for(int i = 0; i < deq_len(q); i = i + 1) {
    testIthHeadString(q,i);
  }

  for(int i = 0; i < deq_len(q); i = i + 1) {
    testIthTailString(q,i);
  }

  //Test remove
  printf("\nTesting remove\n\n");
  testRemHeadString(q,str5);
  testRemHeadString(q,str3);
  testRemTailString(q,str9);
  testRemHeadString(q,str11);
  testRemTailString(q,str4);
  //testRemTailString(q,str14);
  testRemHeadString(q,str13);
  testRemHeadString(q,str10);
  testRemTailString(q,str8);
  testRemTailString(q,str7);
  printDeqString(q);

  //Free memory
  deq_del(q,0);
  free(str1);
  free(str2);
  free(str3);
  free(str4);
  free(str5);
  free(str6);
  free(str7);
  free(str8);
  free(str9);
  free(str10);
  free(str11);
  free(str12);
  free(str13);
  free(str14);
  free(str15);
  free(str16);
  return 0;
}
