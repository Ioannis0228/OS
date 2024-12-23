#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void signal1_handler(int sig){
        printf("Child recieved SIGUSR1 (signal %d)\n",sig);
}

void signalterm_handler(int sig){
        printf("Child recieved SIGTERM (signal %d)\n",sig);
        exit(EXIT_SUCCESS);

}

int main(){
        pid_t pid;
        pid = fork();
        if(pid == -1){
                perror("Error at fork");
                return 1;
        }
        else if(pid == 0 ){
                if(signal(SIGUSR1,signal1_handler) == SIG_ERR){
                        perror("signal");
                        exit(EXIT_FAILURE);
                }
                if(signal(SIGTERM,signalterm_handler) == SIG_ERR){
                        perror("signal");
                        exit(EXIT_FAILURE);
                }
                while(1)
                        pause();
        }
        else {
                //sleep(1);
                printf("Parent sending SIGUSR1 to child...\n");
                sleep(1);
                if(kill(pid,SIGUSR1) == -1){
                        perror("kill");
                        exit(EXIT_FAILURE);
                }
                sleep(1);
                printf("Parent sending SIGTERM to child...\n");
                sleep(1);
		if(kill(pid,SIGTERM) == -1){
                        perror("kill");
                        exit(EXIT_FAILURE);
                }
                sleep(1);
                wait(NULL);
                printf("Child process terminated\n");
        }
        return 0;
}
