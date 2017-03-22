#include <stdio.h>
#include "path_alloc.h"

int main() {
    char * pathsize;
    int size;
    pathsize = path_alloc(&size);
    printf("path size is %d\n", size);
    return 0;
}

