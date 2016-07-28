#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAXBUF 1024
#define SHELL "/bin/sh"


int main(int argc, char *argv[]) {
char str[80];
int died = 0;
printf("%d\n",argc );
printf("%s\n", argv[0] );
printf("%s\n", argv[1] );
printf("%s\n", argv[2] );
strcpy(str, argv[1]);
strcat(str, " ");
strcat(str, argv[2]);

printf("%s\n", argv[1] );
printf("%s\n", argv[2] );

printf("%s\n", str );

pid_t pid = fork();
if (pid == -1) {                                                  //sono nel padre, errore della fork
      fprintf(stderr, "forking error\n");
      exit(1);
} else if (pid == 0){
      printf("bella\n" );                                         //sono nel figlio quindi eseguo
      execl(SHELL, SHELL, "-c", str, NULL);

      exit(0);
}
      printf("ciao\n" );
      kill(pid, SIGTERM);


for (int loop; !died && loop < 5 /*For example */; ++loop)
{
    int status;
    pid_t id;
    sleep(1);
    if (waitpid(pid, &status, WNOHANG) == pid) died = 1;
}

if (!died) kill(pid, SIGKILL);


                                                    //sono di nuovo nel padre ma è andato a buon fine quindi mi salvo il pid del figlio


return 0;
}
