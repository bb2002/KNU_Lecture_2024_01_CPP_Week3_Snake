#include "render.h"
#include "entity.h"
#include "utils.h"
#include "game.h"
#include "console.h"

#define BOARD_SIZE 5

using namespace SnakeEntity;
using namespace SnakeUtil;

namespace SnakeGame {
  void GameInstance::init() {
      this->inputDirection = new Direction2D();
      this->snakeHead = new Snake();
      this->currentApple = new Apple();

      // 입력 처리기 초기화
      this->inputDirection->x = -1;
      this->inputDirection->y = 0;

      // 뱀 초기화
      const int CENTER = center(BOARD_SIZE - 1);
      this->snakeHead->next = NULL;
      this->snakeHead->pos = { CENTER, CENTER };
      this->snakeHead->text = SNAKE_BODY_STRING;

      // 사과 초기화
      while(true) {
        const int x = random(1, BOARD_SIZE - 2);
        const int y = random(1, BOARD_SIZE - 2);

        if (x == CENTER && y == CENTER) {
          continue;
        }

        this->currentApple->pos = { x, y };
        this->currentApple->text = APPLE_STRING;
        break;
      }

      // 플레이 시작
      this->status = GameStatus::PLAYING;
    }

    void GameInstance::loop60FPS(int tick) {
      SnakeRender::drawWalls(BOARD_SIZE);
      SnakeRender::drawSnake(this->snakeHead);
      SnakeRender::drawApple(this->currentApple);
      SnakeRender::drawPoint(BOARD_SIZE, this->point);
    }

    void GameInstance::loop15FPS(int tick) {
      Transform2D lastSnakeTransform = this->handleSnakeMove();

      if (this->collisionSnake()) {
        this->status = LOSE;
      }

      if (this->collisionWalls()) {
        this->status = LOSE;
      }

      if (this->collisionApple()) {
        this->point += 10;
        this->addSnake(lastSnakeTransform);

        if(this->winOrRelocateApple()) {
          this->status = WIN;
        }
      }
    }

    void GameInstance::loopUI(int tick) {
      std::string line = "";
      if (this->status == GameStatus::LOSE) {
        line = "YOU LOSE!";
      }

      if (this->status == GameStatus::WIN) {
        line = "YOU WIN!";
      }

      console::draw(BOARD_SIZE / 2 - line.length() / 2, BOARD_SIZE / 2, line);
      console::draw(BOARD_SIZE / 2 - 9, BOARD_SIZE / 2 + 1, "Try again? (Enter)");
    }

    void GameInstance::handleInput(console::Key key) {
      switch (key) {
        case console::K_LEFT:
          this->inputDirection->x = -1;
          this->inputDirection->y = 0;
          break;
        case console::K_RIGHT:
          this->inputDirection->x = 1;
          this->inputDirection->y = 0;
          break;
        case console::K_UP:
          this->inputDirection->x = 0;
          this->inputDirection->y = -1;
          break;
        case console::K_DOWN:
          this->inputDirection->x = 0;
          this->inputDirection->y = 1;
          break;
        case console::K_ESC:
          this->status = GameStatus::STOPPED;
          break;
      }
    }

    Transform2D GameInstance::handleSnakeMove() {
      int prevX = this->snakeHead->pos.x;
      int prevY = this->snakeHead->pos.y;
      this->snakeHead->pos.x += this->inputDirection->x;
      this->snakeHead->pos.y += this->inputDirection->y;

      Snake* next = this->snakeHead->next;
      while(true) {
        if (next == NULL) {
          break;
        }

        int tmpX = next->pos.x, tmpY = next->pos.y;
			  next->pos.x = prevX;
        next->pos.y = prevY;
        prevX = tmpX;
        prevY = tmpY;

        next = next->next;
      }

      return { prevX, prevY };
    }

    bool GameInstance::collisionApple() {
      return this->currentApple->pos.x == this->snakeHead->pos.x &&
        this->currentApple->pos.y == this->snakeHead->pos.y;
    }

    bool GameInstance::collisionSnake() {
      Snake* head = this->snakeHead;
      Snake* next = head->next;

      while(true) {
        if (next == NULL) {
          return false;
        }

        if (next->pos.x == head->pos.x && next->pos.y == head->pos.y) {
          return true;
        }

        next = next->next;
      }
    }

    bool GameInstance::collisionWalls() {
      Transform2D transform = this->snakeHead->pos;
      if (transform.x < 1 || transform.x >= BOARD_SIZE - 1) {
        return true;
      }

      if (transform.y < 1 || transform.y >= BOARD_SIZE - 1) {
        return true;
      }

      return false;
    }

    bool GameInstance::winOrRelocateApple() {
      StaticArray<Transform2D>* gameArea = new StaticArray<Transform2D>();
      for (int x = 1; x < BOARD_SIZE - 1; ++x) {
        for (int y = 1; y < BOARD_SIZE - 1; ++y) {
          gameArea->push({ x, y });
        }
      }

      StaticArray<Transform2D>* snakeArea = new StaticArray<Transform2D>();
      Snake* last = this->snakeHead;
      while(true) {
        if (last == NULL) {
          break;
        }
        snakeArea->push(last->pos);
        last = last->next;
      }

      if (snakeArea->size() == gameArea->size()) {
        // 뱀이 게임 화면을 모두 채운 경우
        return true;
      }

      StaticArray<Transform2D>* appleAvailableArea = new StaticArray<Transform2D>();
      for (int i = 0; i < gameArea->size(); ++i) {
        bool isAvailable = true;
        auto game = gameArea->get(i);

        for (int j = 0; j < snakeArea->size(); ++j) {
          auto snake = snakeArea->get(j);
          if (game.x == snake.x && game.y == snake.y) {
            isAvailable = false;
            break;
          }
        }

        if (isAvailable) {
          // 뱀이 위치하지 않은 곳만 사과 배치 가능 영역으로 둔다.
          appleAvailableArea->push(game);
        }
      }
      
      auto newTransform = appleAvailableArea->get(random(0, appleAvailableArea->size() - 1));
      this->currentApple->pos = newTransform;
      return false;
    }

    void GameInstance::addSnake(Transform2D transform) {
      Snake* last = this->snakeHead;
      while(true) {
        if (last->next == NULL) {
          break;
        }

        last = last->next;
      }

      Snake* newBody = new Snake();
      newBody->pos = transform;
      newBody->text = SNAKE_BODY_STRING;
      last->next = newBody;
    }
}