#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void PrintParenthesis(int i, int j, int n, const vector<vector<int>>& bracket, char& name) {
    if (i == j) {
        cout << name++;
        return;
    }

    cout << "(";

    PrintParenthesis(i, bracket[i][j], n, bracket, name);
    PrintParenthesis(bracket[i][j] + 1, j, n, bracket, name);

    cout << ")";
}

void PrintMultiplicationOrder(const vector<vector<int>>& bracket, int i, int j, char& name) {
    if (i == j) {
        cout << name++;
        return;
    }

    cout << "(";

    PrintMultiplicationOrder(bracket, i, bracket[i][j], name);
    PrintMultiplicationOrder(bracket, bracket[i][j] + 1, j, name);

    cout << ")";
}

void ChainMatrixMultiplication(const vector<int>& dimensions) {
    int n = dimensions.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    vector<vector<int>> bracket(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    cout << "Minimum cost of matrix chain multiplication: " << dp[0][n - 1] << endl;

    char matrixName = 'A';
    cout << "Optimal multiplication order: ";
    PrintMultiplicationOrder(bracket, 0, n - 1, matrixName);
    cout << endl;

    cout << "Multiplication matrix: " << endl;
    matrixName = 'A';
    PrintParenthesis(0, n - 1, n, bracket, matrixName);
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;

    vector<int> dimensions(n + 1);
    cout << "Enter the dimensions of matrices:" << endl;
    for (int i = 0; i < n + 1; ++i) {
        cin >> dimensions[i];
    }

    ChainMatrixMultiplication(dimensions);

    return 0;
}

