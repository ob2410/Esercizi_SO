#include "get_user_groups.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

      char **prova;
      int j=0;
      prova=get_user_groups();

      while (prova[j]!=NULL){
            printf("%s\n",prova[j] );
            j++;
      }
      free_user_group(prova);

      return 0;
}
