#include <thread>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <random>
#include <iostream>
#include <string>
#include <vector>

//#include "collision.h"
//#include "readtxt.h"


using namespace std;


int player_x = 1, player_y = 1;
int treasure_x = 22, treasure_y = 7;
bool game_win = false;
vector<string> maze;
int maze_height, maze_width;

void gotoXY(int x, int y) {
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}

void clearScreen() {
    cout << "\033[2J";
}

void loadMaze() {
    std::ifstream mazeFile("maze.txt");
    if (!mazeFile) {
        std::cerr << "Error: Could not open maze file!" << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(mazeFile, line)) {
        maze.push_back(line);
    }
    mazeFile.close();
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

bool isCollision(int new_x, int new_y) {
    return maze[new_y][new_x] == '*';
}

void updatePlayerPosition(int prev_x, int prev_y) {
    gotoXY(prev_x, prev_y);
    cout << " ";
    gotoXY(player_x, player_y);
    cout << "P";
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