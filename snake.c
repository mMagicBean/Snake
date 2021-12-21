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
  //int x, y;
  //char width[WIDTH];
  //char height[HEIGHT];
  char tiles[HEIGHT][WIDTH];
  int size;
  
}Grid;


typedef struct Snake {
  //char pos[HEIGHT][WIDTH];
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
  // fill the grid with - symbols
  grid->size = sizeof(HEIGHT * WIDTH);

  //printf("%d\n", grid->size);
  for (int i=0; i <= HEIGHT; i++) {
    //grid->tiles[i][0] = '-';
    
    for (int j=0; j <= WIDTH; j++) {
      grid->tiles[i][j] = '-';
    }
  }
}


//NOTE: i want to draw the grid seperately and
//      use the snake to manipulate the tiles 
void create_snake(Snake* snake) {
  snake->xpos = 0;
  snake->ypos = 0;

  snake->sprite = 'o';
}

// this function might not be actually drawing a grid
// the way i think it is 
void draw_grid(Grid* grid) {
  for (int i=0; i <= HEIGHT; i++) {
    //printf("%c", grid->tiles[i][0]);
    
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

// NOTE: i need to sync the framerate and the movement on char swapping
//       in order for this to work smoothly
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
