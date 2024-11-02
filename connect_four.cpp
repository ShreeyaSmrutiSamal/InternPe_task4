#include <iostream>
#include <vector>

const int ROWS = 6;
const int COLS = 7;
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

void displayBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "\n  ";
    for (int c = 0; c < COLS; ++c) {
        std::cout << c + 1 << " ";
    }
    std::cout << "\n";

    for (int r = 0; r < ROWS; ++r) {
        std::cout << "| ";
        for (int c = 0; c < COLS; ++c) {
            std::cout << board[r][c] << " ";
        }
        std::cout << "|\n";
    }

    std::cout << "  ";
    for (int c = 0; c < COLS; ++c) {
        std::cout << "--";
    }
    std::cout << "\n";
}

bool isColumnFull(const std::vector<std::vector<char>>& board, int col) {
    return board[0][col] != ' ';
}

bool makeMove(std::vector<std::vector<char>>& board, int col, char player) {
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == ' ') {
            board[r][col] = player;
            return true;
        }
    }
    return false;
}

bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Check horizontal
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            if (board[r][c] == player && board[r][c + 1] == player &&
                board[r][c + 2] == player && board[r][c + 3] == player) {
                return true;
            }
        }
    }

    // Check vertical
    for (int c = 0; c < COLS; ++c) {
        for (int r = 0; r <= ROWS - 4; ++r) {
            if (board[r][c] == player && board[r + 1][c] == player &&
                board[r + 2][c] == player && board[r + 3][c] == player) {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int r = 3; r < ROWS; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            if (board[r][c] == player && board[r - 1][c + 1] == player &&
                board[r - 2][c + 2] == player && board[r - 3][c + 3] == player) {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int r = 0; r <= ROWS - 4; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            if (board[r][c] == player && board[r + 1][c + 1] == player &&
                board[r + 2][c + 2] == player && board[r + 3][c + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

bool isBoardFull(const std::vector<std::vector<char>>& board) {
    for (int c = 0; c < COLS; ++c) {
        if (board[0][c] == ' ') {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<std::vector<char>> board(ROWS, std::vector<char>(COLS, ' '));
    char currentPlayer = PLAYER1;
    int column;

    while (true) {
        displayBoard(board);
        std::cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") << ", choose a column (1-" << COLS << "): ";
        std::cin >> column;

        if (std::cin.fail() || column < 1 || column > COLS) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(1000, '\n');  // Ignore incorrect input
            std::cout << "Invalid input. Please enter a column number between 1 and " << COLS << ".\n";
            continue;
        }

        column--; // Adjust for 0-indexed array

        if (isColumnFull(board, column)) {
            std::cout << "Column is full. Choose a different column.\n";
            continue;
        }

        makeMove(board, column, currentPlayer);

        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            std::cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") << " wins!\n";
            break;
        }

        if (isBoardFull(board)) {
            displayBoard(board);
            std::cout << "It's a draw!\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }

    return 0;
}
