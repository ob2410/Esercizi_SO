#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <signal.h>

#define MAXBUF 1024
#define SHELL "/bin/sh"
#define MAX_ARGS 64


/*
Leggere il file di comandi da un file e metterli per bene in un buffer si fa così:
unsa questo
 #define MAXBUF 1024
nel main devi mettere

      FILE *fp;
      char buf[MAXBUF];
      int i=0;
      char *lines[MAXBUF];  --->array delle stringhe dove viene salvato ogni comando uno per uno

      fp=fopen(argv[1], "r");
      if (fp == NULL)
            exit(EXIT_FAILURE);

      while(fgets(buf, MAXBUF, fp)){
                  lines[i]=strdup(buf);
                  i++;
      }



*/


void split(char *command[], char line[]){

	char *token;
	int spaces = 0;

	strtok(line, "\n");
	token = strtok(line, " ");

	while( token != NULL )
	{
		spaces++;
		command[spaces-1] = token;
		token = strtok(NULL, " ");
	}

	command[spaces] = NULL;

}

void run2 (int n, char *lines[], pid_t *pids ){

      char *cmd[MAX_ARGS];
      for (int i  = 0 ; i < n ; i++) { // Start i at 0, not at 1
            pid_t pid = fork();
            if (pid == -1) {                                                  //sono nel padre, errore della fork
                  fprintf(stderr, "forking error\n");
                  exit(1);
            } else if (pid == 0){
                  printf("Sono l'%d figlio\n", i );                                            //sono nel figlio quindi eseguo
                  split( cmd , lines[i]);
                  execvp(cmd[0], cmd);

          		exit(EXIT_FAILURE);
            } else {
            pids[i] = pid;                                                     //sono di nuovo nel padre ma è andato a buon fine quindi mi salvo il pid del figlio
            }

      } 

}

void run (int n, char *lines[], pid_t *pids ){


      for (int i  = 0 ; i < n ; i++) { // Start i at 0, not at 1
            pid_t pid = fork();
            if (pid == -1) {                                                  //sono nel padre, errore della fork
                  fprintf(stderr, "forking error\n");
                  exit(1);
            } else if (pid == 0){
                  printf("Sono l'%d figlio\n", i );                                            //sono nel figlio quindi eseguo
                  execl(SHELL, SHELL, "-c", lines[i], NULL);

          		_exit(EXIT_FAILURE);
            } else {
            pids[i] = pid;                                                     //sono di nuovo nel padre ma è andato a buon fine quindi mi salvo il pid del figlio
            }

      }

}

int main(int argc, char const *argv[]) {

      FILE *fp;
      char buf[MAXBUF];
      int i=0;
      int j=0;
      char *lines[MAXBUF];
      int status;
      int wpid;

      fp=fopen(argv[1], "r");
      if (fp == NULL)
            exit(EXIT_FAILURE);

      while(fgets(buf, MAXBUF, fp)){
                  lines[i]=strdup(buf);
                  i++;
      }

      pid_t *pids = malloc(i * sizeof(pid_t));
      run2 (i,lines, pids);
      for (int k=0; k<i; k++){
            printf("%d\n", pids[k] );
      }
      wpid=wait(&status);
      printf("Child with PID %ld exited with status 0x%x.\n", (long)wpid, status);
      while (j<i) {
            if(wpid != pids[j]) {
                  printf("%d\n", pids[j] );
                  if ( kill(pids[j], SIGKILL))
                        { printf("Failur\n" );}
                  }
            j++;
      }

      fclose(fp);
  return 0;
}
