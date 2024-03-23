#ifndef RENDER_H
#define RENDER_H

#include "entity.h"

#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"

namespace SnakeRender {
  void drawWalls(int);

  void drawSnake(SnakeEntity::Snake*);

  void drawApple(SnakeEntity::Apple*);

  void drawPoint(int, int);
}
#endif