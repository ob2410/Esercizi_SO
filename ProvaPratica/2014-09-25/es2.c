#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <signal.h>

#define MAXBUF 1024
#define MAX_ARGS 64

typedef struct buffer{
      int mypipe[2];
      pid_t pid;
} buffer;

/*
Completare wta in modo che l'output di ogni comando venga salvato separatemente e solo l'output del processo terminato per
primo venga mostrato.
Nell'esempio di prima l'output dovra' essere:


*/

void split(char *command[], char line[]);
void run2 (int n, char *lines[], pid_t *pids );





int main(int argc, char const *argv[]) {

      FILE *fp;
      FILE* stream;
      char buf[MAXBUF];
      char buf2[MAXBUF];
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
      buffer *text = malloc (i * sizeof(buffer));
      char *cmd[MAX_ARGS];

      for (int n  = 0 ; n < i ; n++) { // Start i at 0, not at 1

            if( pipe(text[n].mypipe) == -1){
                perror("Pipe failed");
                exit(1);
              }

            pid_t pid = fork();
            if (pid == -1) {                                                  //sono nel padre, errore della fork
                  fprintf(stderr, "forking error\n");
                  exit(1);
            } else if (pid == 0){
                  printf("Sono l'%d figlio\n", n );
                  close(STDOUT_FILENO);  //closing stdout
          		close(text[n].mypipe[0]);	   //closing pipe read
                  dup2(text[n].mypipe[1], 1);                                           //sono nel figlio quindi eseguo
                  split( cmd , lines[n]);
                  execvp(cmd[0], cmd);

          		exit(EXIT_FAILURE);
            } else {
            pids[n] = pid;
            text[n].pid=pid;                                                     //sono di nuovo nel padre ma è andato a buon fine quindi mi salvo il pid del figlio
            }

      }
      for (int k=0; k<i; k++){
            printf("%d\n", pids[k] );
      }
      wpid=wait(&status);
      printf("Child with PID %ld exited with status 0x%x.\n", (long)wpid, status);
      while (j<i) {
            if (wpid == text[j].pid) {
                  close(STDIN_FILENO);  //closing stdout
          		close(text[j].mypipe[1]);	   //closing pipe read
                  stream = fdopen(text[j].mypipe[0], "r");
                  while(fgets(buf2, MAXBUF, stream)){
                              printf("%s\n", buf2 );
                  }



            }
            else if(wpid != pids[j]) {
                  printf("%d\n", pids[j] );
                  if ( kill(pids[j], SIGKILL))
                        { printf("Failur\n" );}
                  }
            j++;
      }

      fclose(fp);
  return 0;
}




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
