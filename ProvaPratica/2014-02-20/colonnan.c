// Scrivere un programma in C “colonnan” che prenda come parametro il pathname di un file e un numero intero (che
// chiameremo n). Il programma deve stampare come output il numero di caratteri presenti nella n-ma colonna del file se il file e'
// un file regolare di testo, non deve stampare nulla negli altri casi. Un file viene considerato di testo se tutti i suoi byte hanno
// valori compresi nel range 1-127. Per controllare se il file e' “regolare” usare la system call lstat.

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

      char *path;
      int n;
      int c;
      char a;
      FILE *fd, *fd2;
      struct stat mod;
      int column=1;
      int count=0;

      if (argc != 3){
            printf("Ci vogliono 2 parametri\n");
            return -1;
      }

      path=malloc(sizeof(argv[1]));
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


      if (NULL == (fd2=fopen(path, "r"))){
	           fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
                 return -1;
      }

      //check if it's text

      while ((c=fgetc(fd)) != -1) {
            //c=fgetc(fd);
            printf("%d ", c );
             if (c<1 || c>127) {
                   printf("File %s is not text\n", path );
                   return -1;
             }
      }

      rewind(fd);

      do {
            a = fgetc(fd);
            //printf("%c", a );
            if ( a == '\n') {
                  column=1;
            }else{
                  if (column==n) {
                        count++;
                  }
                  column++;
            }

      } while (a != EOF);





      printf("Numero di caratteri nelle righe= %d\n", count );

      /* code */
      return 0;
}
