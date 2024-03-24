# Snake Game
2024년 1학기 C++ 프로그래밍 3주차 과제 SnakeGame 프로젝트 구현체 입니다.

## How to build
프로젝트를 Clone 하고 아래 명령을 따라 빌드해주세요.

```
g++ -Werror -std=c++11 -c *.cpp
g++ -o main.exe *.o
```

main.exe 파일이 생성되었는지 확인하고, 실행해주세요.
```
./main.exe
```

## How to edit 'BOARD_SIZE'
game.cpp 파일의 아래 라인을 수정해주세요.
```
7  #define BOARD_SIZE 8
```
min 4, max 20 조건을 만족해야합니다.

