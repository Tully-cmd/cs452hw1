#define _GNU_SOURCE //Needed for asprintf on my machine. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
#include "testDeqString.h"
#include "testDeqInteger.h"

int main() {
  int numTests = 0;
  int numPassed = 0;

  if(testString() != 0) {
    WARN("Test String\n");
  } else {
    numPassed = numPassed + 1;
  }
  numTests = numTests + 1;

  if(testInt() != 0) {
    WARN("Test Integer\n");
  } else {
	numPassed = numPassed + 1;
  }
  numTests = numTests + 1;

  printf("\n%d out of %d main tests passed %.2f%%\n"
  ,numPassed,numTests,((float)numPassed/(float)numTests) * 100.0f);
  return 0;
}
