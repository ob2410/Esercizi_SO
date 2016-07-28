

#ifndef _check_group_h
#define _check_group_h

#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>


char **get_user_groups(void);
void free_user_group(char **v);


#endif
