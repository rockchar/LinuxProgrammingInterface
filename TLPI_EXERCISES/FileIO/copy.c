#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024 /* allow cc -D to override the definition */
#endif

// usage is ./copy old_file new_file
int main(int argC ,  char ** argV)
{
	int inputFd,outputFd,openFlags;
	mode_t filePerms;
	ssize_t bytesRead;
	char buff[BUF_SIZE];

	if(argC!=3 || strcmp(argV[1],"--help")==0)
		usageErr("%s old_file new_file",argV[0]);

	/* open the input and the output file */
	inputFd = open(argV[1],O_RDONLY);

	if(inputFd == -1)
		err_exit("opening file %s",argV[1]);
	
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;

	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH ; /* rw - rw - rw */

	outputFd = open(argV[2],openFlags,filePerms);

	if(outputFd == -1)
		err_exit(" opening file %s",argV[2]);

	/* transfer data till we encounter and error or reach the end of the input */
	while((bytesRead = read(inputFd,buff,BUF_SIZE))>0)
		if(write(outputFd,buff,bytesRead)!=bytesRead)
			fatal("Failed to write the complete buffer");

	if(bytesRead == -1)
		errExit("Read");

	if(close(inputFd) == -1)
		errExit("Close input file");

	if(close(outputFd) == -1)
		errExit("Close output file");

	exit(EXIT_SUCCESS);
}

