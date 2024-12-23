#include <stdio.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
        int fd[2];
        pid_t pid;
        char msg[] = "This is a message from parent process";
        char term[] = "TERMINATE";
        char buffer[512];
        if(pipe(fd) == -1){
                perror("Error with pipe");
                return 1;
        }
        pid = fork();
        if(pid<0){
                perror("fork failed");
                return 1;
        }
        else if(pid == 0){
                close(fd[1]);
                while(1){
                        ssize_t data = read(fd[0],buffer,sizeof(buffer)-1);
                        if(data > 0){
                                buffer[sizeof(buffer)-1] = '\0';
                                printf("Child received: %s\n",buffer);
                                if(strcmp(buffer,"TERMINATE") == 0){
                                        printf("Terminating child...\n");
                                        break;
                                }
                        }
                }
                close(fd[0]);
                return 0;
        }
        else {
                close(fd[0]);
                write(fd[1],msg,strlen(msg)+1);
                sleep(1);
                write(fd[1],term,strlen(term)+1);
                close(fd[1]);
                wait(NULL);
        }
        return 0;
}
