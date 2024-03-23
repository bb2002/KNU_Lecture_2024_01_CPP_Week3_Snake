#include "render.h"
#include "console.h"

namespace SnakeRender {
  void drawWalls(int boardSize) {
    for (int i = 0; i < boardSize; ++i) {
			for (int j = 0; j < boardSize; ++j) {
				std::string wall = " ";

				if (i == 0) {
					if (j == 0) {
						wall = WALL_LEFT_TOP_STRING;
					} else if (j == boardSize - 1) {
						wall = WALL_RIGHT_TOP_STRING;
					} else {
						wall = WALL_HORIZONTAL_STRING;
					}
				} else if (i == boardSize - 1) {
					if (j == 0) {
						wall = WALL_LEFT_BOTTOM_STRING;
					} else if (j == boardSize - 1) {
						wall = WALL_RIGHT_BOTTOM_STRING;
					} else {
						wall = WALL_HORIZONTAL_STRING;
					}
				} else {
					if (j == 0 || j == boardSize - 1) {
						wall = WALL_VERTICAL_STRING;
					}
				}

				console::draw(j, i, wall);
			}
    }
  }

	void drawSnake(SnakeEntity::Snake* head) {
		SnakeEntity::Snake* next = head;

		while (true) {
			if (next == NULL) {
				break;
			}

			console::draw(next->pos.x, next->pos.y, next->text);
			next = next->next;
		}
	}

	void drawApple(SnakeEntity::Apple* apple) {
		if (apple == NULL) {
			return;
		}

		console::draw(apple->pos.x, apple->pos.y, apple->text);
	}

	void drawPoint(int boardSize, int score) {
		std::string text = "Score: " + std::to_string(score);
		console::draw(boardSize / 2 - text.length() / 2, boardSize, text);
	}
}