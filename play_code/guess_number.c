/*************************************************************************
	> File Name: guess_number.c
	> Author: zhushh
	> Mail: 
	> Created Time: Fri 21 Nov 2014 01:29:32 AM CST
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
#define M_time 10

void init() {
    printf("Input '0' for quit.\n");
    printf("Input 's' for start.\n");
    // printf("Input 'p' for pause.\n");
    printf("Input 'l' for selecting a level.\n");
    printf("Input 'r' for restart.\n");
    printf("Please select a choice: ");
}

char getChoice() {
    char choice[20];
    while (1) {
        fgets(choice, sizeof(choice), stdin);
        if (choice[1] != '\n') {
            printf("Please input the right choice: ");
        } else if (choice[0] != '0' && choice[0] != 's' /*&& choice[0] != 'p'*/ &&
                   choice[0] != 'l' && choice[0] != 'r') {
            printf("Please input the right choice: ");
        } else {
            return choice[0];
        }
    }
}
char select_level() {
    char choice[10];
    printf("Please select a level.\n");
    printf("Input 'h' for hard.\n");
    printf("Input 'm' for middle.\n");
    printf("Input 'e' for easy.\n");
    printf("Please input a choice: ");
    while (1) {
        fgets(choice, sizeof(choice), stdin);
        if (choice[1] != '\n') {
            printf("Please input the right choice: ");
        } else if (choice[0] != 'h' && choice[0] != 'm' && choice[0] != 'e') {
            printf("Please input the right choice: ");
        } else {
            return choice[0];
        }
    }
}

int create_random_number(int max) {
    srand(time(NULL));
    return rand() % max + 1;
}

int main(void) {
    int ans, input;
    char op, level = 'e';
    printf("Welcome play the guess number game.\n");
    init();
    while ((op = getChoice()) != '0') {
        if ('l' == op) {
            level = select_level();
            init();
            continue;
        }
        int max = 'e' == level ? 1000 : 'm' == level ? 2000 : 4000;
        ans = create_random_number(max);
        int guess_time = 0;
        printf("Start guess number.\nPlease input the number. The max number is %d\n", max);
        scanf("%d", &input);
        getchar();    // read the newline
        while (guess_time <= M_time) {
            if (ans == input) {
                printf("Great! you guess the number right. you win.\n");
                init();
                break;
            } else if (ans > input) {
                printf("You guess the number have a little small.\n");
            } else {
                printf("You guess the number have a little higher.\n");
            }
            if (guess_time == M_time) {
                printf("You have no choice to guess, you failed, the right number is %d\n", ans);
                break;
            } else {
                printf("Please try again.\n");
                scanf("%d", &input);
                getchar();    // read the newline
            }
            guess_time++;
        }
    }
    return 0;
}

