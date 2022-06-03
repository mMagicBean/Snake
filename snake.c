#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_LENGTH 512

#define ESCAPE 27

bool moving_right;
bool moving_left;
bool moving_up;
bool moving_down;



void init_snake(Snake snake[]) {
  memset(snake, 0, MAX_LENGTH);
  snake[0].x = 10;
  snake[0].y = 10;
}

 
void init_grid(Grid* grid) {
  for (int i=0; i <= HEIGHT; i++) {
    for (int j=0; j <= WIDTH; j++) {
      // interior of the grid
      grid->tiles[i][j] = ' ';

      // borders
      grid->tiles[i][0]      = '+';
      grid->tiles[0][j]      = '+';
      grid->tiles[HEIGHT][j] = '+';
    }
  }
}

void draw_grid(Grid* grid) {
  // draw grid
  for (int i=0; i <= HEIGHT; i++) {
    for (int j=0; j <= WIDTH; j++) {
      printf("%c", grid->tiles[i][j]);

      if (j >= WIDTH) {
	printf("\n");
      }
    }
  }
}


int move_snake(Grid* grid, Snake snake[]) {  
  char c;
    
  static int score = 0;

  if (snake[0].y == 2 && snake[0].x == 6) {
    score += 1;
  }


  get_prev_pos(snake, score);
  

  if (kbhit()) {
    
    c = getch();

    switch (c) {
      
    case 'w':
      moving_up    = true;
      moving_down  = false;
      moving_right = false;
      moving_left  = false;
      break;
      
    case 'a':
      moving_left  = true;
      moving_up    = false;
      moving_down  = false;
      moving_right = false;
      break;

    case 's':
      moving_down  = true;
      moving_up    = false;
      moving_right = false;
      moving_left  = false;
      break;
      
    case 'd':
      moving_right = true;
      moving_down  = false;
      moving_up    = false;
      moving_left  = false;
      break;
      
    case ESCAPE:
      exit(0);
      break;      
    }
  }
  
  if (moving_up) {
    grid->tiles[snake[0].y--][snake[0].x] = 'o';
  }
  
  if (moving_right) {
    grid->tiles[snake[0].y][snake[0].x++] = 'o';
  }
  
  if (moving_left) {
    grid->tiles[snake[0].y][snake[0].x--] = 'o';
  }
  
  if (moving_down) {
    grid->tiles[snake[0].y++][snake[0].x] = 'o';
  }

  if (score > 0) {
    snake[score] = get_prev_pos(snake, score);
  }
  
  draw_snake_body(grid, snake, score);
  
  printf("score = %d\n", score);

  printf("snake[0] = %d, %d\n", snake[0].x, snake[0].y);
  printf("snake[1] = %d, %d\n", snake[1].x, snake[1].y);
  printf("snake[2] = %d, %d\n", snake[2].x, snake[2].y);
  printf("snake[3] = %d, %d\n", snake[3].x, snake[3].y);
  printf("snake[4] = %d, %d\n", snake[4].x, snake[4].y);
  
  return 0;
}

Snake get_prev_pos(Snake snake[], int score) {
  static Snake prev_pos;

  if (score <= 0) {
    prev_pos = snake[score];
    return prev_pos;
  }

  prev_pos = snake[score - 1];
  return prev_pos;
}

void draw_snake_body(Grid* grid, Snake snake[], int score) {
  for(int i=0; i < score; i++) {
    grid->tiles[snake[i].y][snake[i].x] = 'o'; 
  }
}

void update_grid(Grid* grid) {
  // refresh the screen
  for(int i=1; i < HEIGHT; i++) {
    for(int j=1; j < WIDTH; j++) {
      grid->tiles[i][j] = ' ';
    }
  }

  // draw fruit
  grid->tiles[2][6] = '@';
}

void check_collision(Snake snake[]) {
  if (snake[0].y > 15 || snake[0].y < 1 ||
      snake[0].x > 31 || snake[0].x < 1) {
    printf("GAME OVER\n");
    exit(0);
  }
}


int main() {
  Grid grid;    
  Snake snake[MAX_LENGTH];
     
  init_snake(snake);
  init_grid(&grid);

  system("cls");
  
  printf("    Y\n");
  printf("  .-^-.\n");
  printf(" /     \\      .- ~ ~ -.\n");
  printf("()     ()    /   _ _  `.                       \n");
  printf(" \\_   _/    /  /     \\  \\               . ~----_ \n");
  printf("   | |     /  /       \\  \\             .'  .~ ~-. `.\n");
  printf("   | |    /  /         )  )           /  /        `.`.\n");
  printf("   \\ \\_ _/  /         /   /          /  /            `'\n");
  printf("    \\_ _ _.'         /   /           (  (\n");
  printf("                    /   /             \\  \\		  \n");
  printf("                   /   /               \\  \\			\n");
  printf("                  /   /                 )  )\n");
  printf("                 (   (                 /  /\n");
  printf("                  `.  `.             .'  /\n");
  printf("                    `.   ~ - - - - ~   .'\n");
  printf("                      ~ . _ _ _ _ . ~\n");

  printf("\n");

  printf("\t\t\t");
  printf(" ___         __          ____\n");
  printf("\t\t\t");
  printf("/ __)( \\( ) /__\\  ( )/ )( ___)\n");
  printf("\t\t\t");
  printf("\\__ \\ )  ( /(__)\\  )  (  )__)\n");   
  printf("\t\t\t");
  printf("(___/(_)\\_)|__)(_)(_)\\_)(____) () () ()\n");
  
  printf("PLAY SNAKE? (y/n)\n");

  char c = getch();

  if (c == 'n') {
    exit(0);
  }

  if (c == 'y') {
    
    for (;;) {    
      move_snake(&grid, snake);
      draw_grid(&grid);    
      update_grid(&grid);
      check_collision(snake);
      system("cls");
      printf("\e[?25l"); // hide cursor
    }
  }
  
  return 0;
}
