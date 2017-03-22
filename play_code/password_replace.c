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
    tin.c_lflag &= ~ICANON; /* turn off ICANON */
    tin.c_lflag &= ~ISIG;
    tin.c_cc[VINTR] = 1;
    tin.c_cc[VMIN] = 1;
    tin.c_cc[VTIME] = 0;
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
            fputc('\b',stdout);
            fputc(' ',stdout);
            fputc('\b',stdout);
            order--;
            password--;
            *password='\0';
        } else if ((selected != '\n') && (selected != '\r') && (selected != '\b')) {
            *password++ = selected;
            order++;
            fputc('*', stdout);
            fflush(stdout);
        }
    } while ((selected!='\n')&&(selected!='\r')&&(order>=0)&&(order <= passLength));
    /*
    * Reset the old tty modes.
    */
    ioctl(0, TCSETA, &tio);
    fprintf(stdout, "\nYou entered: %s\n", b);
    free(b);
    exit(0);
}
