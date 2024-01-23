/*
The following program provides the demonstration of seek in conjuction with read and write.
The first command line arguement is the file name of the file that should be opened
The remaining command line arguements specify I/O operations to be performed on the file
Each of these operations consists of a letter followed by an associated value
( with no separating spaces ):

- The first command line arguement is the name of the file to be opened
- The other command line arguements are the letters followd by the operation
    - soffset (s) : Seek to byte offset from the start of the file
    - rlength (r) : Read length bytes from the file starting at the current offset
    - Rlength (R) : Read length bytes from the file starting at the current offset
                    and display as hexadecimal
    - wstr    (w) : Write the string of characters specified in str at the current 
                    file offset
*/


#include<sys/stat.h>
#include<fcntl.h>
#include"tlpi_hdr.h"
#include<ctype.h>

#define BUFF_SIZE 1024

int
main(int argC, char ** argV)
{
    int fd,openMode,iPos;
    off_t pos;
    mode_t filePerms;
    if(argC < 3 || strcmp(argV[1],"--help") == 0)
        usageErr("%s file {r<length>|R<length}|w<string|s<offset>} ... \n",argV[0]);
    openMode = O_RDWR|O_CREAT;
    filePerms = S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH | S_IRGRP |S_IWGRP;/* rw-rw-rw */
    fd = open(argV[1],openMode,filePerms);
    if(fd == -1)
        errExit("File open");
    for(int i = 2 ; i < argC ; i++ )
    {
        char option = argV[i][0];
        char buff[BUFF_SIZE];
        switch(option)
        {
            case 'r':
            case 'R':
                long bytesToRead = getLong(&argV[i][1],GN_ANY_BASE,argV[i]); 
                int bytesRead;

                bytesRead = read(fd,buff,bytesToRead);   
                if(bytesRead == -1)  
                    errExit("Error in reading\n");
                if(bytesRead == 0)
                    printf("End-of-file %s",argV[1]);
                for(int i = 0 ; i < bytesRead ; i++)
                {
                    if(option == 'r')
                        printf("%c",isprint((unsigned char)buff[i])? buff[i]:'?');
                    else if(option == 'R')
                        printf("%02x",buff[i]);
                }
                printf("\n");
            break;
            case 'w':
                printf("\n Write %s String at location\n",&argV[i][1]);
            break;
            case 's':
                printf("Seek %s Bytes\n",&argV[i][1]);
                iPos = getInt(argV[i][1],GN_ANY_BASE,argV[i]);
                pos = lseek(fd,pos,iPos);
            break;
        }
    }
    close(fd);
} 