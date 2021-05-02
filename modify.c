#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

void sigint_handler(int sig) {

        printf("This is a signal handler for SIGINT ");
}

int main() {

        void sigint_handler(int sig);
        int flag=0;
        int num, buffer, pipefd[2];



        if(pipe(pipefd) == -1) {

                perror("pipe");
                exit(EXIT_FAILURE);
        }

          if(signal(SIGINT, sigint_handler) ==  SIG_ERR ) {

                perror("signal");
                exit(1);
        }


        pid_t pid;
        pid = fork();

        if(pid==0) {

                printf("enter a number: ");
                scanf("%d", &num);
                close(pipefd[0]);
                write(pipefd[1], &num, sizeof(num));
        }
        else if ( pid>0 ){

	   wait(NULL);
                close(pipefd[1]);
                read(pipefd[0], &buffer, sizeof(buffer));



        for(int k=2; k<=buffer / 2; k++) {

        if( buffer%k == 0){

                flag=1;
                break;
        }

        }

        if(buffer == 1) {

                printf("1 is not a prime number \n");
        }
        else {

                if( flag == 0 )
                {       printf("%d is a prime number \n", buffer); }
                else
                {       printf("%d is not a prime number \n", buffer); }
        }
}
        return EXIT_SUCCESS;

}
