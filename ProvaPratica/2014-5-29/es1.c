// Scrivere un programma con un solo parametro.
// Come prima cosa il programma deve creare una directory con il path specificato nel parametro. Se la directory esiste gia' o si
// verifica un errore nella creazione, il programma deve terminare. Chiameremo questa directory “directory-base”
// Il programma usando inotify rimane in attesa e stampa una riga di log per ogni file o directory creato o cancellato nella
// directory-base. (solo nella directory-base, non nelle sottodirectory).
// Quando viene cancellata la directory-base il programma termina.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <errno.h>
//#include <linux/inotify.h>

int argError(int argc, int n){
      if (argc != n){
            fprintf(stderr, "Expected 1 parameter - %s\n", strerror(errno));
            return -1;
      }
}

//il sito di linux mi consigliava questa lunghezza per qualche buffer però non ho capito che buffer
//sizeof(struct inotify_event) + NAME_MAX + 1

//quello che segue l'ho copiato da qualche parte però boh

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main(int argc, char const *argv[]) {

      struct stat exist;
      int fd;           //questo è l'inotify
      int dirBase;
      int length;
      char buffer[EVENT_BUF_LEN];
      int i=0;

/*-----a bunch of errors----*/

      if (argError(argc,2) == -1)
            return -1;


      if (stat(argv[1], &exist) == -1) {
            if (mkdir(argv[1],0777) == -1) {

                  fprintf(stderr, "Error : Faild to create directory - %s\n", strerror(errno));
                  return -1;
            }
      }else{
            fprintf(stderr, "Directory already exist - %s\n", strerror(errno));
            return -1;
      }

/*-------------------------*/

/*creating the INOTIFY instance*/
      fd = inotify_init();
      if ( fd < 0 ) {
            perror( "inotify_init" );
      }

      /*adding the “/tmp” directory into watch list. Here, the suggestion is to validate the existence of the directory before adding into monitoring list.*/
      dirBase = inotify_add_watch( fd, argv[1], IN_CREATE | IN_DELETE | IN_DELETE_SELF );
      //IN_CREATE | IN_DELETE |
      /*read to determine the event change happens on “/tmp” directory. Actually this read blocks until the change event occurs*/
      //length = read( fd, buffer, EVENT_BUF_LEN );

      /*checking for error*/
      //if ( length < 0 ) {
      //      perror( "read" );
      //}

      /*actually read return the list of change events happens. Here, read the change event one by one and process it accordingly.*/
while(1){
      length = read( fd, buffer, EVENT_BUF_LEN );

      /*checking for error*/
      if ( length < 0 ) {
            perror( "read" );
            break;
      }
      i=0;
      while ( i < length ) {
             struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
             if ( event->len ) {
                   if ( event->mask & IN_CREATE ) {
                         if ( event->mask & IN_ISDIR ) {
                               printf( "New directory %s created.\n", event->name );
                         }
                         else {
                               printf( "New file %s created.\n", event->name );
                         }
                   }
                   else if ( event->mask & IN_DELETE ) {
                         if ( event->mask & IN_ISDIR ) {
                               printf( "Directory %s deleted.\n", event->name );
                         }
                         else {
                               printf( "File %s deleted.\n", event->name );
                         }
                   }

             }
             if ( event->mask & IN_DELETE_SELF ) {
                   printf( "Directory-base  deleted.\n", event->name );
                   inotify_rm_watch( fd, dirBase );
                   close( fd );
                   return 0;
            }
             i += EVENT_SIZE + event->len;
       }




// length = read( fd, buffer, EVENT_BUF_LEN );
//
// /*checking for error*/
// if ( length < 0 ) {
//       perror( "read" );
//       printf("errore\n");
// }
// i=0;
// while ( i < length ) {
//       struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
//       printf("Sonoqui %s\n", event->len);
//       //if ( event->len ) {
//             printf("Sono qui\n");
//             if ( event->mask & IN_DELETE_SELF ) {
//                    printf( "Directory-base  deleted.\n", event->name );
//                    inotify_rm_watch( fd, dirBase );
//                    close( fd );
//                    return 0;
//             }
//       //}
//       i += EVENT_SIZE + event->len;
//  }

}



  /*removing the “/tmp” directory from the watch list.*/
   inotify_rm_watch( fd, dirBase );

  /*closing the INOTIFY instance*/
   close( fd );



      return 0;
}
