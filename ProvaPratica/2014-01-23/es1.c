// Scrivere un programma in C linean che prenda come parametro il pathname di un file e un numero intero (che chiameremo
// n). Il programma deve stampare come output il numero di caratteri presenti nella n-ma riga del file se il file e' un file regolare
// di testo, non deve stampare nulla negli altri casi. Un file viene considerato di testo se tutti i suoi byte hanno valori compresi nel
// range 1-127. Per controllare se il file e' regolare usare la system call lstat.



#include <ctype.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

      char *path;
      int n;
      char * line = NULL;
      size_t len = 0;
      int riga=0;
      int char_numb=0;
      int read;
      FILE *fd;
      struct stat mod;


      if (argc != 3){
            printf("Ci vogliono 2 parametri\n");
            return -1;
      }

      //path=malloc(sizeof(argv[1]));
      path=argv[1];
      n=atoi(argv[2]);

      printf("%d\n", n );
      stat(path, &mod);
      if(!S_ISREG (mod.st_mode)){
            printf("File %s id not regular\n", path );
            return -1;
      }

      if (NULL == (fd=fopen(path, "r"))){
	           fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
                 return -1;
      }




      //check if it's text
      while ((read = getline(&line, &len, fd)) != -1) {

            for (int i=0;i<read;i++){
			if (!isascii(line[i])) {
                      fprintf(stderr, "Not text\n");
                    return -1;
              }}
              riga++;
              if (riga == n) {
                   char_numb = read;
              }
              printf("read %d char numb %d\n",read, char_numb );
          }


      rewind(fd);







      printf("Numero di caratteri nelle righe= %d\n", char_numb );

      /* code */
      return 0;
}
