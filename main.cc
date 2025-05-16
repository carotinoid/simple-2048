#include "board.hh"

#include <iostream>
#include <set>

using namespace std;

int main() {
    Game_2048 game(2, 3);
    game.initiate();
    while (true) {
        game.display();
        cout << "Score: " << game.score() << endl;
        if (game.gameover()) {
            cout << "Game Over!" << endl;
            break;
        }
        char in;
        cout << "Enter move WASD or Q to quit or R to restart: ";
        cin >> in;
        if (in == 'R' or in == 'r') {
            game.initiate();
            continue;
        }
        if (in == 'Q' or in == 'q') {
            cout << "Bye" << endl;
            break;
        }
        if (in == 'W' or in == 'w' or in == 'A' or in == 'a' or in == 'S' or in == 's' or in == 'D' or in == 'd') {
            if (!game.move(in)) {
                cout << "Invalid move!" << endl;
            }
        } else {
            cout << "Invalid input!" << endl;
        }
    }
    return 0;
}