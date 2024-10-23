#include <thread>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <random>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int player_x = 1, player_y = 1;
int treasure_x = 22, treasure_y = 7;
bool game_win = false;
vector<string> maze;

void gotoXY(int x, int y) {
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}

void clearScreen() {
    cout << "\033[2J";
}



void display() {
    clearScreen();
    for (int i = 0; i < maze.size(); i++) {
        cout << maze[i] << endl;
    }

    gotoXY(player_x, player_y);
    cout << "P";
    gotoXY(treasure_x, treasure_y);
    cout << "X";
}



int main() {
    loadMaze();
    display();

    do {
        if (_kbhit()) {
            int prev_x = player_x, prev_y = player_y;
            char key = _getch();
            int new_x = player_x, new_y = player_y;

            switch (key) {
            case 'w': new_y--; break;
            case 's': new_y++; break;
            case 'a': new_x--; break;
            case 'd': new_x++; break;
            }

            if (!isCollision(new_x, new_y)) {
                player_x = new_x;
                player_y = new_y;

                updatePlayerPosition(prev_x, prev_y);
            }
        }

        if (player_x == treasure_x && player_y == treasure_y) {
            gotoXY(0, 100);
            cout << "You found the treasure! You win!" << endl;
            game_win = true;
        }

    } while (!game_win);

    return 0;
}
