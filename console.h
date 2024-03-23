#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

namespace console {
const int SCREEN_WIDTH = 25;
const int SCREEN_HEIGHT = 25;
void init();
void wait();
void draw(int x, int y, const char *s);
void draw(int x, int y, std::string s);
void clear();
enum Key { K_NONE = 0, K_OTHER, K_LEFT, K_RIGHT, K_UP, K_DOWN, K_ESC, K_ENTER };
bool key(Key k);
}
#endif