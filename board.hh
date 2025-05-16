#ifndef BOARD_HH
#define BOARD_HH

#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define to_2D(l) (l) / _width, (l) % _width
#define to_1D(h, w) ((h)*_width + (w))

class Game_2048 {
  private:
    int _height, _width;
    const int _cell_width = 7;
    long long _score = 0;
    long long *_board;
    std::string _format(long long n);
    long long *_up(bool real = true);
    long long *_down(bool real = true);
    long long *_left(bool real = true);
    long long *_right(bool real = true);

  public:
    Game_2048(int height, int width) : _height(height), _width(width) { _board = new long long[height * width]; }
    Game_2048() : Game_2048(4, 4) {}
    ~Game_2048() { delete[] _board; }
    void initiate();
    bool add_random();
    void display(std::ostream &os = std::cout);
    bool gameover();
    bool move(char dir);
    long long score() const { return _score; }
};

#endif  // BOARD_HH