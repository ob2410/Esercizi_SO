// Scrivere la funzione:
//       char **get_user_groups(void);
// che deve restituire un array (generato dinamicamente) di stringhe (anch'esse allocate dinamicamente) contenente
// lo username relativo all'uid del processo chiamante nel primo elemento  (indice 0). Gli elementi successivi del
// vettore dovranno contenere gli identificativi di tutti i gruppi al quale l'utante appartiene. L'array è terminato
// con un elemento nullo.
//
// Produrre anche la funzione
//       void free_user_group(char **v);
// che deallochi un vettore generato dalla get_user_groups;
//
// Anche in questo caso si chiede un modulo formato dai file get_user_groups.c get_user_groups.h, un file main.c
// di prova e un Makefile. Il main verrà chiamato senza parametri
#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF 24

//allocare usando il BUF di sopra non è la soluzione più elegante ma non mi andava di pensare a come fare

char **get_user_groups(void){

      int j, ngroups;
      gid_t *groups;
      struct passwd *pw;
      struct group *gr;
      uid_t uid;
      char *user;
      char *gid;
      char **ret;

      ngroups=0;
      //get the uid
      uid = getuid();
      /* Fetch passwd structure from uid */

      pw = getpwuid(uid);
      if (pw == NULL) {
          //perror("getpwnam");
          printf("User doesn't exist\n");
          exit(1);
      }

      user=pw->pw_name;



      //check how many groups are assosieted with this user

      groups = malloc(ngroups * sizeof (gid_t));
      if (groups == NULL) {
          perror("malloc");
          return NULL;
      }

      if (getgrouplist(user, pw->pw_gid, groups, &ngroups) != -1) {
          //se entriamo qui vuol dire che allo user non è associato nessun gruppo,
          //ne deduco che l'utente non esiste
          printf("Non è in nessun gruppo \n" );
          return NULL;

     }
     groups = malloc(ngroups * sizeof (gid_t));
     if (groups == NULL) {
         perror("malloc");
         return NULL;
     }
     getgrouplist(user, pw->pw_gid, groups, &ngroups);

     printf("Ci sono %d\n", ngroups );

     ret=malloc((ngroups+2)*sizeof( char* ));

     for (j=0 ; j < (ngroups+2); j++){
           printf("Sono nel ciclo %d\n", j );
           if (j==0){
                  printf("Sono l'utente\n");
                  ret[j]=malloc(sizeof(user));
                  ret[j]=user;
                  printf("%s\n",ret[j]);

            }
             else if (j==(ngroups+1)){
                   printf("Sono dentro %d\n", j );
                   ret[j]=malloc(sizeof(NULL));
                   printf("Ho allocato\n");
                   ret[j]=NULL;
                   // printf("%s\n",ret[j]);
             }
            else {

                   gr = getgrgid(groups[j-1]);
                   if (gr != NULL){
                        /*Voglio provare a fare senza malloc*/
                       ret[j]=malloc(BUF);
                       sprintf(ret[j], "%d", gr->gr_gid);
                       printf("grupid %d \n", gr->gr_gid);
                 }
           }
                  printf("gruppi%d\n",ngroups );
                 printf("\n");
             //printf("%s\n",ret[j]);

     }

     return ret;


}


 void free_user_group(char **v){
       int j=0;
       while (v[j]!=NULL){
             free(v[j]);
             j++;
       }
       free(v[j]);
       free(v);
 }
