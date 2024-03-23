#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <cstdlib>

namespace SnakeUtil {
    template<typename T>
    class StaticArray {
    private:
      T *arr;
      int _size = 0;
      const int CAPACITY = 8192;

    public:
      StaticArray() {
        this->arr = new T[CAPACITY];
      }

      ~StaticArray() {
          delete[] arr;
      }

      void push(T data) {
        if (_size >= this->CAPACITY) {
          return;
        }

        arr[_size++] = data;
      }

      T get(int index) {
        return arr[index];
      }

      int size() {
        return this->_size;
      }
    };

    int random(int min, int max) {
        return (rand() % (max - min + 1)) + min;
    }

    int center(int size) {
        return std::abs(size / 2);
    }
}

#endif /* UTILS_H */
