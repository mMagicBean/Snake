#pragma once

#define WIDTH 32
#define HEIGHT 16


typedef struct Grid {
  char tiles[HEIGHT][WIDTH];
}Grid;


typedef struct Snake {
  int xpos;
  int ypos;

}Snake;


void init_snake(Snake* snake);
void init_grid(Grid* grid);
void draw_grid(Grid* grid);
void move_snake(Snake* snake);
void handle_collision(Grid* grid, Snake* snake);
void update_grid(Grid* grid, Snake* snake);
