// Scrivere un programma che elenchi tutti i file di una directory.
// mytx ddd ddd.tx
// Ogni riga del file di output (secondo parametro) deve contenere la lunghezza, uno spazio e il nume del file. Dopo l'ultima riga
// deve inserire una riga bianca.
// ddd.t2 deve contenere l'elenco dei file regolari. Il primo campo e' un numero intero seguito da uno spazio, tutto cio' che segue
// fino alla fine riga e' il nome del file.
// es.
// 12 file1
// 235 file di prova
//
//
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#define MAXBUF 1024

int main(int argc, char const *argv[]) {

      struct dirent* in_file;
      struct stat mod;
      char buff[MAXBUF];
      int a;
      DIR *FD;
      FILE *out;
      FILE *fd1;

      printf("Iniziamo qui\n");
      if ( argc < 2) {
            printf("Ci vogliono 2 argomenti\n" );
            return -1;
      }

      if (NULL == (FD = opendir (argv[1]))){
	fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
	return -1;
      }


      if (NULL == (out=fopen(argv[2], "w"))){
	fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
	return -1;
      }

      printf("Un momento prima di entrare nel ciclo\n");
      while ((in_file = readdir(FD))){
            FILE *indirFile;

            printf("Sono nel ciclo\n");

            stat(in_file->d_name, &mod);
            if(!S_ISREG (mod.st_mode))
                  continue;
            printf("%s\n",in_file->d_name);
            sprintf(buff, "%d", mod.st_size);
            strcat(buff, " ");
            strcat(buff, in_file->d_name);
            strcat(buff, "\n");

            printf("%s %d\n",buff, strlen(buff));

            if(fwrite(buff , 1 , strlen(buff) , out )!=strlen(buff)) {printf("error\n"); return -1;}
            //fprintf(out, "%s %s\n", (char *)mod.st_size , in_file->d_name );
      }
      fprintf(out, "\n");

      printf("Sono fuori dal ciclo\n");



      rewinddir(FD);


      while ((in_file = readdir(FD))){
            FILE *indirFile;

            printf("Sono nel ciclo\n");

            stat(in_file->d_name, &mod);
            if(!S_ISREG (mod.st_mode))
                  continue;

            if (NULL == (fd1=fopen(in_file->d_name, "r"))){
                  fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
                  return -1;
            }

            do {
                  a = fgetc(fd1);
                  fputc(a, out);
            } while (a != EOF);

            printf("%s\n",in_file->d_name);
            sprintf(buff, "%d", mod.st_size);
            strcat(buff, " ");
            strcat(buff, in_file->d_name);
            strcat(buff, "\n");

            printf("%s %d\n",buff, strlen(buff));

            fclose(fd1);
      }
      fprintf(out, "\n");

      printf("Sono fuori dal ciclo\n");


      fclose(out);
      rewinddir(FD);


      return 0;
}
