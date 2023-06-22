#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Size of the puzzle board
const int BOARD_SIZE = 4;

// Structure to represent a state of the puzzle
struct PuzzleState {
    int board[BOARD_SIZE][BOARD_SIZE];
    int cost;
    int depth;
    int blankRow;
    int blankCol;
    string path;
    string prevMove;

    // calculate distance
    int calCost() {
        int sum = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                int value = board[i][j];
                if (value != 0) {
                    int targetRow = (value - 1) / BOARD_SIZE;
                    int targetCol = (value - 1) % BOARD_SIZE;
                    sum += abs(i - targetRow) + abs(j - targetCol);
                }
            }
        }
        return sum;
    }
};

// Custom comparison function for priority queue
struct ComparePuzzleState {
    bool operator()(const PuzzleState& a, const PuzzleState& b) {
        return (a.cost + a.depth) > (b.cost + b.depth);
    }
};

// check if a given state is the goal state
bool isGoalState(const PuzzleState& state) {
    int value = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (state.board[i][j] != value && value != BOARD_SIZE * BOARD_SIZE) {
                return false;
            }
            value++;
        }
    }
    return true;
}

// check if a move is valid
bool isValidMove(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

// perform a move in the puzzle board
void makeMove(PuzzleState& state, int newRow, int newCol) {
    swap(state.board[state.blankRow][state.blankCol], state.board[newRow][newCol]);
    state.blankRow = newRow;
    state.blankCol = newCol;
}

// print the puzzle board
void printBoard(const PuzzleState& state) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << state.board[i][j] << "\t";
            
        }
        cout << endl;
       
    }
    cout << endl;
     cout<< "Cost of the Board: "<< state.cost<<endl;
     cout<<endl;
}

// solve the puzzle using Branch and Bound technique
void solvePuzzle(const PuzzleState& initialState) {
    priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> pq;
    pq.push(initialState);

    int iteration = 0;
    while (!pq.empty() && iteration < 4) {
        PuzzleState currentState = pq.top();
        pq.pop();

        cout << "Iteration " << iteration << ":\n";
        cout << "Current Cost: " << currentState.cost << endl;
        cout << "Current Path: " << currentState.path << endl;
        printBoard(currentState);

        if (isGoalState(currentState)) {
            cout << "Puzzle solved!\n";
            cout << "Minimum Cost: " << currentState.cost << endl;
            cout << "Minimum Path: " << currentState.path << endl;
            return;
        }

        int row = currentState.blankRow;
        int col = currentState.blankCol;

        // Move Up
        if (isValidMove(row - 1, col) && currentState.prevMove!="D") {
            PuzzleState newState = currentState;
            makeMove(newState, row - 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "U";
            newState.prevMove = "U";
            
            pq.push(newState);
            cout<<"Possible Move (Up): "<<endl;
            printBoard(newState);
        }

        // Move Down
        if (isValidMove(row + 1, col) && currentState.prevMove!="U") {
            PuzzleState newState = currentState;
            makeMove(newState, row + 1, col);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "D";
            newState.prevMove="D";
            pq.push(newState);
            cout<<"Possible Move (Down): "<<endl;
            printBoard(newState);
        }

        // Move Left
        if (isValidMove(row, col - 1) && currentState.prevMove!="R") {
            PuzzleState newState = currentState;
            makeMove(newState, row, col - 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "L";
            newState.prevMove ="L";
            pq.push(newState);
            cout<<"Possible Move (Left): "<<endl;
            printBoard(newState);
        }

        // Move Right
        if (isValidMove(row, col + 1) && currentState.prevMove!="L") {
            PuzzleState newState = currentState;
            makeMove(newState, row, col + 1);
            newState.depth = currentState.depth + 1;
            newState.cost = newState.calCost();
            newState.path += "R";
            newState.prevMove="R";
            pq.push(newState);
            cout<<"Possible Move (Right): "<<endl;
            printBoard(newState);
        }
		cout<<endl<<"----------------------------------------------------------------------"<<endl;
        iteration++;
    }

    cout << "Solution not found within the specified iterations.\n";
}

int main() {
    PuzzleState initialState;
    cout << "Enter the initial state of the puzzle (space-separated numbers, 0 represents the blank tile):\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cin >> initialState.board[i][j];
            if (initialState.board[i][j] == 0) {
                initialState.blankRow = i;
                initialState.blankCol = j;
            }
        }
    }

    initialState.cost = initialState.calCost();
    initialState.depth = 0;
    initialState.path = "";

    solvePuzzle(initialState);

    return 0;
}

