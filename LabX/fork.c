#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
        pid_t pid;

        for(int i=0;i<3;i++){
                pid = fork();
                if(pid<0){
                        perror("fork failed");
                        exit(EXIT_FAILURE);
                }
                else if(pid == 0){
                        printf("Child process: PID = %d, Parent PID= %d\n",getpid(),getppid());
                        exit(0);
                }
                else {
                        wait(NULL);
                }
        }
        return 0;
}
