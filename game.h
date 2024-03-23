#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "console.h"

using namespace SnakeEntity;

namespace SnakeGame {
  class GameInstance {
  private:
    Direction2D* inputDirection;
    Snake* snakeHead;
    Apple* currentApple;
    int point = 0;
    GameStatus status;

  public:
    void init();
    void loop60FPS(int tick);
    void loop15FPS(int tick);
    void loopUI(int tick);

    void handleInput(console::Key);

    GameStatus getGameStatus() { return this->status; };

  protected:
    Transform2D handleSnakeMove();
    bool winOrRelocateApple();
    bool collisionApple();
    bool collisionSnake();
    bool collisionWalls();
    void addSnake(Transform2D);
  };
}
#endif