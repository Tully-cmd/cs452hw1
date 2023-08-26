#define _GNU_SOURCE //Needed for asprintf on my machine. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
#include "testDeqString.h"

int main() {
  int numTests = 0;
  int numPassed = 0;

  printf("Testing a Deq of strings\n");
  if(testString() != 0) {
    ERROR("Test String\n");
  } else {
    numPassed = numPassed + 1;
  }
  numTests = numTests + 1;

  //TODO Test malloced ints, structs, chars, doubles, longs

  printf("\n%d out of %d tests passed\n",numPassed,numTests);
  return 0;
}
