#include <unistd.h>
#include <termio.h>
#include <stdio.h>
#include <stdlib.h>

#define passLength 100

int main(int argc, char **argv)
{
    struct termio tio, tin;
    char* password = (char*)malloc(passLength);
    char* b = password;

    ioctl(0, TCGETA, &tio);
    tin = tio;
    tin.c_lflag &= ~ECHO; /* turn off ECHO */
    /*
    * Set the new modes. Again we ignore return
    * values.
    */
    ioctl(0, TCSETA, &tin);

    char selected;
    int order = 0;
    printf("Enter password: ");
    do {
        selected = fgetc(stdin);
        if ((selected == '\b') && (order > 0))
        {
            order--;
            password--;
            *password = '\0';
        } else if ((selected != '\n') && (selected != '\r') && (selected != '\b')) {
            *password++ = selected;
            order++;
            fflush(stdout);
        }
    } while ((selected!='\n')&&(selected!='\r')&&(order < passLength));
    password[order] = '\0';
    /*
    * Reset the old tty modes.
    */
    ioctl(0, TCSETA, &tio);
    fprintf(stdout, "\nYou entered: %s\n", b);
    free(b);
    exit(0);
}
