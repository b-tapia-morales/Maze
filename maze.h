#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#ifndef MAZE_H
#define MAZE_H

#endif // MAZE_H

#define N 5
#define M 6
#define MOVES 4

const int xMoves[MOVES] = {+1, +0, -1, +0};
const int yMoves[MOVES] = {+0, +1, +0, -1};

void readFromFile(int [N][M], char *);

bool coordinatesAreValid(int, int);

bool spaceIsUnmarked(int [N][M], int, int);

void markSpace(int [N][M], int, int, int);

void unmarkSpace(int [N][M], int, int);

bool isFinished(int, int);

bool isUnsolvable(int, int, int);

void moveForward(int *, int *, int *, int *, int, int);

void previousSpace(int [N][M], int *, int *, int *, int *);

bool solve(int [N][M]);

void drawLine();

void show(int [N][M]);

void readFromFile(int board[N][M], char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "r");
    assert((fp != NULL) && ("Could not open file"));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            assert((fscanf(fp, "%d", &board[i][j]) == 1) && ("Error reading values from file"));
        }
    }
    fclose(fp);
}

bool coordinatesAreValid(int x, int y) {
    return (x >= 0 && x < N) && (y >= 0 && y < M);
}

bool spaceIsUnmarked(int board[N][M], int x, int y) {
    return board[x][y] == 0;
}

void markSpace(int board[N][M], int x, int y, int counter) {
    board[x][y] = counter;
}

void unmarkSpace(int board[N][M], int x, int y) {
    board[x][y] = 0;
}

bool isFinished(int x, int y) {
    return x == (N - 1) && y == (M - 1);
}

bool isUnsolvable(int x, int y, int index) {
    return x == 0 && y == 0 && index >= (MOVES - 1);
}

void moveForward(int *x, int *y, int *index, int *counter, int nextX, int nextY) {
    *x = nextX;
    *y = nextY;
    *index = 0;
    *counter += 1;
}

void previousSpace(int board[N][M], int *x, int *y, int *index, int *counter) {
    *counter -= 2;
    for (int i = 0; i < MOVES; i++) {
        int prevX = *x + xMoves[i];
        int prevY = *y + yMoves[i];
        if (board[prevX][prevY] == *counter) {
            const int n = MOVES / 2;
            *x = prevX;
            *y = prevY;
            *index = (i + n) % MOVES + 1;
            *counter += 1;
            return;
        }
    }
}

void drawLine() {
    for (int i = 0; i < M; i++) {
        printf("+----");
    }
    printf("+\n");
}

void show(int board[N][M]) {
    fflush(stdout);
    drawLine();
    for (int i = 0; i < N; i++) {
        fflush(stdout);
        for (int j = 0; j < M; j++) {
            printf("| %2d ", board[i][j]);
        }
        printf("|\n");
        drawLine();
    }
    printf("\n");
}


bool solve(int board[N][M]) {
    markSpace(board, 0, 0, 1);
    int x = 0;
    int y = 0;
    int index = 0;
    int counter = 2;
    while (true) {
        int nextX = x + xMoves[index];
        int nextY = y + yMoves[index];
        if (coordinatesAreValid(nextX, nextY) && spaceIsUnmarked(board, nextX, nextY)) {
            markSpace(board, nextX, nextY, counter);
            if (isFinished(nextX, nextY)) {
                return true;
            }
            moveForward(&x, &y, &index, &counter, nextX, nextY);
        } else {
            index += 1;
            if (isUnsolvable(x, y, index)) {
                return false;
            }
            if (index >= MOVES) {
                unmarkSpace(board, x, y);
                previousSpace(board, &x, &y, &index, &counter);
            }
        }
    }
}

#pragma clang diagnostic pop