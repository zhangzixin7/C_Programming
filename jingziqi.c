#include <stdio.h>

#define SIZE 3  // 棋盘大小 3x3

// 函数声明
void printBoard(char board[SIZE][SIZE]);
int checkWinner(char board[SIZE][SIZE]);
int isBoardFull(char board[SIZE][SIZE]);
int validMove(char board[SIZE][SIZE], int row, int col);

int main() {
    char board[SIZE][SIZE] = {{'1', '2', '3'},
                               {'4', '5', '6'},
                               {'7', '8', '9'}};  // 初始化棋盘
    int row, col, move, winner = 0;
    char player = 'X';  // 玩家 X 从先开始

    while (!winner && !isBoardFull(board)) {
        printBoard(board);
        printf("Player %c's turn\n", player);
        printf("Enter the row and column (1-3) to place your mark: ");
        scanf("%d %d", &row, &col);
        
        // 检查输入是否有效
        if (validMove(board, row - 1, col - 1)) {
            board[row - 1][col - 1] = player;  // 放置玩家的棋子
            winner = checkWinner(board);  // 检查是否有玩家获胜
            if (winner) {
                printBoard(board);
                printf("Player %c wins!\n", player);
                break;
            }
            player = (player == 'X') ? 'O' : 'X';  // 切换玩家
        } else {
            printf("Invalid move, try again!\n");
        }
    }

    if (!winner) {
        printBoard(board);
        printf("It's a draw!\n");
    }

    return 0;
}

// 打印棋盘
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

// 检查是否有玩家获胜
int checkWinner(char board[SIZE][SIZE]) {
    // 检查行
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }

    // 检查列
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    // 检查对角线
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;  // 没有获胜者
}

// 检查棋盘是否已满
int isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')  // 如果有未占用的位置
                return 0;
        }
    }
    return 1;  // 棋盘已满
}

// 检查玩家输入的坐标是否合法
int validMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)  // 超出边界
        return 0;
    if (board[row][col] == 'X' || board[row][col] == 'O')  // 已有棋子
        return 0;
    return 1;  // 合法
}
