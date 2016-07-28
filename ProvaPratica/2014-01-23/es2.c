// Si scriva un programma C chiamato “lineandir”. Il risultato del programma, stampato su standard output, deve essere un solo
// numero intero: la somma del numero di caratteri presenti nelle n-me righe di tutti i file regolari, di testo, non nascosti (il primo
// carattere deve essere diverso da punto) della directory corrente.


//non ho provato neanche questo ma dovrebbe andare


#include <ctype.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>


int isText (char *string){
      for (int i=0;i<read;i++){
            if (!isascii(string[i])) {

              return 0;
        }}
       return 1;
}

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
      int sum=0;
      struct dirent* in_file;
      DIR* FD;
      int text=1;


      if (argc != 2){
            printf("Ci vogliono 1 parametri\n");
            return -1;
      }

      //path=malloc(sizeof(argv[1]));
      path="./"
      n=atoi(argv[1]);


      if (NULL == (FD = opendir ("."))){
      	fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
      	return -1;
      }


      while ((in_file = readdir(FD))){

            riga=0;
            char_numb=0;
            text=1;
            read=0;

            if (!strncmp(in_file->d_name, ".",1))
			continue;	//it compare the first char of the string, this ignore all hidden files


      //printf("%d\n", n );

      stat(in_file->d_name, &mod);
      if(!S_ISREG (mod.st_mode)){
            //printf("File %s id not regular\n", path );
            continue;
      }

      if (NULL == (fd=fopen(path, "r"))){
	           fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
                 return -1;
      }




      //check if it's text
      while ((read = getline(&line, &len, fd)) != -1) {

            if (!isText(line)) {
                  text=0;
                  break;
            }
              riga++;
              if (riga == n) {
                   char_numb = read;
              }

        }

        if (text) {
             sum = sum+ char_numb;
       }


      rewind(fd);
      fclose(fd);



}





      printf("Numero di caratteri nelle righe= %d\n", char_numb );

      /* code */
      return 0;
}
