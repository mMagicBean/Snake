#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>

#define UNIX    1
#define WINDOWS 2

#define OS WINDOWS

#define WIDTH 32
#define HEIGHT 16

#define KEYUP    72
#define KEYDOWN  80
#define KEYLEFT  75
#define KEYRIGHT 77
#define ESCAPE   27


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

void read_input(Grid* grid, Snake* snake) {
  char c = getch();

  switch(c) {
  case ESCAPE:
    exit(0);
    break;
    
  case KEYUP:
    grid->tiles[snake->ypos -= 1][snake->xpos] = 'o';
    break;
    
  case KEYDOWN:
    grid->tiles[snake->ypos += 1][snake->xpos] = 'o';
    break;

  case KEYLEFT:
    grid->tiles[snake->ypos][snake->xpos -= 1] = 'o';
    break;

  case KEYRIGHT:
    grid->tiles[snake->ypos][snake->xpos += 1] = 'o';
    break;
  }
}


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

  
/*
void update_grid(Grid* grid, Snake* snake) {
  int score = 0;
  time_t t;
  srand((unsigned) time(&t));

  //int random_ypos = rand() % HEIGHT;
  //int random_xpos = rand() % WIDTH;
  
  int random_ypos = 0;
  int random_xpos = 8;
  
  grid->tiles[random_ypos][random_xpos] = '%';

  // check if snake overlaps with apple
  if (grid->tiles[snake->ypos][snake->xpos] == grid->tiles[random_ypos][random_xpos]) {
    score++;
    //grid->tiles[random_ypos][random_xpos] = '-';
    //grid->tiles[snake->ypos][snake->xpos - score] == 'o';
  }
}
*/


void update_snake(Grid* grid, Snake* snake) {
  int score = 1;
  
  //time_t t;
  //srand(time(NULL));
  
  //int random_ypos = rand() % HEIGHT;
  //int random_xpos = rand() % WIDTH;
  
  int random_ypos = 2;
  int random_xpos = 8;
  
  grid->tiles[random_ypos][random_xpos] = '%';

  // check if snake overlaps with apple
  if (grid->tiles[snake->ypos][snake->xpos] == grid->tiles[random_ypos][random_xpos]) {
    score++;
    grid->tiles[random_ypos][random_xpos] = '-';
    grid->tiles[snake->ypos][snake->xpos - score] == 'o';
  }

  //grid->tiles[snake->ypos][snake->xpos += 1] = 'o';
  
  // overwrite leftover snake symbol from left to right
  if (grid->tiles[snake->ypos][snake->xpos - score] == snake->sprite) {
    grid->tiles[snake->ypos][snake->xpos - score] = '-';
  }

  // overwrite leftover snake symbol from up to bottom
  if (grid->tiles[snake->ypos - score][snake->xpos] == snake->sprite) {
    grid->tiles[snake->ypos - score][snake->xpos] = '-';
  }

  // overwrite leftover snake symbol from right to left
  if (grid->tiles[snake->ypos][snake->xpos + score] == snake->sprite) {
    grid->tiles[snake->ypos][snake->xpos + score] = '-';
  }
  
  // overwrite leftover snake symbol from bottom to up
  if (grid->tiles[snake->ypos + score][snake->xpos] == snake->sprite) {
    grid->tiles[snake->ypos + score][snake->xpos] = '-';
  }
		  
  if (snake->ypos > HEIGHT + 1 || snake->ypos < 0) {
    printf("Game over\n");
    exit(0);
  }

  if (snake->xpos > WIDTH + 1 || snake->xpos < 0 ) {
    printf("Game over\n");
    exit(0);
  }
}


void mainloop(bool is_running) {
  snake.xpos = 0;
  snake.ypos = 0;
  
  while(is_running == true) {
    draw_grid(&grid);
    read_input(&grid, &snake);
    update_snake(&grid, &snake);
    system("cls");
  }
}


int main() {
  create_grid(&grid);
  create_snake(&snake);
  mainloop(true);
}
