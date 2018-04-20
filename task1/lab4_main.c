#include <libio.h>
#include "lab4_util.h"

#define SYS_WRITE 1
#define STDOUT 1
#define ERR_MESSAGE 0x55
#define READ 0
#define WRITE 1
#define SYS_OPEN 2
#define END 2
#define SYS_LSEEK 8
#define PERMMISION 777
#define READONLY 0
#define BEGINNING 0
#define CURRENT_POSITION 1
#define CREATE 102
#define offset(a) a
#define STDOUT 1
#define SYS_CLOSE 3
#define DELETE 87
/*TODO kjdfshirakkhkl should be changed too?*/

extern int system_call();

void replaceContent(int fs_new, int fs_old,const char* filePath){
    int tempSize = system_call(SYS_LSEEK,fs_old,offset(0),END);
    char tempBuffer[tempSize];
    system_call(SYS_LSEEK,fs_old,offset(0),BEGINNING);
    system_call(READ,fs_old,tempBuffer,tempSize);
    system_call(SYS_CLOSE,fs_new);
    fs_new=system_call(SYS_OPEN,filePath,0x202,PERMMISION);
    system_call(SYS_LSEEK,fs_new,offset(0),BEGINNING);
    system_call(SYS_WRITE,fs_new,tempBuffer,tempSize);
    system_call(SYS_LSEEK,fs_new,offset(0),BEGINNING);
    system_call(SYS_CLOSE,fs_old);
    system_call(DELETE,"temp.txt");
}

void print(char* str){
    system_call(SYS_WRITE,STDOUT,str,simple_strlen(str));
    system_call(SYS_WRITE,STDOUT,"\n",1);
}
void printn(char* str,int length){
    system_call(SYS_WRITE,STDOUT,str,length);
    system_call(SYS_WRITE,STDOUT,"\n",1);
}
void printFile(int fs){
    int curr = system_call(SYS_LSEEK, fs, offset(0), CURRENT_POSITION);
    int size = system_call(SYS_LSEEK, fs, offset(0), END);
    system_call(SYS_LSEEK, fs, offset(0), BEGINNING);
    char fsize[size];
    system_call(READ,fs,fsize,size);
    printn(fsize,size);
    system_call(SYS_LSEEK, fs, offset(curr), BEGINNING);
}
void zeroBuffer(char* buffer, int bufferSize){
    int i=0;
    for (;i<bufferSize;i++){
        buffer[i]='\0';
    }
}
int main (int argc , char* argv[], char* envp[])
{
    if (argc!=  3)
        return ERR_MESSAGE;
    const char* filepath = argv[1];
    const char* newName = argv[2];
    int fs_Original = system_call(SYS_OPEN,filepath,READONLY,PERMMISION);
    int fs_Temp = system_call(SYS_OPEN,"temp.txt",CREATE,PERMMISION);
    int sizeOfFile = system_call(SYS_LSEEK,fs_Original,offset(0),END);
    unsigned int sizeOfName = simple_strlen(newName);
    char buffer[5];
    int currPosition = system_call(SYS_LSEEK,fs_Original,offset(0),BEGINNING);

    while(currPosition<sizeOfFile){
        zeroBuffer(buffer,5);
        system_call(READ,fs_Original,buffer,5);
        if(simple_strcmp(buffer,"Shira")==0){
            system_call(SYS_WRITE,fs_Temp,newName,sizeOfName);
            currPosition +=5;
        }
        else {
            currPosition = system_call(SYS_LSEEK, fs_Original, offset(currPosition + 1), BEGINNING);
            system_call(SYS_WRITE,fs_Temp,buffer,1);
        }
    }
    replaceContent(fs_Original,fs_Temp,filepath);
    printFile(fs_Original);


    return 0;
}
