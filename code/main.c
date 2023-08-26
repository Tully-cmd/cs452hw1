#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"

typedef enum {Head,Tail,Ends} End;

int main() {
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
  
  //Test put
  printf("\nTesting put\n\n");
  printf("deq_tail_put:\t%s\n",str1);
  deq_tail_put(q,(void*) str1); //free after deq_del before exit
  printf("deq_head_put:\t%s\n",str2);
  deq_head_put(q,(void*) str2);
  printf("deq_head_put:\t%s\n",str3);
  deq_head_put(q,(void*) str3);
  printf("deq_head_put:\t%s\n",str4);
  deq_head_put(q,(void*) str4); 
  printf("deq_head_put:\t%s\n",str5);
  deq_head_put(q,(void*) str5);
  printf("deq_tail_put:\t%s\n",str1);
  deq_tail_put(q,(void*) str6);

  printf("\nDeq:\t");
  char *s1 = deq_str(q,0); //print list toString.
  printf("%s\ndeq_len(q):\t%d\n\n",s1,deq_len(q));
  free(s1);

  //Test Pop Head and Tail
  printf("Testing Pop get(Head|Tail)\n\n");
  printf("Pop Head:\t%s\n",(char *)deq_head_get(q));
  printf("Pop Tail:\t%s\n\n",(char *)deq_tail_get(q));

  printf("Deq:\t");
  char * s2 = deq_str(q,0); //print list toString.
  printf("%s\ndeq_len(q):\t%d\n\n",s2,deq_len(q));
  free(s2);

  printf("Testing ith\n\n");
  for(int i = 0; i < deq_len(q); i = i + 1) {
    printf("deq_head_ith[%d]:\t%s\n",i,(char *) deq_head_ith(q,i));
  }

  for(int i = 0; i < deq_len(q); i = i + 1) {
    printf("deq_tail_ith[%d]:\t%s\n",i,(char *) deq_tail_ith(q,i));
  }
  //Test remove
  printf("Testing remove\n\n");
  printf("deq_head_rem: %s\n\n",(char *)deq_head_rem(q,str4)); 
  printf("Deq:\t");
  char * s3 = deq_str(q,0);
  printf("%s\ndeq_len(q):\t%d\n\n",s3,deq_len(q));
  //Free memory
  free(s3);
  deq_del(q,0);
  free(str1);
  free(str2);
  free(str3);
  free(str4);
  free(str5);
  free(str6);
  return 0;
}
