#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template <typename Func>
long long execution_time_ms(Func function, const vector<vector<int> > &A, const vector<vector<int> > &B, string alg) {
  auto start_time = std::chrono::high_resolution_clock::now();
  function(A, B, alg);
  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}
// Función para leer una matrix
void read_matrix(vector<vector<int> > &M){
  for(auto &row : M)
    for(auto &element : row) cin>>element;
}

// Función para imprimir una matrxi en consola
void print_matrix(const vector<vector<int> > &M){
  for(int i = 0; i < M.size(); i++){
    for(int j = 0; j < M[i].size(); j++)
      cout<<M[i][j]<<" ";
    cout<<endl;
  }
}

// Función para sumar dos matrices
vector<vector<int> > matrixAddition(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int> > result(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

vector<vector<int> > matrixSubtraction(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int> > result(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Función de multiplicación de matrices tradicional
vector<vector<int> > standard_mm(const vector<vector<int> > &A, const vector<vector<int> > &B) {
  int n = A.size();
  int m = A[0].size();
  int k = B[0].size();

  vector<vector<int> > C(n, vector<int>(k, 0));

  for(int i = 0; i < n; i++) 
    for(int j = 0; j < k; j++)
      for(int k = 0; k < m; k++)
        C[i][j] += A[i][k] * B[k][j];

  return C;
}

// Función de multiplicación de matrices con uso de traspuesta
vector<vector<int> > transpose_mm(const vector<vector<int> > &A, const vector<vector<int> > &B) {
  int n = A.size();
  int m = A[0].size();
  int k = B[0].size();

  vector<vector<int> > Bt(k, vector<int>(m, 0));

  for(int i = 0; i < k; i++) 
    for(int j = 0; j < m; j++) 
      Bt[i][j] = B[j][i];

  vector<vector<int> > C(n, vector<int>(k, 0));

  for(int i = 0; i < n; i++)
    for(int j = 0; j < k; j++){
      int dotProduct = 0;
      for(int k = 0; k < m; k++)
        dotProduct += A[i][k] * Bt[j][k];
      C[i][j] = dotProduct;
    }

  return C;
}          

// Función de multiplicación Strassen
vector<vector<int> > strassen(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();
    
    // Verificar si las matrices pueden ser multiplicadas
    if (colsA != rowsB) {
        cerr << "Las matrices no pueden ser multiplicadas" << endl;
        exit(1);
    }
    
    // Verificar si las matrices son de tamaño 1x1
    if (rowsA == 1 && colsA == 1 && rowsB == 1 && colsB == 1) {
        vector<vector<int> > result(1, vector<int>(1));
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }
    
    // Dividir las matrices en cuatro submatrices
    int halfRowsA = rowsA / 2;
    int halfColsA = colsA / 2;
    int halfRowsB = rowsB / 2;
    int halfColsB = colsB / 2;
    
    vector<vector<int> > A11(halfRowsA, vector<int>(halfColsA));
    vector<vector<int> > A12(halfRowsA, vector<int>(halfColsA));
    vector<vector<int> > A21(halfRowsA, vector<int>(halfColsA));
    vector<vector<int> > A22(halfRowsA, vector<int>(halfColsA));
    
    vector<vector<int> > B11(halfRowsB, vector<int>(halfColsB));
    vector<vector<int> > B12(halfRowsB, vector<int>(halfColsB));
    vector<vector<int> > B21(halfRowsB, vector<int>(halfColsB));
    vector<vector<int> > B22(halfRowsB, vector<int>(halfColsB));
    
    for (int i = 0; i < halfRowsA; i++) {
        for (int j = 0; j < halfColsA; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + halfColsA];
            A21[i][j] = A[i + halfRowsA][j];
            A22[i][j] = A[i + halfRowsA][j + halfColsA];
        }
    }
    
    for (int i = 0; i < halfRowsB; i++) {
        for (int j = 0; j < halfColsB; j++) {
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + halfColsB];
            B21[i][j] = B[i + halfRowsB][j];
            B22[i][j] = B[i + halfRowsB][j + halfColsB];
        }
    }
    
    // Calcular siete productos de matrices recursivamente
    vector<vector<int> > P1 = strassen(A11, matrixSubtraction(B12, B22));
    vector<vector<int> > P2 = strassen(matrixAddition(A11, A12), B22);
    vector<vector<int> > P3 = strassen(matrixAddition(A21, A22), B11);
    vector<vector<int> > P4 = strassen(A22, matrixSubtraction(B21, B11));
    vector<vector<int> > P5 = strassen(matrixAddition(A11, A22), matrixAddition(B11, B22));
    vector<vector<int> > P6 = strassen(matrixSubtraction(A12, A22), matrixAddition(B21, B22));
    vector<vector<int> > P7 = strassen(matrixSubtraction(A11, A21), matrixAddition(B11, B12));
    
    // Calcular las submatrices del resultado final
    vector<vector<int> > C11 = matrixAddition(matrixSubtraction(matrixAddition(P5, P4), P2), P6);
    vector<vector<int> > C12 = matrixAddition(P1, P2);
    vector<vector<int> > C21 = matrixAddition(P3, P4);
    vector<vector<int> > C22 = matrixSubtraction(matrixSubtraction(matrixAddition(P5, P1), P3), P7);
    
    // Combinar las submatrices en una matriz resultante
    vector<vector<int> > result(rowsA, vector<int>(colsB));
    for (int i = 0; i < halfRowsA; i++) {
        for (int j = 0; j < halfColsB; j++) {
            result[i][j] = C11[i][j];
            result[i][j + halfColsB] = C12[i][j];
            result[i + halfRowsA][j] = C21[i][j];
            result[i + halfRowsA][j + halfColsB] = C22[i][j];
        }
    }
    return result;
}

// Funcion máster de selección de algoritmo de multiplicación
vector<vector<int> > matrix_multiplication(const vector<vector<int> > &A, const vector<vector<int> > &B, string alg){
  if(alg == "transpose_mm") return transpose_mm(A,B);
  if(alg == "strassen_mm") return strassen(A,B);
  if(alg == "standard_mm") return standard_mm(A,B);
}

