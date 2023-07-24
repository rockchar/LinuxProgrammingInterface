#ifndef _COMMON_HEADERS_H_
#define _COMMON_HEADERS_H_     /* prevent accidental double inclusion */

//standard headers
#include <sys/types.h>         /* Type definitions used by many programs */
#include <stdio.h>             /* Standard input and output functions */
#include <stdlib.h>            /* Commonly used library functions and the EXIT_SUCCESS and EXIT_FAILURE constants*/
#include <unistd.h>            /* Prototypes of many unix system callS */
#include <errno.h>             /* Declares errno and defines error constants */
#include <string.h>            /* commonly used string handling functions */

//user defined headers
#include "get_num.h"           /* Declares our functions for handling numeric
                                  arguements (getInt() , getLong() )*/
#include "error_functions.h"   /* Declares the error handling functions */


//enums
typedef enum { FALSE , TRUE } Boolean ;

//macros
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a.b) ((a) > (b) ? (a) : (b))

#endif