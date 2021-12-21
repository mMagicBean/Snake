#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define UNIX    1
#define WINDOWS 2

#define OS WINDOWS

#define WIDTH 32
#define HEIGHT 16


typedef struct Grid {
  char tiles[HEIGHT][WIDTH];
  int size;
  
}Grid;


typedef struct Snake {
  int xpos;
  int ypos;
  
  char sprite;
  
}Snake;


Grid grid;
Snake snake;


char swap_chars(char current, char new) {
  if (current == '-') {
    return new;
  }
}
 

void create_grid(Grid* grid) {
  grid->size = sizeof(HEIGHT * WIDTH);

  for (int i=0; i <= HEIGHT; i++) {
    for (int j=0; j <= WIDTH; j++) {

      grid->tiles[i][j] = '-';
    }
  }
}


void create_snake(Snake* snake) {
  snake->xpos = 0;
  snake->ypos = 0;

  snake->sprite = 'o';
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

void draw_snake(Snake* snake, Grid* grid) {  
  snake->ypos = 14;
  snake->xpos = 2;
  
  grid->tiles[snake->ypos][snake->xpos] = 'o';
}


void update_snake(Snake* snake, Grid* grid) {
  
}

void mainloop(bool is_running) {
  while(is_running == true) {
    draw_grid(&grid);
    draw_snake(&snake, &grid);
    sleep(1);
    system("cls");
  }
}


int main() {
  create_grid(&grid);
  create_snake(&snake);
  mainloop(true);
}
