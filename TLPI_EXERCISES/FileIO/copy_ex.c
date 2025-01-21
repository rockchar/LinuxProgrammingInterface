#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include"tlpi_hdr.h"

#define MAX_BUFFER_SIZE 1024

int main(int argC , char **argV)
{
    int inputFd ,outputFd, openMode , open_mode;
    mode_t filePermissionsIn,filePermissionsOut;
    int bytesRead,bytesWrote;
    char szBuffer[MAX_BUFFER_SIZE];

    filePermissionsIn  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH ; /* rw - rw - rw */
    filePermissionsOut = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH ; /* rw - rw - rw */

    //validate the command line args
    if( argC < 3 )
        usageErr("%s source destination\n",argV[0]);
    //source file opened in readonly mode
    open_mode = O_RDONLY;
    inputFd = open(argV[1],open_mode,filePermissionsIn);
    if(inputFd == -1)
        err_exit("Error in opening source file %s \n",argV[1]);

    //destination file opened in writeonly and create if doesnot exist
    open_mode = O_WRONLY|O_CREAT;
    outputFd = open(argV[2],open_mode,filePermissionsOut);

    if(outputFd == -1)
        err_exit("Could not open destination file %s \n",argV[2]);

    while((bytesRead = read(inputFd,szBuffer,MAX_BUFFER_SIZE))>0)
        if(write(outputFd,szBuffer,bytesRead)!=bytesRead)
            err_exit("Failed to write the buffer\n");


	if(close(inputFd) == -1)
		errExit("Close input file");

	if(close(outputFd) == -1)
		errExit("Close output file");

	exit(EXIT_SUCCESS);
    

    
    
}