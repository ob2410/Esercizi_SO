// Scrivere un programma che per ogni file .c nella directory corrente chiami il compilatore gcc per generare il file oggetto (.o) a
// meno che esista gia' nella directory un file oggetto relativo allo stesso sorgente che sia piu' nuovo (ultima modifica) del
// sorgente.
// Tutti I parametri devono essere passati al compilatore.
// Es:
// genobj -I . -ggdb
// se nella directory corrente esistono I file uno.c e due.c e il file due.o deve richiamare
// gcc -I. -ggdb -c uno.c
// e, solo se due.o ha ultima modifica precedente a due.c, deve chiamare
// gcc -I. -ggdb -c due.c


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

//returns the extension of
const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of character in the C string str
	if(!dot || dot == filename) return "";
	return dot + 1;
}

//compare time modification
double FileCreationTime(char *path) {
    struct stat attr;
    stat(path, &attr);
    printf("Last modified time: %s", ctime(&attr.st_mtime));
}


int main(int argc, char const *argv[]) {

      /*struct dirent { // when _DARWIN_FEATURE_64_BIT_INODE is NOT defined
	ino_t      d_ino;                // file number of entry
	__uint16_t d_reclen;             // length of this record
	__uint8_t  d_type;               // file type, see below
	__uint8_t  d_namlen;             // length of string in d_name
	char    d_name[255 + 1];   // name must be no longer than this
}; */

      struct dirent* file;
      struct dirent* file2;
      struct stat mod;
      time_t time1;
      time_t time2;
      DIR* FD;
      DIR* FD2;
      char *command[argc+3];
      int found=0;

      //create di string for exec
      command[0]="gcc";
      for(int i=1; i<argc; i++){
            command[i]=argv[i];
      }
      command[argc]="-c";

      //open the current directory
      if (NULL == (FD = opendir ("."))){
            fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
            return -1;
      }

      //FD2 to scan for .o ma voglio provare a usarlo senza riaprire la cartella

      /*if (NULL == (FD2 = opendir ("."))){
            fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
            return -1;
      }*/
      FD2=FD //non l'ho provato, dillà faccio come giulio


      while ((file = readdir(FD))){

            if (strcmp (get_filename_ext(file->d_name), "c"))
      		continue;

            //finish the command argv
      	command[argc+1]=file->d_name;
      	command[argc+2]=NULL;

            while (file2 = readdir(FD2)) {



                  if (strcmp (get_filename_ext(file2->d_name), "o"))
            		continue;

                  if (!strcmp (file->d_name, file2->d_name, file->d_namlen-2)) {

                        found=1;
                        stat(file->d_name, &mod);
                        time1=mod->st_mtime;
                        stat(file2->d_name, &mod);
                        time2=mod->st_mtime;

                        if (difftime(time1,time2) > 0) {
                              execvp(command[0],command);
                        }

                  }

            }

            if (!found) {
                  execvp(command[0],command);
            }
            found=0;


      }

      //rewind the directory descriptor
      rewinddir(FD);



      return 0;
}
