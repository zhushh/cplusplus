/***********************************************************************
 *  > File Name: dcl_and_dirdcl_new_update.c
 *  > Author: zhushuhuang
 *  > Mail: zsh5318@gmail.com
 *  > Created Time: Mon 11 Aug 2014 11:40:42 PM CST
***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
void errmsg(char *);
int gettoken(void);

extern int tokentype;       /* type of last token */
extern char token[];        /* last token string */
extern char name[];         /* identifier name */
extern char datatype[];          /* data type = char, int, etc. */
extern char out[];
extern int prevtoken;

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';)    /* count *'s */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declaration */
void dirdcl(void)
{
    int type;
    void parmdcl(void);

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            errmsg("error: missing )\n");
    } else if (tokentype == NAME) {
        if (name[0] == '\0')
            strcpy(name, token);
    } else
        prevtoken = YES;
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function expecting");
            parmdcl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* errmsg: print error message and indicate avail. token */
void errmsg(char *msg)
{
    printf("%s", msg);
    prevtoken = YES;
}

