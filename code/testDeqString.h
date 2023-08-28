#define _GNU_SOURCE //Needed for asprintf on my machine. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
  sleep(2);
}
extern int testPutTailString(Deq q, Str s) {
  printf("deq_tail_put\t%s\n",s);
  usleep(40000);
  deq_tail_put(q,(void*) s); 
  if(rep(q)->ht[Tail]->data != s) {
    printf("deq_tail_put\t%s Failed!\n",s);
    return 0;
  } else {
    printf("deq_tail_put\t%s Passed\n",s);
    return 1;
  }
}
extern int testPutHeadString(Deq q, Str s) {
  printf("deq_head_put\t%s\n",s);
  usleep(40000);
  deq_head_put(q,(void*) s); 
  if(strcmp(rep(q)->ht[Head]->data,s) != 0) {
    printf("deq_head_put\tFailed!\n");
    return 0;
  } else {
    printf("deq_head_put\t%s\tPassed\n",s);
    return 1;
  }
}

extern int testGetHeadString(Deq q) {
  if(rep(q)->len == 0 || rep(q)->ht[Head] == 0 || rep(q)->ht[Tail] == 0) {
    printf("Attempting Pop off of empty list. deq_head_get\n");
    return 0;
  }
  char * head = rep(q)->ht[Head]->data;
  printf("Pop Head deq_head_get\n");
  usleep(40000);
  if(strcmp(deq_head_get(q),head) != 0) {
    printf("deq_head_get\tFailed!\n");
    return 0;
  } else {
    printf("deq_head_get\t%s\tPassed\n",head);
    return 1;
  }
}

extern int testGetTailString(Deq q) {
  if(rep(q)->len == 0 || rep(q)->ht[Head] == 0 || rep(q)->ht[Tail] == 0) {
    printf("Attempting Pop off of empty list. deq_tail_get\n");
    return 0;
  }
  char * tail = rep(q)->ht[Tail]->data;
  printf("Pop Tail deq_tail_get\n");
  usleep(40000);
  if(strcmp(deq_tail_get(q),tail) != 0) {
    printf("deq_tail_get\tFailed!\n");
    return 0;
  } else {
    printf("deq_tail_get\t%s\tPassed\n",tail);
    return 1;
  }
}

extern int testIthHeadString(Deq q, int i) { 
  if(i < 0 || i >= rep(q)->len) {
    printf("Attempting ith on bad index deq_tail_ith\n");
    return 0;
  }
  printf("deq_head_ith(%d)\n",i);
  usleep(40000);
  int curInd = 0;
  for(Node cur = rep(q)->ht[Head]; cur; cur = cur->np[Tail]) {
    if(curInd == i) {
      if(strcmp(cur->data,deq_head_ith(q,i)) == 0) {
        printf("deq_head_ith(%d)    %s\tPassed\n",i,(char *)cur->data);
	return 1;
      }
    }
    curInd = curInd + 1;
  }
  printf("deq_head_ith()\tFailed!\n");
  return 0;
}

extern int testIthTailString(Deq q, int i) {
  if(i < 0 || i >= rep(q)->len) {
    printf("Attempting ith on bad index deq_tail_ith\n");
    return 0;
  }
  int curInd = 0;
  printf("deq_tail_ith(%d)\n",i);
  usleep(40000);
  for(Node cur = rep(q)->ht[Tail]; cur; cur = cur->np[Head]) {
    if(curInd == i) {
      if(strcmp(cur->data,deq_tail_ith(q,i)) == 0) {
        printf("deq_tail_ith(%d)    %s\tPassed\n",i,(char *)cur->data);
	return 1;
      }
    }
    curInd = curInd + 1;
  }
  printf("deq_tail_ith()\tFailed!\n");
  return 0;
}

extern int testRemHeadString(Deq q, Str s) {
  printf("deq_head_rem\t%s\n",s);
  usleep(40000);
  for(Node cur = rep(q)->ht[Head]; cur; cur = cur->np[Tail]) {
    if(strcmp(s,cur->data) == 0) {
      if(strcmp(deq_head_rem(q,s),s) == 0) {
	printf("deq_head_rem\t%s\tPassed\n",s);
	return 1;
      }
    }
  }
  printf("deq_head_rem\tFailed!\n");
  return 0;
}

extern int testRemTailString(Deq q, Str s) {
  printf("deq_tail_rem\t%s\n",s);
  usleep(40000);
  for(Node cur = rep(q)->ht[Tail]; cur; cur = cur->np[Head]) {
    if(strcmp(s,cur->data) == 0) {
      if(strcmp(s,deq_tail_rem(q,s)) == 0) {
        printf("deq_tail_rem\t%s\tPassed\n",s);
	return 1;
      }
    }
  }
  printf("deq_tail_rem\tFailed!\n");
  return 0;
}

extern int testString() {
  Deq q=deq_new();

  printf("Testing a Deq of Strings\n");
  int n = 0;  //number of tests passed.
  int t = 0;  //number of total tests ran.
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
  Str str17 = strdup("WutFace om for cats ha\0");
  Str str18 = strdup("maicaC maicaUgh lilawiBlush icaarlTea pennymComfy\0");
  Str str19 = strdup("dizzyComfy dizzyComfy\0");
  Str str20 = strdup("dizzyHey\0");
  Str str21 = strdup("I'm late Sadge How's it going? AYAYA\0");
  Str str22 = strdup("dizzyHey dizzyHey\0");
  Str str23 = strdup("Alphabet into countdown PogU\0");
  Str str24 = strdup("Bleep\0");
  Str str25 = strdup("peepoHey\0");
  Str str26 = strdup("ResidentSleeper\0");
  Str str27 = strdup("my favorite is still japanese trigger words i think\0");
  Str str28 = strdup("can you do the pinecone with echoes?\0");
  Str str29 = strdup("yay NICE\0");
  Str str30 = strdup("You look spectacular with your outfit!!!\0");
  Str str31 = strdup("PauseChamp\0");
  Str str32 = strdup("Howl\0");
  Str str33 = strdup("circle tracing pls :)\0");
  Str str34 = strdup("dizzyComfy\0");
  Str str35 = strdup("dizzyLul\0");
  Str str36 = strdup("when you ace the dui test\0");
  Str str37 = strdup("nothings saving you spiderman\0");
  Str str38 = strdup("Bedge dizzyComfy\0");
  Str str39 = strdup("I cant even do abcs backwards while sober\0");
  Str str40 = strdup("Kreygasm\0");
  Str str41 = strdup("dizzyTired dizzyTired dizzyTired dizzyTired\0");
  Str str42 = strdup("dizzySenpai \0");
  Str str43 = strdup("^\0");
  Str str44 = strdup("dizzyTired\0");
  Str str45 = strdup("monkaS zero\0");
  Str str46 = strdup("-1, -2,... Kappa\0");
  Str str47 = strdup("PogU\0");
  Str str48 = strdup("danGachi\0");
  Str str49 = strdup("dizzySmug\0");
  Str str50 = strdup("Torchic\0");
  Str str51 = strdup("ooh, japanese counting\0");
  Str str52 = strdup("... again, with the mind reading... \0");
  Str str53 = strdup("i was gonna say \0");
  Str str54 = strdup("now in japanese \0");
  Str str55 = strdup("LUL sorry if im being weird\0");
  Str str56 = strdup("Happy new year\0");
  Str str57 = strdup("uno dos\0");
  Str str58 = strdup("wtf that countdown was so tingly\0");
  Str str59 = strdup("¿Maybe in spanish?\0");
  Str str60 = strdup("*whispers* NEIN\0");
  Str str61 = strdup("whats abcs? i dont go to the gym\0");
  Str str62 = strdup("What do you mean?\0");
  Str str63 = strdup("Spanish! AYAYA\0");
  Str str64 = strdup("PauseChamp\0");
  Str str65 = strdup("Counting in French is really easy\0");
  Str str66 = strdup("German is fairly easy\0");
  Str str67 = strdup("NODDERS Clap\0");
  Str str68 = strdup("perfecto\0");
  Str str69 = strdup("  mbushCute\0");
  Str str70 = strdup("can u do circle tracing :)\0");
  Str str71 = strdup("mrbluejean dizzyHey dizzyHeart\0");
  Str str72 = strdup("Perfect EZ Clap\0");
  Str str73 = strdup("got em all\0");
  Str str74 = strdup("Muy biennn goood job dizzyPaimon dizzyPaimon dizzyPi\0");
  Str str75 = strdup("correct\0");
  Str str76 = strdup("PogU\0");
  Str str77 = strdup("NANDA KORE WA grimTrigger\0");
  Str str78 = strdup("quatre\0");
  Str str79 = strdup("quatre\0");
  Str str80 = strdup("Me no hablo espanol\0");
  Str str81 = strdup("Cat\0");
  Str str82 = strdup("yes :D\0");
  Str str83 = strdup("how about japanese\0");
  Str str84 = strdup("dizzyUp\0");
  Str str85 = strdup("quatre\0");
  Str str86 = strdup("your spanish pronunciation is so good\0");
  Str str87 = strdup("cat -truh\0");
  Str str88 = strdup("baeginLove pennymPlay ttspDerp mystickNotes bsquarED\0");
  Str str89 = strdup("Un deux trois quatre cinq\0");
  Str str90 = strdup("Counting on french is hard af monkaW\0");
  Str str91 = strdup("peepoArgentina\0");
  Str str92 = strdup("AINTNOWAY AINTNOWAY\0");
  Str str93 = strdup("NAILS\0");
  Str str94 = strdup("SCHIZO\0");
  Str str95 = strdup("It's Joever\0");
  Str str96 = strdup("COCKA\0");
  Str str97 = strdup("BOOBA\0");
  Str str98 = strdup("Bedge\0");
  Str str99 = strdup("Deadge\0");
  Str str100 = strdup("cJerk\0");

  //Test put
  printf("\nTesting put\n\n");
  n += testPutTailString(q,str1); t += 1;
  n += testPutHeadString(q,str2); t += 1;
  n += testPutHeadString(q,str3); t += 1;
  n += testPutHeadString(q,str4); t += 1;
  n += testPutHeadString(q,str5); t += 1;
  n += testPutTailString(q,str6); t += 1;
  n += testPutTailString(q,str7); t += 1;
  n += testPutTailString(q,str8); t += 1;
  n += testPutHeadString(q,str9); t += 1;
  n += testPutTailString(q,str10); t += 1;
  n += testPutHeadString(q,str11); t += 1;
  n += testPutHeadString(q,str12); t += 1;
  n += testPutTailString(q,str13); t += 1;
  n += testPutTailString(q,str14); t += 1;
  n += testPutTailString(q,str15); t += 1;
  n += testPutHeadString(q,str16); t += 1;
  n += testPutTailString(q,str17); t += 1;
  n += testPutTailString(q,str18); t += 1;
  n += testPutTailString(q,str19); t += 1;
  n += testPutTailString(q,str20); t += 1;
  n += testPutHeadString(q,str21); t += 1;
  n += testPutHeadString(q,str22); t += 1;
  n += testPutTailString(q,str23); t += 1;
  n += testPutTailString(q,str24); t += 1;
  n += testPutHeadString(q,str25); t += 1;
  n += testPutHeadString(q,str26); t += 1;
  n += testPutTailString(q,str27); t += 1;
  n += testPutTailString(q,str28); t += 1;
  n += testPutHeadString(q,str29); t += 1;
  n += testPutHeadString(q,str30); t += 1;
  n += testPutTailString(q,str31); t += 1;
  n += testPutTailString(q,str32); t += 1;
  n += testPutHeadString(q,str33); t += 1;
  n += testPutHeadString(q,str34); t += 1;
  n += testPutTailString(q,str35); t += 1;
  n += testPutTailString(q,str36); t += 1;
  n += testPutTailString(q,str37); t += 1;
  n += testPutTailString(q,str38); t += 1;
  n += testPutTailString(q,str39); t += 1;
  n += testPutHeadString(q,str40); t += 1;
  n += testPutHeadString(q,str41); t += 1;
  n += testPutTailString(q,str42); t += 1;
  n += testPutTailString(q,str43); t += 1;
  n += testPutHeadString(q,str44); t += 1;
  n += testPutHeadString(q,str45); t += 1;
  n += testPutTailString(q,str46); t += 1;
  n += testPutTailString(q,str47); t += 1;
  n += testPutHeadString(q,str48); t += 1;
  n += testPutHeadString(q,str49); t += 1;
  n += testPutTailString(q,str50); t += 1;
  n += testPutTailString(q,str51); t += 1;
  n += testPutTailString(q,str52); t += 1;
  n += testPutTailString(q,str53); t += 1;
  n += testPutTailString(q,str54); t += 1;
  n += testPutTailString(q,str55); t += 1;
  n += testPutTailString(q,str56); t += 1;
  n += testPutTailString(q,str57); t += 1;
  n += testPutHeadString(q,str58); t += 1;
  n += testPutHeadString(q,str59); t += 1;
  n += testPutTailString(q,str60); t += 1;
  n += testPutTailString(q,str61); t += 1;
  n += testPutHeadString(q,str62); t += 1;
  n += testPutHeadString(q,str63); t += 1;
  n += testPutTailString(q,str64); t += 1;
  n += testPutTailString(q,str65); t += 1;
  n += testPutHeadString(q,str66); t += 1;
  n += testPutHeadString(q,str67); t += 1;
  n += testPutTailString(q,str68); t += 1;
  n += testPutTailString(q,str69); t += 1;
  n += testPutHeadString(q,str70); t += 1;
  n += testPutHeadString(q,str71); t += 1;
  n += testPutTailString(q,str72); t += 1;
  n += testPutTailString(q,str73); t += 1;
  n += testPutHeadString(q,str74); t += 1;
  n += testPutHeadString(q,str75); t += 1;
  n += testPutTailString(q,str76); t += 1;
  n += testPutTailString(q,str77); t += 1;
  n += testPutHeadString(q,str78); t += 1;
  n += testPutHeadString(q,str79); t += 1;
  n += testPutTailString(q,str80); t += 1;
  n += testPutTailString(q,str81); t += 1;
  n += testPutTailString(q,str82); t += 1;
  n += testPutTailString(q,str83); t += 1;
  n += testPutHeadString(q,str84); t += 1;
  n += testPutHeadString(q,str85); t += 1;
  n += testPutTailString(q,str86); t += 1;
  n += testPutTailString(q,str87); t += 1;
  n += testPutHeadString(q,str88); t += 1;
  n += testPutHeadString(q,str89); t += 1;
  n += testPutTailString(q,str90); t += 1;
  n += testPutTailString(q,str91); t += 1;
  n += testPutHeadString(q,str92); t += 1;
  n += testPutHeadString(q,str93); t += 1;
  n += testPutTailString(q,str94); t += 1;
  n += testPutTailString(q,str95); t += 1;
  n += testPutTailString(q,str96); t += 1;
  n += testPutTailString(q,str97); t += 1;
  n += testPutTailString(q,str98); t += 1;
  n += testPutTailString(q,str99); t += 1;
  n += testPutTailString(q,str100); t += 1;

  printDeqString(q);

  //Test Pop Head and Tail
  printf("Testing Pop get(Head|Tail)\n\n");
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetHeadString(q); t += 1;
  n += testGetTailString(q); t += 1;
  n += testGetTailString(q); t += 1;
  
  printDeqString(q);

  printf("Testing ith\n\n");
  for(int i = 0; i < deq_len(q); i = i + 1) {
    n += testIthHeadString(q,i); t += 1;
  }

  for(int i = 0; i < deq_len(q); i = i + 1) {
    n += testIthTailString(q,i); t += 1;
  }

  printDeqString(q);

  //Test remove
  printf("\nTesting remove\n\n");
  n += testRemHeadString(q,str52); t += 1;
  n += testRemHeadString(q,str32); t += 1;
  n += testRemTailString(q,str55); t += 1;
  n += testRemHeadString(q,str33); t += 1;
  n += testRemTailString(q,str46); t += 1;
  n += testRemTailString(q,str19); t += 1;
  n += testRemHeadString(q,str23); t += 1;
  n += testRemTailString(q,str24); t += 1;
  n += testRemHeadString(q,str6); t += 1;
  n += testRemTailString(q,str7); t += 1;
  n += testRemTailString(q,str3); t += 1;
  n += testRemTailString(q,str17); t += 1;
  n += testRemHeadString(q,str8); t += 1;
  n += testRemHeadString(q,str10); t += 1;
  n += testRemTailString(q,str50); t += 1;
  n += testRemTailString(q,str43); t += 1;
  n += testRemHeadString(q,str51); t += 1;
  n += testRemTailString(q,str30); t += 1;
  n += testRemHeadString(q,str53); t += 1;
  n += testRemTailString(q,str54); t += 1;
  n += testRemHeadString(q,str56); t += 1;
  n += testRemHeadString(q,str57); t += 1;
  n += testRemTailString(q,str40); t += 1;
  n += testRemTailString(q,str34); t += 1;
  n += testRemTailString(q,str29); t += 1;
  n += testRemHeadString(q,str12); t += 1;
  n += testRemHeadString(q,str5); t += 1;
  n += testRemTailString(q,str14); t += 1;
  n += testRemTailString(q,str28); t += 1;
  n += testRemHeadString(q,str37); t += 1;
  n += testRemTailString(q,str26); t += 1;
  n += testRemTailString(q,str25); t += 1;
  n += testRemTailString(q,str39); t += 1;
  n += testRemHeadString(q,str18); t += 1;
  n += testRemHeadString(q,str35); t += 1;
  n += testRemTailString(q,str47); t += 1;
  n += testRemHeadString(q,str36); t += 1;
  n += testRemTailString(q,str4); t += 1;
  n += testRemTailString(q,str27); t += 1;
  n += testRemHeadString(q,str42); t += 1;
  n += testRemHeadString(q,str22); t += 1;
  n += testRemHeadString(q,str11); t += 1;
  n += testRemTailString(q,str9); t += 1;
  n += testRemHeadString(q,str1); t += 1;
  n += testRemTailString(q,str20); t += 1;
  n += testRemTailString(q,str31); t += 1;
  n += testRemTailString(q,str21); t += 1;
  n += testRemTailString(q,str16); t += 1;
  n += testRemHeadString(q,str13); t += 1;
  n += testRemHeadString(q,str15); t += 1;
  n += testRemTailString(q,str38); t += 1;

  printDeqString(q);
  
  printf("%d out of %d String tests passed %.2f%%\n"
  ,n,t,((float)n/(float)t) * 100.0f);

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
  free(str17);
  free(str18);
  free(str19);
  free(str20);
  free(str21);
  free(str22);
  free(str23);
  free(str24);
  free(str25);
  free(str26);
  free(str27);
  free(str28);
  free(str29);
  free(str30);
  free(str31);
  free(str32);
  free(str33);
  free(str34);
  free(str35);
  free(str36);
  free(str37);
  free(str38);
  free(str39);
  free(str40);
  free(str41);
  free(str42);
  free(str43);
  free(str44);
  free(str45);
  free(str46);
  free(str47);
  free(str48);
  free(str49);
  free(str50);
  free(str51);
  free(str52);
  free(str53);
  free(str54);
  free(str55);
  free(str56);
  free(str57);
  free(str58);
  free(str59);
  free(str60);
  free(str61);
  free(str62);
  free(str63);
  free(str64);
  free(str65);
  free(str66);
  free(str67);
  free(str68);
  free(str69);
  free(str70);
  free(str71);
  free(str72);
  free(str73);
  free(str74);
  free(str75);
  free(str76);
  free(str77);
  free(str78);
  free(str79);
  free(str80);
  free(str81);
  free(str82);
  free(str83);
  free(str84);
  free(str85);
  free(str86);
  free(str87);
  free(str88);
  free(str89);
  free(str90);
  free(str91);
  free(str92);
  free(str93);
  free(str94);
  free(str95);
  free(str96);
  free(str97);
  free(str98);
  free(str99);
  free(str100);
  
  if(n == t) {
    printf("String test passed!\n");
    return 0;
  }
  printf("String test failed!\n");
  return 1;
}
