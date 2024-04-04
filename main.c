#include "maze.h"

int main() {
    int board[N][M] = {0};
    readFromFile(board, "maze.txt");
    show(board);
    solve(board);
    show(board);
    return 0;
}
