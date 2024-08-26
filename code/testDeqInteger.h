#define _GNU_SOURCE // Needed for asprintf on my machine.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "deq.h"
#include "error.h"
/*
// Indices and size of array of node pointers
typedef enum { Head, Tail, Ends } End;  // Head = 0, Tail = 1. Ends unused.

// Node type implementation. Array of Node pointers of neighbors and int data.
typedef struct Node {
    struct Node *np[Ends]; // Next/prev neighbors.
    int data;              // Data (stores integer).
} *Node;                    // Node is a pointer to Node Structure.

// Deq type implementation. Array of Nodes of head and tail of Deq and int len.
typedef struct {
    Node ht[Ends]; // Head/Tail nodes.
    int len;       // int length of Deq.
} *Rep;            // Rep is a pointer to Deq Structure.

// Check if pointer to Deq (doubly linked list) is valid and CAST to a Rep
static Rep rep(Deq q) { // Return: Rep (ptr->Deq). Param: Deq q.
    if (!q) {
        ERROR("zero pointer\n"); // Throw error on NULL pointer and exit.
        exit(1);
    }
    return (Rep)q;
}
*/
extern void printDeqInt(Deq q) {
    printf("\nDeq:\t");
    char *s1 = deq_str(q, 0); // print list toString.
    printf("%s\ndeq_len(q):\t%d\n\n", s1, deq_len(q));
    free(s1);
    sleep(2);
}

extern int testPutTailInt(Deq q, int num) {
    printf("deq_tail_put\t%d\n", num);
    usleep(40000);
    deq_tail_put(q, (void *)(intptr_t)num); 
    if ((int)(intptr_t)(rep(q)->ht[Tail]->data) != num) {  // Proper casting to compare integers
        printf("deq_tail_put\t%d Failed!\n", num);
        return 0;
    } else {
        printf("deq_tail_put\t%d Passed\n", num);
        return 1;
    }
}

extern int testPutHeadInt(Deq q, int num) {
    printf("deq_head_put\t%d\n", num);
    usleep(40000);
    deq_head_put(q, (void *)(intptr_t)num); 
    if ((int)(intptr_t)(rep(q)->ht[Head]->data) != num) {  // Proper casting to compare integers
        printf("deq_head_put\tFailed!\n");
        return 0;
    } else {
        printf("deq_head_put\t%d\tPassed\n", num);
        return 1;
    }
}

extern int testGetHeadInt(Deq q) {
    if (rep(q)->len == 0 || rep(q)->ht[Head] == 0 || rep(q)->ht[Tail] == 0) {
        printf("Attempting Pop off of empty list. deq_head_get\n");
        return 0;
    }
    int head = (int)(intptr_t)(rep(q)->ht[Head]->data);  // Proper casting to convert void* to int
    printf("Pop Head deq_head_get\n");
    usleep(40000);
    if ((int)(intptr_t)deq_head_get(q) != head) {
        printf("deq_head_get\tFailed!\n");
        return 0;
    } else {
        printf("deq_head_get\t%d\tPassed\n", head);
        return 1;
    }
}

extern int testGetTailInt(Deq q) {
    if (rep(q)->len == 0 || rep(q)->ht[Head] == 0 || rep(q)->ht[Tail] == 0) {
        printf("Attempting Pop off of empty list. deq_tail_get\n");
        return 0;
    }
    int tail = (int)(intptr_t)(rep(q)->ht[Tail]->data);  // Proper casting to convert void* to int
    printf("Pop Tail deq_tail_get\n");
    usleep(40000);
    if ((int)(intptr_t)deq_tail_get(q) != tail) {
        printf("deq_tail_get\tFailed!\n");
        return 0;
    } else {
        printf("deq_tail_get\t%d\tPassed\n", tail);
        return 1;
    }
}

extern int testIthHeadInt(Deq q, int i) { 
    if (i < 0 || i >= rep(q)->len) {
        printf("Attempting ith on bad index deq_tail_ith\n");
        return 0;
    }
    printf("deq_head_ith(%d)\n", i);
    usleep(40000);
    int curInd = 0;
    for (Node cur = rep(q)->ht[Head]; cur; cur = cur->np[Tail]) {
        if (curInd == i) {
            if ((int)(intptr_t)(cur->data) == (int)(intptr_t)deq_head_ith(q, i)) {  // Proper casting for comparison
                printf("deq_head_ith(%d)    %d\tPassed\n", i, (int)(intptr_t)(cur->data));
                return 1;
            }
        }
        curInd = curInd + 1;
    }
    printf("deq_head_ith()\tFailed!\n");
    return 0;
}

extern int testIthTailInt(Deq q, int i) {
    if (i < 0 || i >= rep(q)->len) {
        printf("Attempting ith on bad index deq_tail_ith\n");
        return 0;
    }
    int curInd = 0;
    printf("deq_tail_ith(%d)\n", i);
    usleep(40000);
    for (Node cur = rep(q)->ht[Tail]; cur; cur = cur->np[Head]) {
        if (curInd == i) {
            if ((int)(intptr_t)(cur->data) == (int)(intptr_t)deq_tail_ith(q, i)) {  // Proper casting for comparison
                printf("deq_tail_ith(%d)    %d\tPassed\n", i, (int)(intptr_t)(cur->data));
                return 1;
            }
        }
        curInd = curInd + 1;
    }
    printf("deq_tail_ith()\tFailed!\n");
    return 0;
}

extern int testRemHeadInt(Deq q, int num) {
    printf("deq_head_rem\t%d\n", num);
    usleep(40000);
    for (Node cur = rep(q)->ht[Head]; cur; cur = cur->np[Tail]) {
        if ((int)(intptr_t)(cur->data) == num) {  // Proper casting for comparison
            if ((int)(intptr_t)deq_head_rem(q, (void *)(intptr_t)num) == num) {
                printf("deq_head_rem\t%d\tPassed\n", num);
                return 1;
            }
        }
    }
    printf("deq_head_rem\tFailed!\n");
    return 0;
}

extern int testRemTailInt(Deq q, int num) {
    printf("deq_tail_rem\t%d\n", num);
    usleep(40000);
    for (Node cur = rep(q)->ht[Tail]; cur; cur = cur->np[Head]) {
        if ((int)(intptr_t)(cur->data) == num) {  // Proper casting for comparison
            if ((int)(intptr_t)deq_tail_rem(q, (void *)(intptr_t)num) == num) {
                printf("deq_tail_rem\t%d\tPassed\n", num);
                return 1;
            }
        }
    }
    printf("deq_tail_rem\tFailed!\n");
    return 0;
}

extern int testInt() {
    Deq q = deq_new();

    printf("Testing a Deq of Integers\n");
    int n = 0;  // number of tests passed.
    int t = 0;  // number of total tests ran.

    // Test integers
    int int1 = 62345; 
    int int2 = 12345;
    int int3 = 293832;
    int int4 = 98765;
    int int5 = 1234567;
    int int6 = 777777;
    int int7 = 99999;
    int int8 = 54321;

    // Test put
    printf("\nTesting put\n\n");
    n += testPutTailInt(q, int1); t += 1;
    n += testPutHeadInt(q, int2); t += 1;
    n += testPutTailInt(q, int3); t += 1;
    n += testPutHeadInt(q, int4); t += 1;
    n += testPutTailInt(q, int5); t += 1;
    n += testPutHeadInt(q, int6); t += 1;
    n += testPutTailInt(q, int7); t += 1;
    n += testPutHeadInt(q, int8); t += 1;

    // Test get
    printf("\nTesting get\n\n");
    n += testGetHeadInt(q); t += 1;
    n += testGetTailInt(q); t += 1;

    // Test ith
    printf("\nTesting ith\n\n");
    n += testIthHeadInt(q, 0); t += 1;
    n += testIthHeadInt(q, 1); t += 1;
    n += testIthHeadInt(q, 2); t += 1;
    n += testIthHeadInt(q, 3); t += 1;
    n += testIthHeadInt(q, 4); t += 1;
    n += testIthHeadInt(q, 5); t += 1;
    n += testIthTailInt(q, 0); t += 1;
    n += testIthTailInt(q, 1); t += 1;
    n += testIthTailInt(q, 2); t += 1;
    n += testIthTailInt(q, 3); t += 1;
    n += testIthTailInt(q, 4); t += 1;
    n += testIthTailInt(q, 5); t += 1;
    // Test rem
    printf("\nTesting rem\n\n");
    n += testRemHeadInt(q, int3); t += 1;
    n += testRemTailInt(q, int4); t += 1;
    n += testRemHeadInt(q, int5); t += 1;
    n += testRemTailInt(q, int6); t += 1;

	deq_del(q,0);

    printf("\n\nPassed %d/%d Tests\n", n, t);

	if(n == t) {
      printf("Integer test passed!\n");
      return 0;
    }
    printf("Integer test failed!\n");
    return 1;

}

