#include "lab4_util.h"
#include <dirent.h>
#include <printf.h>
#include <fcntl.h>




extern int system_call();


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
void recPrintDir(char* filepath,int size, char* name,int flag){
    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int bpos;
    char d_type;

    fd = system_call(SYS_OPEN,filepath,READONLY,PERMMISION);
    HANDLE_ERROR(fd);
    nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
    HANDLE_ERROR(nread);
    if (nread == 0)
        return;

    for (bpos = 0; bpos < nread;) {
        d = (struct linux_dirent *) (buf + bpos);
        getNewArray;
        if(simple_strcmp(d->d_name,".")!=0&&simple_strcmp(d->d_name,"..")) {
            d_type = *(buf + bpos + d->d_reclen - 1);
            if (d_type ==4&&d->d_name[size+pathSize]!='.'){
                if(NameWasGiven)
                    print(myPath);
                recPrintDir(myPath,size+pathSize+1,name,flag);
            }
            else{
                if(NameWasGiven)
                    print(myPath);
            }
        }
        bpos += d->d_reclen;
    }
    system_call(SYS_CLOSE,fd);


}






int main (int argc , char* argv[], char* envp[]){
    char* workingDir = ".";
    if(argc>1){
        if(simple_strcmp(argv[1],"-n")==0){

            recPrintDir(workingDir,1, argv[2],1);
        }
    }
    else
        recPrintDir(workingDir,1,"",0);

    return 0;
}
