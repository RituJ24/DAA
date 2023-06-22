#include <iostream>
#include <vector>

using namespace std;

// Function to check if a queen can be placed at a given position
bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    // Check if there is a queen in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check if there is a queen in the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check if there is a queen in the upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Function to solve the N-Queens problem using backtracking
bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    if (row == N) {
        // All queens have been placed successfully
        return true;
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col, N)) {
            // Place the queen at the current position
            board[row][col] = 1;

            // Recursively solve for the next row
            if (solveNQueens(board, row + 1, N)) {
                return true;
            }

            // If placing the queen at the current position does not lead to a solution,
            // backtrack and try placing it in the next column
            board[row][col] = 0;
        }
    }

    // If no queen can be placed in the current row, return false
    return false;
}

// Function to print the N-Queens solution
void printNQueens(const vector<vector<int>>& board) {
    int N = board.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Enter the value of N: ";
    cin >> N;

    // Create an N x N chessboard
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQueens(board, 0, N)) {
        cout << "N-Queens Solution:" << endl;
        printNQueens(board);
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}

