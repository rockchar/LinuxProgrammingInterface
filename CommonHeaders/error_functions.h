#ifndef _ERROR_FUNCTIONS_H_
#define _ERROR_FUNCTIONS_H_

void errMsg(const char *format, ...);

#ifdef __GNUC__

/* the following declarations stops the GNU C compiler(gcc -Wall from complaining that
control has reached the end of a non void function when we use our error handling
functions to terminate the program */

#define NORETURN __attribute__ ((__noreturn__)) 
#else
#define NORETURN
#endif

void errExit(const char *format, ... ) NORETURN;
void err_exit(const char *format, ...) NORETURN;
void errExitEN(int errrnum,const char *format, ... ) NORETURN;
void fatal(const char *format, ... ) NORETURN;
void usageErr(const char *format, ...) NORETURN;
void cmdLineErr(const char *format, ...) NORETURN;

#endif