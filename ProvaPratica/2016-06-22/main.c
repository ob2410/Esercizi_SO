#include "checkgroup.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

      int ret;
      ret=checkgroup(argv[1], argv[2]);
      printf("Return: %d\n", ret );


      return 0;
}
