// scrivere la funzione :
//       int checkgroup(const char *user, const char *group);
// che deve restituire:
//       0 se l'utente non appartiene al gruppo;
//       1 se l'utente appartiene al gruppo;
//       -1 in caso di errore (es. l'utente non esiste).
// Creare i file checkgroup.c, checkgroup.h e un file main.c contenente un programma principale che prenda come
// argv[1] e argv[2] i due parametri della funione e ne stampi il risultato. Produrre un Makefile opportuno


#include "checkgroup.h"

int checkgroup(const char *user, const char *group){

           int j, ngroups;
           gid_t *groups;
           struct passwd *pw;
           struct group *gr;


      //      if (argc != 3) {
      //          fprintf(stderr, "Usage: %s <user> <ngroups>\n", argv[0]);
      //          exit(EXIT_FAILURE);
      //      }

           ngroups = 0;


           groups = malloc(ngroups * sizeof (gid_t));
           if (groups == NULL) {
               perror("malloc");
               return -1;
           }
           /* Fetch passwd structure (contains first group ID for user) */

           pw = getpwnam(user);
           if (pw == NULL) {
               //perror("getpwnam");
               printf("User doesn't exist\n");
               return -1;
           }

           /* Retrieve group list */

           if (getgrouplist(user, pw->pw_gid, groups, &ngroups) != -1) {
               //se entriamo qui vuol dire che allo user non è associato nessun gruppo,
               //ne deduco che l'utente non esiste
               printf("Non è in nessun gruppo \n" );
               return -1;

           }

//la chiamata prima in teoria ci dice in quanti gruppi sta lo user e ora la richiamo per recuperare effettivamente in quanti gruppi sta

           groups = malloc(ngroups * sizeof (gid_t));
           if (groups == NULL) {
               perror("malloc");
               return -1;
           }
           getgrouplist(user, pw->pw_gid, groups, &ngroups);
           /* Display list of retrieved groups, along with group names */

           fprintf(stderr, "ngroups = %d\n", ngroups);
           for (j = 0; j < ngroups; j++) {
               //qui stampa i nomi e l'id dei gruppi
               printf("%d", groups[j]);
               gr = getgrgid(groups[j]);
               if (gr != NULL)
                   printf(" (%s)", gr->gr_name);
               printf("\n");
               //da qui controllo se c'è il gruppo che cerco
               if (!strcmp(gr->gr_name,group)){
                     return 1;
               }
           }

           return 0;
}
