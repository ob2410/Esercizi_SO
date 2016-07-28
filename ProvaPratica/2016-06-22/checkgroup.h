#ifndef _check_group_h
#define _check_group_h

#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

int checkgroup(const char *user, const char *group);

#endif
