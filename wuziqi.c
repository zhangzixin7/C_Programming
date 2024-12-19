#include <stdio.h>

#define SIZE 15  // 棋盘大小 15x15
#define EMPTY ' ' // 空白位置
#define PLAYER_X 'X' // 玩家 X
#define PLAYER_O 'O' // 玩家 O

// 函数声明
void printBoard(char board[SIZE][SIZE]);
int isBoardFull(char board[SIZE][SIZE]);
int checkWinner(char board[SIZE][SIZE], int row, int col, char player);
int validMove(char board[SIZE][SIZE], int row, int col);

int main() {
    char board[SIZE][SIZE];
    int row, col, move, winner = 0;
    char player = PLAYER_X;

    // 初始化棋盘
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }

    // 游戏循环
    while (!winner && !isBoardFull(board)) {
        printBoard(board);
        printf("Player %c's turn\n", player);
        printf("Enter row and column (1-15): ");
        scanf("%d %d", &row, &col);
        
        // 检查输入是否合法
        if (validMove(board, row - 1, col - 1)) {
            board[row - 1][col - 1] = player;  // 放置棋子
            winner = checkWinner(board, row - 1, col - 1, player);  // 检查是否获胜
            if (winner) {
                printBoard(board);
                printf("Player %c wins!\n", player);
                break;
            }
            // 切换玩家
            player = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
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
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) {
            for (int j = 0; j < SIZE * 3 - 1; j++) {
                printf("-");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// 检查棋盘是否已满
int isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY)  // 只要有空位
                return 0;
        }
    }
    return 1;  // 棋盘已满
}

// 检查玩家是否获胜
int checkWinner(char board[SIZE][SIZE], int row, int col, char player) {
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};  // 四个方向：水平、垂直、斜向左下、斜向右上
    int count;

    // 对每一个方向进行检查
    for (int i = 0; i < 4; i++) {
        count = 1;  // 当前棋子已经算一个
        int dx = directions[i][0], dy = directions[i][1];

        // 检查一个方向
        for (int step = 1; step < 5; step++) {
            int newRow = row + dx * step;
            int newCol = col + dy * step;
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
                count++;
            } else {
                break;
            }
        }

        // 检查反方向
        for (int step = 1; step < 5; step++) {
            int newRow = row - dx * step;
            int newCol = col - dy * step;
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
                count++;
            } else {
                break;
            }
        }

        // 如果一方向上连续5个棋子，则获胜
        if (count >= 5) {
            return 1;
        }
    }

    return 0;  // 未获胜
}

// 检查玩家输入的坐标是否合法
int validMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)  // 超出棋盘边界
        return 0;
    if (board[row][col] != EMPTY)  // 该位置已有棋子
        return 0;
    return 1;  // 合法
}
