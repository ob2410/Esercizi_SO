// Scrivere un programma genexe che generi l'eseguibile a partire da tutti I file oggetto della directory corrente.
// genexe prog -lm
// il primo parametro e' il nome dell'eseguibile da generare, tutti gli altri parametri devono essere passati al gcc.
// Prima di generare l'eseguibile genexe deve controllare che tutti I file oggetto siano piu' recenti (ultima modifica) del relativo
// sorgente (se esiste). In caso contrario non si deve generare l'eseguibile ma terminare con un output di errore:
// “run genobj first”

//gcc file1.o file2.o -o file

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of character in the C string str
	if(!dot || dot == filename) return "";
	return dot + 1;
}


int main(int argc, char const *argv[]) {

      struct dirent* file;
      struct dirent* file2;
      struct stat mod;
      time_t time1;
      time_t time2;
      DIR* FD;
      DIR* FD2;
      char **command;
      int n=argc; //sono stanca: n deve avere la grandezza dell'array di partenza

      //non so se si deve mettere prima il flag o prima l'oggetto

      c=malloc( (argc * sizeof( char* ));
      c[0]="gcc";


      //open the current directory
      if (NULL == (FD = opendir ("."))){
            fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
            return -1;
      }

      //FD2 to scan for .o ma voglio provare a usarlo senza riaprire la cartella

      if (NULL == (FD2 = opendir ("."))){
            fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
            return -1;
      }


      while ((file = readdir(FD))){

            if (strcmp (get_filename_ext(file->d_name), "o"))
      		continue;

            n++; //count how many file.o there are

            //finish the command argv
            command = realloc( command , n * sizeof ( char* ))
      	command[n]=file->d_name;


            while (file2 = readdir(FD2)) {



                  if (strcmp (get_filename_ext(file2->d_name), "c"))
            		continue;

                  if (!strcmp (file->d_name, file2->d_name, file->d_namlen-2)) {


                        stat(file->d_name, &mod);
                        time1=mod->st_mtime;
                        stat(file2->d_name, &mod);
                        time2=mod->st_mtime;

                        if (difftime(time1,time2) < 0) {
                              printf("run genobj first\n");
                              return -1;
                        }

                  }

            }

            command=realloc(command, (n+(argc-1))*sizeof(char*));


      }

      //rewind the directory descriptor
      rewinddir(FD);






      return 0;
}
