/* Error routines for program that can run as a daemon */

#ifndef _LOG_ERR_H_
#define _LOG_ERR_H_

#include <errno.h>      /* for definition of errno. */
#include <stdarg.h>     /* ANSI C header file */
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAXLINE
#define MAXLINE 4096
#endif

static void log_doit(int, int, const char *, va_list ap);

extern int debug;       /* caller must define and set this:
                            nonzero if interactive, zero if deamon */

/* Nonfatal error unrelated to a system call.
 * Print a message and return. */

void
log_msg(const char *fmt, ...) {
    va_list     ap;
    va_start(ap, fmt);
    log_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    return;
}

/* Initialize syslog(), if running as deamon. */
void
log_open(const char *ident, int option, int facility) {
    if (debug == 0)
        openlog(ident, option, facility);
}

/* Fatal error unrelated to system call.
 * Print a message and terminate. */

void
log_quit(const char *fmt, ...) {
    va_list     ap;
    va_start(ap, fmt);
    log_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/* Nonfatal error related to a system call.
 * Print a message with the system's errno value and return */

void
log_ret(const char *fmt, ...) {
    va_list     ap;
    va_start(ap, fmt);
    log_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    return;
}
/* Fatal error related to system call.
 * Print a message and terminate. */

void
log_sys(const char *fmt, ...) {
    va_list     ap;
    va_start(ap, fmt);
    log_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/* Print a message and return to caller.
 * Caller specifies "errnoflag" and "priority". */

static void
log_doit(int errnoflag, int priority, const char *fmt, va_list ap) {
    int     errno_save;
    char    buf[MAXLINE];

    errno_save = errno;     /* value caller might want printed */
    vsprintf(buf, fmt, ap);
    if (errnoflag)
        sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
    strcat(buf, "\n");
    if (debug) {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    } else {
        syslog(priority,"%s", buf);
    }
    return;
}

#endif      /* _LOG_ERR_H_ */
