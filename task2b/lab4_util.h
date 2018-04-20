#include <sys/types.h>

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

#define getNewArray \
            int pathSize=0;\
for(;d->d_name[pathSize]!='\0';pathSize++){}\
char myPath[pathSize+size+2];\
int i=0;\
for (;i<size;i++){\
myPath[i] = filepath[i];\
}\
myPath[i] = '/';\
i++;\
int j=0;\
for (;i<size+pathSize+1;i++,j++) {\
myPath[i] = d->d_name[j];\
}\
myPath[size+pathSize+1]='\0'
#define NameWasGiven flag==0||(simple_strcmp(name,d->d_name)==0)

struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

unsigned int simple_strlen (const char *str);
int simple_strcmp(const char *str1, const char *str2);
int simple_strncmp(const char* str1, const char* str2, unsigned int n);
char *simple_itoa(int num);
int positive_atoi(char* str);
void simple_system(char* command);