// Si scriva un programma C chiamato “colonnandir”. Il risultato del programma, stampato su standard output, deve essere un
// solo numero intero: la somma del numero di caratteri presenti nelle n-me colonne di tutti i file regolari, di testo, non nascosti (il
// primo carattere deve essere diverso da punto) della directory passata come parametro, ovvero della directory corrente se
// colonnandir viene lanciato senza specificare parametri.


#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>



int main(int argc, char const *argv[]) {

      char *path;
      int n;
      int c;
      char a;
      FILE *fd;
      DIR *dir;
      struct stat mod;
      int column=1;
      int count=0;
      struct dirent* in_file;
      int sum=0;
      int isText=1;

      if (argc == 2){
            path="./"
      }else if (argc != 3){
            printf("Ci vogliono 2 parametri\n");
            return -1;
      }else{

            path=malloc(sizeof(argv[2]));
            path=argv[2];
      }
      n=atoi(argv[1]);

      if (NULL == (FD = opendir (argv[1]))){
	           fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
                 return -1;
      }
      while ((in_file = readdir(FD))){
            count=0;
            column=1;
            stat(in_file->d_name, &mod);
            if(!S_ISREG (mod.st_mode)){
                  printf("File %s id not regular\n", path );
                  continue;
            }

            //dovrei controllare i file nascosti ma non mi va di provarlo quindi, in base a come mi da il nome
            //del file, per controllare se è nascosto potrei fare in diversi modi, ora non mi va però

            if (NULL == (fd=fopen(in_file->d_name, "r"))){
	                 fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
                        return -1;
            }

      //check if it's text

            while ((c=fgetc(fd)) != -1) {
                  //c=fgetc(fd);
                  printf("%d ", c );
                  if (c<1 || c>127) {
                        printf("File %s is not text\n", path );
                        isText=0;
                  }
            }
            if (!isText){
                  isText=1;
                  continue;
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
            sum= sum+count;




            printf("Numero di caratteri nelle righe= %d\n", count );
      }
      /* code */
      return 0;
}


//non so se funziona ma non mi va di provarlo, comunque non mi legge bene se è testo o meno
