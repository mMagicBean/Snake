#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


bool is_moving_right = false;
bool is_moving_left = false;
bool is_moving_up = false;
bool is_moving_down = false;

int SCORE = 0;

enum DIR {
  UP = 17,
  DOWN = 18,
  LEFT = 20,
  RIGHT = 19,
  ESCAPE = 27
};


void create_grid(Grid* grid) {
  for (int i = 0; i <= GRID_HEIGHT - 1; i++) {
    for (int j = 0; j <= GRID_WIDTH - 1; j++) {
      // interior 
      grid->tiles[i][j] = ' ';

      //borders
      grid->tiles[i][0] = '+'; // left
      grid->tiles[0][j] = '+'; // top
      grid->tiles[i][GRID_WIDTH - 1] = '+'; // right
      grid->tiles[GRID_HEIGHT - 1][j] = '+'; // bottom
    }
  }
}

void draw_grid(Grid* grid) {
  for (int i = 0; i <= GRID_HEIGHT - 1; i++) {
    for (int j = 0; j <= GRID_WIDTH - 1; j++) {
      printf("%c", grid->tiles[i][j]);

      if (j >= GRID_WIDTH - 1) {
	printf("\n");
      }
    }
  }
}

void update_grid(Grid* grid) {
  for (int i = 1; i < GRID_HEIGHT - 1; i++) {
    for (int j = 1; j < GRID_WIDTH - 1; j++) {
      
      if (grid->tiles[i][j] == '@') {
	continue;
      }
            
      grid->tiles[i][j] = ' ';
    }
  }
}
 
void create_apple(Apple* apple, Grid* grid) {
  srand((unsigned)time(NULL));

  int lower = 4;
  
  int max_width  = GRID_WIDTH - 2;
  int max_height = GRID_HEIGHT - 2;
  
  int rand_xpos = (rand() % (max_width - lower + 1)) + lower;
  int rand_ypos = (rand() % (max_height - lower + 1)) + lower;

  if (grid->tiles[rand_ypos][rand_xpos] == 'o' || grid->tiles[rand_ypos][rand_xpos] == 'O') {
    printf("apple spawned on already occupied tile\n");
  }
  
  apple->x = rand_xpos;
  apple->y = rand_ypos;
}

void draw_apple(Apple* apple, Grid* grid) {
  grid->tiles[apple->y][apple->x] = '@';
}


void create_snake(Snake snake[]) {
  memset(snake, 0, MAX_LENGTH);

  snake[0].x = 10;
  snake[0].y = 10;
}

void draw_snake(Snake snake[], Grid* grid) {
  // snake body
  for (int i = 1; i <= SCORE; i++) {
    grid->tiles[snake[i].y][snake[i].x] = 'o';
  }

  // snake head
  grid->tiles[snake[0].y][snake[0].x] = 'O';
}

void move_snake(Snake snake[], Apple* apple, Grid* grid) {
  if (is_moving_up) {
    snake[0].y--;
  }

  if (is_moving_right) {
    snake[0].x++;
  }

  if (is_moving_left) {
    snake[0].x--;
  }

  if (is_moving_down) {
    snake[0].y++;
  }

  int prev_x = snake[0].x;
  int prev_y = snake[0].y;

  int prev_x2, prev_y2;

  for (int i = 1; i <= SCORE; i++) {
    prev_x2 = snake[i].x;
    prev_y2 = snake[i].y;

    snake[i].x = prev_x;
    snake[i].y = prev_y;

    prev_x = prev_x2;
    prev_y = prev_y2;
    
    if (snake[0].x == prev_x && snake[0].y == prev_y) {
      printf("GAME OVER\n");
      exit(0);
    }
  }
  
  char c;

  if (_kbhit()) {
    c = _getch();

    switch (c) {
    case 'w':
    case 'W':
      is_moving_up    = true;
      is_moving_down  = false;
      is_moving_right = false;
      is_moving_left  = false;
      break;

    case 's':
    case 'S':
      is_moving_down  = true;
      is_moving_up    = false;
      is_moving_right = false;
      is_moving_left  = false;
      break;

    case 'a':
    case 'A':
      is_moving_left  = true;
      is_moving_up    = false;
      is_moving_down  = false;
      is_moving_right = false;
      break;

    case 'd':
    case 'D':
      is_moving_right = true;
      is_moving_down  = false;
      is_moving_up    = false;
      is_moving_left  = false;
      break;
      
    case ESCAPE:
      exit(0);
      break;
    }
  }
}

void detect_collisions(Snake snake[], Apple* apple, Grid* grid) {
  printf("\t\tScore: %d\n", SCORE);
  
  if (snake[0].x > GRID_WIDTH - 2 || snake[0].x < 1) {
    system("cls");
    printf("GAME OVER");
    Sleep(200);
    exit(0);
  }

  if (snake[0].y > GRID_HEIGHT - 2 || snake[0].y < 1) {
    system("cls");
    printf("GAME OVER");
    Sleep(200);
    exit(0);
  }

  // snake & apple collision
  if (snake[0].x == apple->x && snake[0].y == apple->y) {
    SCORE += 1;

    // hide apple 
    apple->x = -1;
    apple->y = -1;

    create_apple(apple, grid); 
    
    printf("\n");
    printf("collision detected!");
  }
}

int main() {
  Grid grid;
  create_grid(&grid);
  
  Snake snake[MAX_LENGTH];
  create_snake(snake);
  
  Apple apple;
  create_apple(&apple, &grid);
  
  COORD coord;
  
  coord.X = 0;
  coord.Y = 0;
  
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
  printf("\n");
  printf("                               PLAY SNAKE? (y/n)\n");

  char c = _getch();

  if (c == 'n' || c == 'N') {
    exit(0);
  }

  if (c == 'y' || c == 'Y') {
    system("cls");
        
    for (;;) {
      draw_snake(snake, &grid);
      draw_grid(&grid);
      draw_apple(&apple, &grid);

      move_snake(snake, &apple, &grid);
      update_grid(&grid);
      detect_collisions(snake, &apple, &grid);

      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      Sleep(30);
    }
  }

  return 0;
}
