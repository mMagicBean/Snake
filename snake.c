#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define UNIX    1
#define WINDOWS 2

#define OS WINDOWS

#define WIDTH 32
#define HEIGHT 16

#define KEYUP    72
#define KEYDOWN  80
#define KEYLEFT  75
#define KEYRIGHT 77


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


void handle_input(Snake* snake); 


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

void update_snake(Grid* grid, Snake* snake, bool is_running) {
  grid->tiles[snake->ypos][snake->xpos += 1] = 'o';
  
  // basic non-char repeating snake code 
  if (grid->tiles[snake->ypos][snake->xpos - 1] == 'o') {
    grid->tiles[snake->ypos][snake->xpos - 1] = '-';
  }
  
  if (snake->ypos >= HEIGHT || snake->ypos < 0) {
    printf("Game over\n");
    exit(0);
  }

  // cause game over later on 
  if (snake->xpos >= WIDTH || snake->xpos < 0 ) {
    printf("Game over\n");
    exit(0);
  }
}


void mainloop(bool is_running) {
  snake.xpos = 0;
  snake.ypos = 0;
  
  while(is_running == true) {
    draw_grid(&grid);
    update_snake(&grid, &snake, is_running);
    system("cls");
  }
}


int main() {
  create_grid(&grid);
  create_snake(&snake);
  mainloop(true);
}
