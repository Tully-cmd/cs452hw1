#define __STDC_WANT_LIB_EXT2__ 1 

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"

typedef enum {Head,Tail,Ends} End;

int main() {
  Deq q=deq_new();
  deq_tail_put(q,(void*) &"62345");
  deq_head_put(q,(void*) &"Item\0");
  deq_head_put(q,(void*) &"293832\0");
  
  //deq_head_put(q,"aticReprep(Deqq){return(Rep)q;}staticvoidput(Re,Ende,Datad){if(e==Head){if(r->len==0){structNode*new=malloc(sizeof(structNode));new->np[Head]0;new->np[Tail]=0;new->data=d;r->len=r->len+r->ht[Head]=new}else{structNode*new=malloc(sizeof(structNode))new->np[Tail]=r->ht[Head]new->np[Head]new->data=r->len=r->len+1;r->ht[Head]->np[Head]=new;r->ht[Head]=new}}\0");
  deq_head_put(q,(void*) &"aticReprep(Deqq){return(Rep)q;}staticvoidput(Re,Ende,Datad){if(e==Head){if(r->len==0){structNode*new=malloc(sizeof(structNode));new->np[Head]0;new->np[Tail]=0;new->data=d;r->len=r->len+r\0");
  deq_tail_put(q,(void*) &"777777\0");

  int eight = 88;
  deq_tail_put(q,(void *) &eight);

  char *s=deq_str(q,0);
  free(s);

  printf("\nHead: %s\n",(char *)deq_head_get(q));
  printf("\nTail: %s\n\n",(char *)deq_tail_get(q));
 
  //printf("deq_len(q): %d\n",deq_len(q));

  for(int i = 0; i < deq_len(q); i = i + 1) {
    printf("deq_head_ith[%d]: %s\n\n",i,(char *) deq_head_ith(q,i));
  }

  for(int i = 0; i < deq_len(q); i = i + 1) {
    printf("deq_tail_ith[%d]: %s\n\n",i,(char *) deq_tail_ith(q,i));
  }

  
  char * ch = (char *)  deq_head_rem(q,"aticReprep(Deqq){return(Rep)q;}staticvoidput(Re,Ende,Datad){if(e==Head){if(r->len==0){structNode*new=malloc(sizeof(structNode));new->np[Head]0;new->np[Tail]=0;new->data=d;r->len=r->len+r\0");
  printf("deq_head_rem: %s\n\n",ch);
  //free(ch);
  
  //printf("deq_head_rem: %s\n\n",(char *)deq_head_rem(q,"aticReprep(Deqq){return(Rep)q;}staticvoidput(Re,Ende,Datad){if(e==Head){if(r->len==0){structNode*new=malloc(sizeof(structNode));new->np[Head]0;new->np[Tail]=0;new->data=d;r->len=r->len+r->ht[Head]=new}else{structNode*new=malloc(sizeof(structNode))new->np[Tail]=r->ht[Head]new->np[Head]new->data=r->len=r->len+1;r->ht[Head]->np[Head]=new;r->ht[Head]=new}}\0"));
  
  s = deq_str(q,0);
  printf("%s\n",s);
  free(s);
  deq_del(q,0);

  return 0;
}
