#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define ESCAPE 27

int score = 3;

bool moving_right;
bool moving_left;
bool moving_up;
bool moving_down;

void init_snake(Snake* snake) {
  snake->xpos = 10;
  snake->ypos = 10;
}

void init_grid(Grid* grid) {
  for (int i=0; i <= HEIGHT; i++) {
    for (int j=0; j <= WIDTH; j++) {
      grid->tiles[i][j] = '-';
    }
  }
}


void draw_grid(Grid* grid) {
  for (int i=0; i <= HEIGHT; i++) {
    for (int j=0; j <= WIDTH; j++) {
      printf("%c", grid->tiles[i][j]);
      
      if (j >= WIDTH) {
	printf("\n");
      }
    }
  }
}

int handle_keys(Grid* grid, Snake* snake) {
  char c;

  if (kbhit()) {
    
    c = getch();

    switch (c) {
      
    case 'w':
      moving_up = true;
      moving_down = false;
      moving_right = false;
      moving_left = false;
      break;
      
    case 'a':
      moving_left = true;
      moving_up = false;
      moving_down = false;
      moving_right = false;
      break;

    case 's':
      moving_down = true;
      moving_up = false;
      moving_right = false;
      moving_left = false;
      break;
      
    case 'd':
      moving_right = true;
      moving_down = false;
      moving_up = false;
      moving_left = false;

      break;
      
    case ESCAPE:
      exit(0);
      break;
      
    }
  }
  
  if (moving_up) {
    grid->tiles[snake->ypos--][snake->xpos] = 'o';
  }
  
  if (moving_right) {
    grid->tiles[snake->ypos][snake->xpos++] = 'o';
  }
    
  if (moving_left) {
    grid->tiles[snake->ypos][snake->xpos--] = 'o';
  }
  
  if (moving_down) {
    grid->tiles[snake->ypos++][snake->xpos] = 'o';
  }

  printf("value of c = %c\n", c);  
  
  printf("getch() = %c\n", c);
  printf("score = %d\n", score);
  
  return 0;
}

int main() {
  Grid grid;
  Snake snake;

  init_snake(&snake);
  init_grid(&grid);

  for (;;) {
    handle_keys(&grid, &snake);
    draw_grid(&grid);
        
    system("cls");
  }

  return 0;
}
