#pragma once

#define GRID_WIDTH 42
#define GRID_HEIGHT 26
#define MAX_LENGTH 1092

#define HEAD 0

typedef struct Grid {
  char tiles[GRID_HEIGHT][GRID_WIDTH];
}Grid;

typedef struct Snake {
  int x, y;
}Snake;


typedef struct Apple {
  int x, y;
}Apple;


void create_grid(Grid* grid);
void draw_grid(Grid* grid);
void update_grid(Grid* grid);
void create_apple(Apple* apple, Grid* grid);
void draw_apple(Apple* apple, Grid* grid);
void create_snake(Snake snake[]);
void draw_snake(Snake snake[], Grid* grid);
void move_snake(Snake snake[], Apple* apple, Grid* grid);
void destroy_apple(Apple* apple);
void detect_collisions(Snake snake[], Apple* apple, Grid* grid);
