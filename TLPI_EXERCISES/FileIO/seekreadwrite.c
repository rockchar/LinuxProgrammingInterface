/*
Listing 4-3 demonstrates the use of lseek() in conjunction with read() and write(). 
The first command-line argument to this program is the name of a file to be opened. 
The remaining arguments specify I/O operations to be performed on the file. 
Each of these operations consists of a letter followed by an associated value (with no separating space):
soffset: Seek to byte offset from the start of the file.
rlength: Read length bytes from the file, starting at the current file offset, and
display them in text form.
Rlength: Read length bytes from the file, starting at the current file offset, and display them in hexadecimal.
wstr: Write the string of characters specified in str at the current file offset.
*/

#include"tlpi_hdr.h"
#include <fcntl.h>

#define MAX_READ 1024
int main(int argC,char **argV)
{
    int fd,openMode,pos;
    ssize_t numRead;
    mode_t filePerms;
    int sOffset=0;
    char buffer[MAX_READ];
    int bytes_to_read=0;
    char * text_to_write;
    if(argC < 3){
        usageErr("error in command line arguements usage: %s filename {soffset<pos>|rlength<length>|Rlength<length>|wstr<string>}",argV[0]);
    }
    
    openMode = O_RDWR|O_CREAT;//if in case the O_CREAT flag is not specified the perms are not required and can be omitted 
    filePerms = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
    fd=open(argV[1],openMode,filePerms);
    if(fd == -1){
        errExit("Error in opening file");
    }

    for(int i=2 ; i < argC ; i++)
    {
        
        switch(argV[i][0])
        {
            case 's':
                sOffset = getInt(&argV[i][1],GN_ANY_BASE,argV[i]);
                printf("Offset is %d \n",sOffset);
                pos = lseek(fd,sOffset,SEEK_CUR);
                break;
            case 'r':
                bytes_to_read = getInt(&argV[i][1],GN_ANY_BASE,argV[i]);
                numRead = read(fd,buffer,bytes_to_read);
                if(numRead == -1)
                {
                    err_exit("Error Reading file");
                }
                buffer[numRead]='\0';
                printf("The number of bytes read is %d and text is %s",(int)numRead,buffer);
                printf("\n");
                break;
            case 'R':
                bytes_to_read = getInt(&argV[i][1],GN_ANY_BASE,argV[i]);
                numRead = read(fd,buffer,bytes_to_read);
                if(numRead == -1)
                {
                    err_exit("Error Reading file");
                }
                for(int i = 0 ; i < numRead ; i++)
                {
                    printf("%02x ",(int)buffer[i]);
                }
                printf("\n");
                break;
            case 'w':
                text_to_write = &argV[i][1];
                printf("Text is - %s",text_to_write);
                write(fd,text_to_write,strlen(text_to_write));
                printf("\n");
                break;
            default:
                usageErr("Unknown command line");
                break;
        }
    }
}
    
