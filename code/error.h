#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

//Call either Warning or Error with a string.
//WARNLOC & ERRORLOC will print to standard error;
//file:lineNum error/warning: stringMessage
//example: deq.c:49 warning: Attempting remove from empty list 

#define WARNLOC(file,line,kind,args...) do {  \
  fprintf(stderr,"\n%s:%d: ",file,line);      \
  fprintf(stderr,"%s: ",kind);                \
  fprintf(stderr,args);                       \
  fprintf(stderr,"\n");                       \
  fflush(stderr);                             \
} while (0)

#define ERRORLOC(file,line,kind,args...) do { \
  WARNLOC(file,line,kind,args);               \
  exit(1);                                    \
} while (0)

#define WARN(args...) WARNLOC(__FILE__,__LINE__,"warning",args)
#define ERROR(args...) ERRORLOC(__FILE__,__LINE__,"error",args)

#endif
