#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;

namespace SnakeEntity {
  typedef struct Transform2D {
    int x;
    int y;
  } Transform2D;

  typedef struct Direction2D {
    int x;
    int y;
  } Direction2D;

  typedef struct Snake {
    string text;
    Transform2D pos;
    Snake* next;
  } Snake;

  typedef struct Apple {
    string text;
    Transform2D pos;
  } Apple;

  enum GameStatus { PLAYING = 0, WIN = 1, LOSE = 2, STOPPED = 3 };
}
#endif