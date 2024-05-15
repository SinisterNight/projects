#include <iostream>
#include <vector>

using namespace std;
//Dewey Holland

//desc the program has a few functions that delegate a few different tasks, ADDmatrix adds matrix, subtract matrix subtacts, strassenmatrixmultiply is the strassen algorithm base case of 0 just multiply and returns. The matrix is created using vectors Divide is set to n/2 and is used to break the matrix up for loops are used to iterate through the matrix to create sub matrixes conqN (1-7), that is that then placed into 4 smaller submatix dividedC(N) the child matrix is formed using arrays and assigns in the values of c respectively in the main function the program calls strassens so it can perform the matrix multiplication. A print matrix function was also created the values of matrix a b and c are shown

// matrix addition is needed in order for us to calculate the result of conquredN Matrix
vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, int n) {//a and b must be contstant so that values can get passed through
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int conquerI = 0; conquerI < n; ++conquerI) { // outmost loop for rows innermost for columns
        for (int conquerJ = 0; conquerJ < n; ++conquerJ) { // iterate through the matrix and compute the result
            result[conquerI][conquerJ] = A[conquerI][conquerJ] + B[conquerI][conquerJ]; // A = [I] [J] + B[i][j] 
        }
    }
    return result; // return result
}

// matrix subtraction subtraction is needed in order for us to calculate the result of conquredN matrix,
vector<vector<int>> subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, int n) {//a and b must be const so values can get passed through
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int conquerI = 0; conquerI < n; ++conquerI) { // outmost loop for rows innermost for columns
        for (int conquerJ = 0; conquerJ < n; ++conquerJ) { // iterate through the matrix and compute the result
            result[conquerI][conquerJ] = A[conquerI][conquerJ] - B[conquerI][conquerJ]; // A =[i][j] - B[i][j]
        }
    }
    return result; // return result
}


// Strassens matrix multiplication
vector<vector<int>> strassenMatrixMultiply(const vector<vector<int>>& A,const vector<vector<int>>& B, int n) {// a and b must be const so values can get passed through
    // If the matrices are 1x1, just multiply and return
    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];//set value of c
        return C;//return c
    }

    // Create submatrices for A and B
    int Divide = n / 2;
    vector<vector<int>> A11(Divide, vector<int>(Divide));//create submatrix a11
    vector<vector<int>> A12(Divide, vector<int>(Divide));//create submatrix a12
    vector<vector<int>> A21(Divide, vector<int>(Divide));//create submatrix a21
    vector<vector<int>> A22(Divide, vector<int>(Divide));//create submatrix a22
    vector<vector<int>> B11(Divide, vector<int>(Divide));//create submatrix b11 
    vector<vector<int>> B12(Divide, vector<int>(Divide));//create submatrix b12
    vector<vector<int>> B21(Divide, vector<int>(Divide));//create submatrix b21
    vector<vector<int>> B22(Divide, vector<int>(Divide));//create submatrix b22

    // Populate submatrices by dividing A and B
    for (int conquerI = 0; conquerI < Divide; ++conquerI) {
        for (int conquerJ = 0; conquerJ < Divide; ++conquerJ) {
            A11[conquerI][conquerJ] = A[conquerI][conquerJ];//a11
            A12[conquerI][conquerJ] = A[conquerI][conquerJ + Divide];//a12
            A21[conquerI][conquerJ] = A[conquerI + Divide][conquerJ];//a21
            A22[conquerI][conquerJ] = A[conquerI + Divide][conquerJ + Divide];//a22
            B11[conquerI][conquerJ] = B[conquerI][conquerJ];//b11
            B12[conquerI][conquerJ] = B[conquerI][conquerJ + Divide];//b12
            B21[conquerI][conquerJ] = B[conquerI + Divide][conquerJ];//b21
            B22[conquerI][conquerJ] = B[conquerI + Divide][conquerJ + Divide];//b22
        }
    }

       // Calculate conqured1 to conqured7 using Strassen's algorithm (recursively)
	vector<vector<int>> conqured1 = strassenMatrixMultiply(A11, subtractMatrix(B12, B22, Divide), Divide); // a11 b12-b22
	vector<vector<int>> conqured2 = strassenMatrixMultiply(addMatrix(A11, A12, Divide), B22, Divide); // a11 + a12 * b22
	vector<vector<int>> conqured3 = strassenMatrixMultiply(addMatrix(A21, A22, Divide), B11, Divide); // a21 + a22 * b11
	vector<vector<int>> conqured4 = strassenMatrixMultiply(A22, subtractMatrix(B21, B11, Divide), Divide); // a22 * b21 - b11
	vector<vector<int>> conqured5 = strassenMatrixMultiply(addMatrix(A11, A22, Divide), addMatrix(B11, B22, Divide), Divide); // a11 + a22 * b11 + b22
	vector<vector<int>> conqured6 = strassenMatrixMultiply(subtractMatrix(A12, A22, Divide), addMatrix(B21, B22, Divide), Divide); // a12 - a22 * b21 + b22
	vector<vector<int>> conqured7 = strassenMatrixMultiply(subtractMatrix(A11, A21, Divide), addMatrix(B11, B12, Divide), Divide); // a11 - a21 * b11 + b12



    // Calculate four submatrices dividedC11 dividedC12 dividedC21, dividedC22
    vector<vector<int>> dividedC11 = subtractMatrix(addMatrix(addMatrix(conqured5, conqured4, Divide), conqured6, Divide), conqured2, Divide);// adds conq 4 5 6 subtracts conq 2
    vector<vector<int>> dividedC12 = addMatrix(conqured1, conqured2, Divide);//adds conq 1 2
    vector<vector<int>> dividedC21 = addMatrix(conqured3, conqured4, Divide); //adds conq 3 4
    vector<vector<int>> dividedC22 = subtractMatrix(subtractMatrix(addMatrix(conqured5, conqured1, Divide), conqured3, Divide), conqured7, Divide); // add conq 5 and 1 subtracts conq 3

    // Combine the submatrices to form the childMatrix
    vector<vector<int>> childMatrix(n, vector<int>(n));
    for (int conquerI = 0; conquerI < Divide; ++conquerI) { //outmost loop for rows innermost for collumns
        for (int conquerJ = 0; conquerJ < Divide; ++conquerJ) {
            childMatrix[conquerI][conquerJ] = dividedC11[conquerI][conquerJ];//child matrix[i][j] = c11[i][j]
            childMatrix[conquerI][conquerJ + Divide] = dividedC12[conquerI][conquerJ];//c12
            childMatrix[conquerI + Divide][conquerJ] = dividedC21[conquerI][conquerJ];//c21
            childMatrix[conquerI + Divide][conquerJ + Divide] = dividedC22[conquerI][conquerJ];//c22
        }
    }

    return childMatrix;//return child matrix
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();//set n to size of matrix
    for (int i = 0; i < n; ++i) {//outmost loop for rows innermost for collumns
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";//print matrix
        }
        cout << endl;//nl
    }
}

int main() {
    int n = 2; // The size of the matrices is 2x2
    vector<vector<int>> A = {{1, 3},
                             {7, 5}};//set value to hw3

    vector<vector<int>> B = {{6, 8},
                             {4, 2}};//set value to hw3

    vector<vector<int>> C = strassenMatrixMultiply(A, B, n); //call

    cout << "Matrix A:" << endl;
    printMatrix(A); //print matrix a

    cout << "Matrix B:" << endl;
    printMatrix(B); //print b

    cout << "Matrix C (Result of A * B):" << endl;
    printMatrix(C); //print c

    return 0;
}
