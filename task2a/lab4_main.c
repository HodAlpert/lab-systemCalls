#include "lab4_util.h"
#include <dirent.h>
#include <fcntl.h>


#define SYS_WRITE 1
#define STDOUT 1
#define SYS_OPEN 2
#define READONLY 0
#define PERMMISION 777
#define SYS_GETDENTS 78
#define EXIT 60
#define BUF_SIZE 1024
#define SYS_CLOSE 3
#define HANDLE_ERROR(value) if ((value)<0){\
print("error- value is: ");\
print(simple_itoa(value));\
system_call(EXIT);\
}

#define newChar(old) \
    int pathSize=0;\
for(;filepath[pathSize]!='\0';pathSize++){}\
char* myPath[pathSize+2];\
int i=0;\
for (;filepath[i]!='\0';i++){\
myPath[i] = filepath[i];\
}\
myPath[i] = currentDir->d_name;\
myPath[i+1] = '\0'
extern int system_call();

struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};
void print(char* str){
    system_call(SYS_WRITE,STDOUT,str,simple_strlen(str));
    system_call(SYS_WRITE,STDOUT,"\n",1);
}
void printn(char* str,int length){
    system_call(SYS_WRITE,STDOUT,str,length);
    system_call(SYS_WRITE,STDOUT,"\n",1);
}
void printPath(char* path[]){
    print(*path);
    path++;
    for(;*path!='\0';path++){
        print("/");
        print(*path);
    }
    print("\n");
}
void recPrintDir(char* filepath,int size){
    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int bpos;
    char d_type;
    print(filepath);
    fd = system_call(SYS_OPEN,filepath,READONLY,PERMMISION);
    HANDLE_ERROR(fd);
    nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
    HANDLE_ERROR(nread);
    if (nread == 0)
        return;

    for (bpos = 0; bpos < nread;) {
        d = (struct linux_dirent *) (buf + bpos);
        int pathSize=0;
        for(;d->d_name[pathSize]!='\0';pathSize++){}
        char myPath[pathSize+size+2];
        int i=0;
        for (;i<size;i++){
            myPath[i] = filepath[i];
        }
        myPath[i] = '/';
        i++;
        int j=0;
        for (;i<size+pathSize+1;i++,j++) {
            myPath[i] = d->d_name[j];
        }
        myPath[size+pathSize+1]='\0';
        if(simple_strcmp(d->d_name,".")!=0&&simple_strcmp(d->d_name,"..")) {
            d_type = *(buf + bpos + d->d_reclen - 1);
            if (d_type ==4&&d->d_name[size+pathSize]!='.'){
                recPrintDir(myPath,size+pathSize+1);
            }
            else{
                printn(myPath, size + pathSize+1);
            }
        }
        bpos += d->d_reclen;
    }
    system_call(SYS_CLOSE,fd);


}






int main (int argc , char* argv[], char* envp[]){
    struct linux_dirent64* current;
    char* workingDir = ".";
    recPrintDir(workingDir,1);

    return 0;
}
