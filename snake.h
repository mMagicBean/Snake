#pragma once

#define WIDTH 32
#define HEIGHT 16

#define HEAD 0

typedef struct Grid {
  char tiles[HEIGHT][WIDTH];
}Grid;


typedef struct Snake {
  int x, y;
}Snake;


void init_snake(Snake snake[]);
void init_grid(Grid* grid);
void draw_grid(Grid* grid);
int move_snake(Grid* grid, Snake snake[]);
void draw_snake_body(Grid* grid, Snake snake[], int score);
void update_grid(Grid* grid);

