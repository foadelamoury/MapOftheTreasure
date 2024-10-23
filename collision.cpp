bool isCollision(int new_x, int new_y) {


    return maze[new_y][new_x] == '*';
}

void updatePlayerPosition(int prev_x, int prev_y) {
    gotoXY(prev_x, prev_y);
    cout << " ";

    gotoXY(player_x, player_y);
    cout << "P";
}