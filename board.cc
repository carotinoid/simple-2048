#include "board.hh"

#include <cstring>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

std::string Game_2048::_format(long long n) {
    std::string s = std::to_string(n);
    while (s.length() <= _cell_width - 2) {
        s = " " + s + " ";
    }
    if (s.length() < _cell_width)
        s = s + " ";
    return s;
}

void Game_2048::initiate() {
    for (int i = 0; i < _height * _width; ++i) {
        _board[i] = 0;
    }
    _score = 0;
    add_random();
    add_random();
}

bool Game_2048::add_random() {
    std::vector<int> empty_cells;
    for (int i = 0; i < _height * _width; i++)
        if (_board[i] == 0)
            empty_cells.push_back(i);
    if (empty_cells.empty())
        return false;
    int select = rng() % empty_cells.size();
    bool four = (rng() % 4 == 0);
    _board[empty_cells[select]] = four ? 4 : 2;
    return true;
}

void Game_2048::display(std::ostream &os) {
    std::string hr;
    std::string empty;
    for (int j = 0; j < _cell_width; j++) {
        hr += "─";
        empty += " ";
    }
    os << "┌";
    for (int i = 0; i < _width - 1; i++) {
        os << hr;
        os << "┬";
    }
    os << hr;
    os << "┐\n";
    for (int i = 0; i < _height; i++) {
        os << "│";
        for (int j = 0; j < _width; j++) {
            os << (_board[to_1D(i, j)] == 0 ? empty : _format(_board[to_1D(i, j)]));
            os << "│";
        }
        os << "\n";
        if (i == _height - 1)
            break;
        os << "├";
        for (int j = 0; j < _width - 1; j++) {
            os << hr;
            os << "┼";
        }
        os << hr;
        os << "┤\n";
    }
    os << "└";
    for (int i = 0; i < _width - 1; i++) {
        os << hr;
        os << "┴";
    }
    os << hr;
    os << "┘\n";
}

long long *Game_2048::_up(bool real) {
    long long *new_board = new long long[_height * _width];
    memset(new_board, 0, sizeof(long long) * _height * _width);
    for (int i = 0; i < _width; i++) {
        int value = 0, index = 0;
        for (int j = 0; j < _height; j++) {
            if (_board[to_1D(j, i)] == 0)
                continue;
            if (value == 0) {
                value = _board[to_1D(j, i)];
            } else if (value == _board[to_1D(j, i)]) {
                new_board[to_1D(index++, i)] = value * 2;
                if (real)
                    _score += value * 2;
                value = 0;
            } else {
                new_board[to_1D(index++, i)] = value;
                value = _board[to_1D(j, i)];
            }
        }
        if (value != 0) {
            new_board[to_1D(index, i)] = value;
            value = 0;
        }
    }
    return new_board;
}

long long *Game_2048::_down(bool real) {
    long long *new_board = new long long[_height * _width];
    memset(new_board, 0, sizeof(long long) * _height * _width);
    for (int i = 0; i < _width; i++) {
        int value = 0, index = _height - 1;
        for (int j = _height - 1; j >= 0; j--) {
            if (_board[to_1D(j, i)] == 0)
                continue;
            if (value == 0) {
                value = _board[to_1D(j, i)];
            } else if (value == _board[to_1D(j, i)]) {
                new_board[to_1D(index--, i)] = value * 2;
                if (real)
                    _score += value * 2;
                value = 0;
            } else {
                new_board[to_1D(index--, i)] = value;
                value = _board[to_1D(j, i)];
            }
        }
        if (value != 0) {
            new_board[to_1D(index--, i)] = value;
            value = 0;
        }
    }
    return new_board;
}
long long *Game_2048::_left(bool real) {
    long long *new_board = new long long[_height * _width];
    memset(new_board, 0, sizeof(long long) * _height * _width);
    for (int i = 0; i < _height; i++) {
        int value = 0, index = 0;
        for (int j = 0; j < _width; j++) {
            if (_board[to_1D(i, j)] == 0)
                continue;
            if (value == 0) {
                value = _board[to_1D(i, j)];
            } else if (value == _board[to_1D(i, j)]) {
                new_board[to_1D(i, index++)] = value * 2;
                if (real)
                    _score += value * 2;
                value = 0;
            } else {
                new_board[to_1D(i, index++)] = value;
                value = _board[to_1D(i, j)];
            }
        }
        if (value != 0) {
            new_board[to_1D(i, index)] = value;
            value = 0;
        }
    }
    return new_board;
}
long long *Game_2048::_right(bool real) {
    long long *new_board = new long long[_height * _width];
    memset(new_board, 0, sizeof(long long) * _height * _width);
    for (int i = 0; i < _height; i++) {
        int value = 0, index = _width - 1;
        for (int j = _width - 1; j >= 0; j--) {
            if (_board[to_1D(i, j)] == 0)
                continue;
            if (value == 0) {
                value = _board[to_1D(i, j)];
            } else if (value == _board[to_1D(i, j)]) {
                new_board[to_1D(i, index--)] = value * 2;
                if (real)
                    _score += value * 2;
                value = 0;
            } else {
                new_board[to_1D(i, index--)] = value;
                value = _board[to_1D(i, j)];
            }
        }
        if (value != 0) {
            new_board[to_1D(i, index--)] = value;
            value = 0;
        }
    }
    return new_board;
}

bool Game_2048::move(char dir) {
    long long *new_board = nullptr;
    if (dir == 'W' or dir == 'w') {
        new_board = _up();
    } else if (dir == 'S' or dir == 's') {
        new_board = _down();
    } else if (dir == 'A' or dir == 'a') {
        new_board = _left();
    } else if (dir == 'D' or dir == 'd') {
        new_board = _right();
    }
    bool changed = false;
    for (int i = 0; i < _height * _width; i++) {
        if (_board[i] != new_board[i]) {
            changed = true;
            break;
        }
    }
    if (changed) {
        delete[] _board;
        _board = new_board;
        add_random();
        return true;
    } else {
        delete[] new_board;
        return false;
    }
}

bool Game_2048::gameover() {
    bool dead = true;
    long long *up = _up(false);
    long long *down = _down(false);
    long long *left = _left(false);
    long long *right = _right(false);
    for (int i = 0; i < _height * _width; i++) {
        if (up[i] != _board[i] || down[i] != _board[i] || left[i] != _board[i] || right[i] != _board[i]) {
            dead = false;
            break;
        }
    }
    delete[] up;
    delete[] down;
    delete[] left;
    delete[] right;
    return dead;
}