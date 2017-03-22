#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

// getch function
int getch();

// control the snake movement and product its body.
void snakemove(int a, int b);
// print the scores users got.
void put_score(void);
// drawl game interface.
void output(void);
// outs when gameover.
void gameover(void);
// product the food on the blank_cell.
void foodproduction(void);
// make snake move automaticlly.
void snake_move_auto();

// the initial condition of the game.
char map[13][13]=
     {"************",
     "*XXXXH     *",
     "*          *",
     "*          *",
     "*          *",
     "*          *",
     "*     $    *",
     "*          *",
     "*          *",
     "*          *",
     "*          *",
     "************"};

int snakeX[SNAKE_MAX_LENGTH]={1, 2, 3, 4, 5};
int snakeY[SNAKE_MAX_LENGTH]={1, 1, 1, 1, 1};
int snakeLength = 5;

int main() {
    int i, count;
    char c;
    system("clear");
    output();
    while (1) {
		if (c = getch()) {
        	switch (c) {
				case 'w':
            	case 'W': snakemove(0, -1); break;
            	case 'a':
            	case 'A': snakemove(-1, 0); break;
            	case 's':
            	case 'S': snakemove(0, 1); break;
            	case 'd':
            	case 'D': snakemove(1, 0); break;
            	default : break;
        	}
		}
        system("clear");
        output();
        if (snakeLength == 0) break;
    }
    printf("\nPlease press any key to end: \n");
    getch();
    return 0;
}

void snakemove(int a, int b) {
    int i, x, y;
    x = snakeX[snakeLength-1] + a;
    y = snakeY[snakeLength-1] + b;
    // determine whether the snake is moving back.
    if (snakeX[snakeLength-2] == snakeX[snakeLength-1] + a) {
        if (snakeY[snakeLength-2] == snakeY[snakeLength-1] + b) {
            return;
        }
    }
    // snake moves normally if it did not eat the food.
    if (map[y][x] != SNAKE_FOOD) {
        map[snakeY[0]][snakeX[0]] = BLANK_CELL;
        for (i = 0; i < snakeLength - 1; i++) {
            snakeX[i] = snakeX[i+1];
            snakeY[i] = snakeY[i+1];
            map[snakeY[i]][snakeX[i]] = SNAKE_BODY;
        }
        snakeX[snakeLength-1] = snakeX[snakeLength-1] + a;
        snakeY[snakeLength-1] = snakeY[snakeLength-1] + b;
        map[snakeY[snakeLength-1]][snakeX[snakeLength-1]] = SNAKE_HEAD;
        return;
    }
    // product snake body if the snake ate the food.
	else {
        // determine whether users win.
        if (snakeLength + 1 > SNAKE_MAX_LENGTH) {
            snakeLength = 0;
        }
        // the production of the snake body and another food.
		else {
            map[snakeY[snakeLength-1]][snakeX[snakeLength-1]] = SNAKE_BODY;
            snakeLength = snakeLength + 1;
            snakeX[snakeLength-1] = x;
            snakeY[snakeLength-1] = y;
            map[snakeY[snakeLength-1]][snakeX[snakeLength-1]] = SNAKE_HEAD;
            foodproduction();
        }
    }
}
// make snake move once automatically
void snake_move_auto() {
    if (snakeX[0] == snakeX[1]) {
		snakemove(1, 0);
    } else if (snakeY[0] == snakeY[1]) {
		snakemove(0, 1);
    }
}

void gameover() {
    int i;
    // return if users win.
    if (snakeLength == 0) return;
    // determine whether the snake hits against the wall.
    else if (snakeX[snakeLength-1] >= 11 || snakeX[snakeLength-1] <= 0
          || snakeY[snakeLength-1] <= 0 || snakeY[snakeLength-1] >= 11) {
        snakeLength = 0;
        printf("Game Over!!!\n");
    }
    // determine whether the snake bits itself.
	else {
        for (i = 0; i < snakeLength - 1; i++) {
            if (snakeX[i] == snakeX[snakeLength-1]) {
                if (snakeY[i] == snakeY[snakeLength-1]) {
                    snakeLength = 0;
                    printf("Game Over!!!\n");
                }
            }
        }
    }
}

void output() {
    int i;
    // if user do not win, print the game interface.
    if (snakeLength) {
        for (i = 0; i < 12; i++) {
            printf("%s\n", map[i]);
        }
    } else {
        printf("YOU ARE WIN!!!\n");
    }
    gameover();
}

void foodproduction(void) {
    int i, foodX, foodY, foodnumber = 0;
    srand(time(0));
    while (foodnumber == 0) {
        foodX = 1 + rand()%9;  // creat the food coordinate randomly.
        foodY = 1 + rand()%9;
        foodnumber = 1;
        // determine whether the coordinate of the food is one of the snake.
        for (i = 0; i < snakeLength; i++) {
            if (foodX == snakeX[i]) {
                if (foodY == snakeY[i]) {
                    foodnumber = 0;
                }
            }
        }
        // product the food if all the condition was satisfied.
        if (foodnumber != 0) {
            map[foodY][foodX] = '$';
        }
    }
    return;
}

#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios tm, tm_old;
    int fd = STDIN_FILENO, c;

    if (tcgetattr(fd, &tm) < 0) {
        return -1;
    }

    tm_old = tm;
    cfmakeraw(&tm);

    if (tcsetattr(fd, TCSANOW, &tm) < 0) {
        return -1;
    }

    c = fgetc(stdin);

    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
        return -1;
    }

    return c;
}
