/***********************************************************************
 *  > File Name: tail.c
 *  > Author: zhushuhuang
 *  > Mail: zsh5318@gmail.com
 *  > Created Time: Mon 11 Aug 2014 02:31:09 PM CST
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFLINES 10     /* default # of lines to print  */
#define LINES   100     /* max # of lines to print      */
#define MAXLEN  100     /* max length of an input line  */

void error(char *);

/* print last n lines of the input */
int main(int argc, char *argv[])
{
    FILE *fp;
    char *p;
    char *buf;              /* pointer to larger buffer */
    char *bufend;           /* end of the buffer */
    char line[MAXLEN];      /* current input line */
    char *lineptr[LINES];   /* pointers to lines read */
    int first, i, last, len, n, nlines;

    if (argc == 2)          /* not argument present */
        n = DEFLINES;       /* use default # of lines */
    else if (argc == 3 && (*++argv)[0] == '-')
        n = atoi(argv[0]+1);
    else
        error("Usage:   tail [-n]");
    if (n < 1 || n > LINES)     /* unreasonable value for n? */
        n = LINES;
    for (i = 0; i < LINES; ++i)
        lineptr[i] = NULL;
    if ( (p = buf = (char*)malloc(LINES * MAXLEN)) == NULL )
        error("tail: can't allocate buf");
    bufend = buf + LINES * MAXLEN;
    fp = fopen(*++argv, "r");
    last = 0;                   /* index of last line read */
    nlines = 0;                 /* number of lines read */
    while ( fgets(line, MAXLEN, fp) != NULL ) {
        len = strlen(line);
        if (p + len + 1 >= bufend)
            p = buf;            /* buffer wrap around */
        lineptr[last] = p;
        strcpy(lineptr[last], line);
        if (++last >= LINES)
            last = 0;           /* ptrs to buffer wrap around */
        p += len + 1;
        nlines++;
    }
    if (n > nlines)             /* req. lines more than rec.? */
        n = nlines;
    first = last - n;
    if (first < 0)              /* it did wrap around the list */
        first += LINES;
    for (i = first; n-- > 0; i = (i + 1) % LINES)
        printf("%s", lineptr[i]);
    fclose(fp);
    return 0;
}

/* error: print error message and exit */
void error(char *s)
{
    printf("%s\n", s);
    exit(1);
}
