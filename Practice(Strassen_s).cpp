#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

// Function to add two matrices
Matrix matrixAdd(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

// Function to subtract two matrices
Matrix matrixSub(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }

    return result;
}

// Function to multiply two matrices using Strassen's algorithm
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();

    // Base case: If the matrix size is 1x1, perform simple multiplication
    if (n == 1) {
        Matrix C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Splitting input matrices into quarters
    int newSize = n / 2;
    Matrix A11(newSize, vector<int>(newSize));
    Matrix A12(newSize, vector<int>(newSize));
    Matrix A21(newSize, vector<int>(newSize));
    Matrix A22(newSize, vector<int>(newSize));
    Matrix B11(newSize, vector<int>(newSize));
    Matrix B12(newSize, vector<int>(newSize));
    Matrix B21(newSize, vector<int>(newSize));
    Matrix B22(newSize, vector<int>(newSize));

    // Dividing matrices A and B into quarters
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Recursively compute the seven products required in Strassen's algorithm
    Matrix P1 = strassenMultiply(A11, matrixSub(B12, B22));
    Matrix P2 = strassenMultiply(matrixAdd(A11, A12), B22);
    Matrix P3 = strassenMultiply(matrixAdd(A21, A22), B11);
    Matrix P4 = strassenMultiply(A22, matrixSub(B21, B11));
    Matrix P5 = strassenMultiply(matrixAdd(A11, A22), matrixAdd(B11, B22));
    Matrix P6 = strassenMultiply(matrixSub(A12, A22), matrixAdd(B21, B22));
    Matrix P7 = strassenMultiply(matrixSub(A11, A21), matrixAdd(B11, B12));

    // Compute the four quadrants of the result matrix
    Matrix C11 = matrixSub(matrixAdd(matrixAdd(P5, P4), P6), P2);
    Matrix C12 = matrixAdd(P1, P2);
    Matrix C21 = matrixAdd(P3, P4);
    Matrix C22 = matrixSub(matrixSub(matrixAdd(P5, P1), P3), P7);

    // Construct the result matrix by combining the four quadrants
    Matrix result(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            result[i][j] = C11[i][j];
            result[i][j + newSize] = C12[i][j];
            result[i + newSize][j] = C21[i][j];
            result[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return result;
}

// Function to print a matrix
void printMatrix(const Matrix& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to take input for a matrix
Matrix inputMatrix(int n) {
    Matrix matrix(n, vector<int>(n));
    cout << "Enter matrix elements:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

int main() {
    int n;
    cout << "Enter the size of the matrices (4 or 8): ";
    cin >> n;

    if (n != 4 && n != 8) {
        cout << "Invalid matrix size! Please enter either 4 or 8." << endl;
        return 0;
    }

    cout << "Enter the first matrix (A):" << endl;
    Matrix A = inputMatrix(n);

    cout << "Enter the second matrix (B):" << endl;
    Matrix B = inputMatrix(n);

    cout << "Matrix A:" << endl;
    printMatrix(A);

    cout << "Matrix B:" << endl;
    printMatrix(B);

    Matrix C = strassenMultiply(A, B);

    cout << "Matrix C (Result):" << endl;
    printMatrix(C);

    return 0;
}

