#ifndef PATH_ALLOC_H
#define PATH_ALLOC_H

#include <errno.h>
#include <limits.h>
#include "new_err.h"
#include <unistd.h>

/*
 * #include <unistd.h>
 * 
 * long sysconf(int name);
 * log pathconf(const char *pathname, int name);
 * log fpathname(int filedes, int name);
 */

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define PATH_MAX_GUSS 1024 /* if PATH_MAX is indeterminate */
                /* we're not guaranteed this is adequate */

/* also return allocated size, if nonnull */
char * path_alloc(int *size) {
    char *ptr;
    
    if (pathmax == 0) {     /* first time through */
        errno = 0;
        if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if (errno == 0)
                pathmax = PATH_MAX_GUSS;    /* it is indeterminate */
            else
                err_sys("pathconf error for _PC_PATH_MAX");
        } else {
            pathmax++;      /* add one since it's relative to root */
        }
    }

    if ((ptr = malloc(pathmax + 1)) == NULL)
        err_sys("malloc error for pathname");

    if (size != NULL)
        *size = pathmax + 1;
    return (ptr);
}

#endif  /* PATH_ALLOC_H */
