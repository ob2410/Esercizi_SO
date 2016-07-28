// fare un programma che consenta di recuperare un file dal formato generato dall'esercizio1.
// demytx file1 ddd.tx
// deve creare il file 'file1' recuperando il contenuto dal file generato da myt2 dell'esercizio1

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

      FILE *fd1; //file di testo
      FILE *fd1; //file di recupero
      char *line=NULL;
      char *token;
      int size[MAXBUF];
      int i=0;
      int found=0;
      int seek=0;
      fpos_t pos;
      char buff[BUFFSIZE];

      if (NULL == (fd1=fopen(argv[2], "r"))){
	fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
	return -1;
      }


      if (NULL == (fd2=fopen(argv[1], "w"))){
	fprintf(stderr, "Error : Failed to open file - %s\n", strerror(errno));
	return -1;
      }

      while (strcmp(line,"\n")) {

            if (fgets(line, MAXBUF, fd1 ) && !found){
                  token = strtok(line, " ");
                  size[i]=atoi(token);
                  token = strtok(NULL, "\n");
                  if (!strcmp(token,argv1)){
                        found=1;
                  }
                  i++;
            }


      }
      //da qui in poi sono troppo stanca, domani dovrai fare il tar quindi magari vedi un po da come ha fatto giulio e capisci

      //in seek salvo la grandezza di tutti i file che stanno prima di quello che mi interessa
      for (int j=0; j<i-1; j++){
            seek=seek+size[j];
      }
      //se la posizione nello fd1 è quella che deve essere da qui leggo un byte alla volta tutto il contenuto che c'è prima del file che mi interessa
      for(int i=0; i<=seek; i++){
            fgetc(fd1);
      }

      //con il comando di prima sono arrivara al primo elemento del file da copiare e quindi lo copio
      seek=0;
      while (seek<size[i-1]){
            a= fgetc(fd1);
            fputc(a,fd2);
            seek++;
      }

      fclose(fd1);
      fclose(fd2);

      return 0;
}
