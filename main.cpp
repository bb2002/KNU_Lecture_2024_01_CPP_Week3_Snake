#include <ctime>
#include "console.h"
#include "game.h"

#define MOVE_DELAY 15

using namespace SnakeGame;

int x = 0;
int y = 0;
int globalTick = 0;

void handleInput(GameInstance* instance) {
  if (console::key(console::K_LEFT)) {
    x--;
    instance->handleInput(console::K_LEFT);
  }
  if (console::key(console::K_RIGHT)) {
    x++;
    instance->handleInput(console::K_RIGHT);
  }
  if (console::key(console::K_UP)) {
    y--;
    instance->handleInput(console::K_UP);
  }
  if (console::key(console::K_DOWN)) {
    y++;
    instance->handleInput(console::K_DOWN);
  }
  if (console::key(console::K_ESC)) {
    instance->handleInput(console::K_ESC);
  }
}

void restrictInScreen() {
  // x, y 위치를 화면의 최대 크기에서 벗어나지 않게 한다.
  if (x < 0)
    x = 0;
  if (x >= console::SCREEN_WIDTH)
    x = console::SCREEN_WIDTH - 1;
  if (y < 0)
    y = 0;
  if (y >= console::SCREEN_HEIGHT)
    y = console::SCREEN_HEIGHT - 1;
}

int main() {
  console::init();
  srand(time(NULL));

  GameInstance* gameInstance = new GameInstance();
  gameInstance->init();

  while (true) {
    console::clear();

    handleInput(gameInstance);
    restrictInScreen();

    gameInstance->loop60FPS(globalTick);
    GameStatus status = gameInstance->getGameStatus();

    switch (status) {
      case GameStatus::PLAYING:
        if (globalTick % MOVE_DELAY == 0) {
          gameInstance->loop15FPS(globalTick);
        }
        break;
      case GameStatus::LOSE:
      case GameStatus::WIN:
        gameInstance->loopUI(globalTick);
        if (console::key(console::K_ENTER)) {
          gameInstance = new GameInstance();
          gameInstance->init();
        }
        break;
      case GameStatus::STOPPED:
        return 1;
    }

    ++globalTick;
    console::wait();
  }
}