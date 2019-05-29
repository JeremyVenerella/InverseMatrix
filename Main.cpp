#include <iostream>
#include <math.h>

int calculateDeterminant(int * matrix, int matrixSize);
int * cofactorMatrix(int * matrix, int matrixSize);
double * matrixInverse(int * matrix, int matrixSize);
void printSquareMatrix(int * matrix, int matrixSize);
void printSquareMatrix(double * matrix, int matrixSize);

using namespace std;

int main() {
   const int squareMatrix2Size = 2;
   const int squareMatrix3Size = 3;
   const int squareMatrix4Size = 4;
   const int squareMatrix5Size = 5;
   double * inverseMatrix2 = nullptr;
   double * inverseMatrix3 = nullptr;
   double * inverseMatrix4 = nullptr;
   double * inverseMatrix5 = nullptr;

   //Determinant = -1
   int squareMatrix2[squareMatrix2Size][squareMatrix2Size] = { { 4, 11 },
                                                               { 3, 8}};
   //Determinant = -16296
   int squareMatrix3[squareMatrix3Size][squareMatrix3Size] = {{ 17, 23, 15 },
                                                              { 44, 29, 52 },
                                                              { 21, 63, 35 }};
   //Determinant = 1529496
   int squareMatrix4[squareMatrix4Size][squareMatrix4Size] = {{  1,  4, -1,  0 },
                                                              {  2,  3,  5, -2 },
                                                              {  0,  3,  1,  6 },
                                                              {  3,  0,  2,  1 }};
   //Determinant = 200298426
   int squareMatrix5[squareMatrix5Size][squareMatrix5Size] = {{  3,  6, 11, 21, 74},
                                                              { 33, 12, 41, 61, 55},
                                                              { 21,  6, 91, 57, 81},
                                                              {  3, 71, 42, 12, 38},
                                                              { 51, 95, 19, 44,  2}};

   cout << "-------2x2-MATRIX-------" << endl;
   cout << "-------INVERSE-MATRIX-------" << endl;
   inverseMatrix2 = matrixInverse((int*)squareMatrix2, squareMatrix2Size);
   printSquareMatrix(inverseMatrix2, squareMatrix2Size);

   cout << "-------3x3-MATRIX-------" << endl;
   cout << "-------INVERSE-MATRIX-------" << endl;
   inverseMatrix3 = matrixInverse((int*)squareMatrix3, squareMatrix3Size);
   printSquareMatrix(inverseMatrix3, squareMatrix3Size);

   cout << "-------4x4-MATRIX-------" << endl;
   cout << "-------INVERSE-MATRIX-------" << endl;
   inverseMatrix4 = matrixInverse((int*)squareMatrix4, squareMatrix4Size);
   printSquareMatrix(inverseMatrix4, squareMatrix4Size);

   cout << "-------5x5-MATRIX-------" << endl;
   cout << "-------INVERSE-MATRIX-------" << endl;
   inverseMatrix5 = matrixInverse((int*)squareMatrix5, squareMatrix5Size);
   printSquareMatrix(inverseMatrix5, squareMatrix5Size);

   delete[] inverseMatrix2;
   delete[] inverseMatrix3;
   delete[] inverseMatrix4;
   delete[] inverseMatrix5;

   return 0;
}

int * cofactorMatrix(int * matrix, int matrixSize) {
   int newMatrixSize = 0;
   int *cofactorMatrix = nullptr;
   if (matrixSize > 0) {
      cofactorMatrix = new int[matrixSize*matrixSize];
      newMatrixSize = matrixSize - 1;
      for (int rowSkip = 0; rowSkip < matrixSize; rowSkip++) {
         for (int columnSkip = 0; columnSkip < matrixSize; columnSkip++) {
            int *newSquareMatrix = new int[newMatrixSize*newMatrixSize];//create a smaller matrix
            for (int i = 0; i < matrixSize; i++) {
               for (int j = 0; j < matrixSize; j++) {
                  if (j == columnSkip || i == rowSkip) {//skip the rest of the column 				
                     continue;
                  }//fill smaller matrix bases on skipped column/row.If last column/row skip, no change. If column/row 0 skipped, shift rest of columns/rows left. Else, don't if middle column/row skipped, don't move columns/rows left of skip and move columns/rows right of skip to the left.
                  newSquareMatrix[(((rowSkip == matrixSize - 1) ? i : ((rowSkip == 0) ? (i - 1) : ((i < rowSkip) ? i : i - 1)))) * newMatrixSize +
                     ((columnSkip == matrixSize - 1) ? j : ((columnSkip == 0) ? (j - 1) : ((j < columnSkip) ? j : j - 1)))] = matrix[i * matrixSize + j];
               }
            }
            //printSquareMatrix(newSquareMatrix, newMatrixSize);
            cofactorMatrix[rowSkip * matrixSize + columnSkip] = (matrixSize == 2)? (newSquareMatrix[0] * (pow(-1, rowSkip + 1 + columnSkip + 1))) : 
                                                    calculateDeterminant(newSquareMatrix, newMatrixSize) * (pow(-1, rowSkip + 1 + columnSkip + 1));
            delete[] newSquareMatrix;
         }
      }
   }
   //printSquareMatrix(cofactorMatrix, matrixSize);
   return cofactorMatrix;
}

int calculateDeterminant(int * matrix, int matrixSize) {
   int determinant = 0;
   int newMatrixDeterminant = 0;
   int newMatrixSize = 0;

   if (matrixSize > 2) {
      newMatrixSize = matrixSize - 1;
      for (int columnSkip = 0; columnSkip < matrixSize; columnSkip++) {
         int *newSquareMatrix = new int[newMatrixSize*newMatrixSize];//create a smaller matrix
         for (int i = 1; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
               if (j == columnSkip) {//skip the rest of the column 				
                  continue;
               }//fill smaller matrix bases on skipped column.If last column skip, no change. If column 0 skipped, shift rest of columns left. Else, don't if middle column skipped, don't move columns left of skip and move columns right of skip to the left.
               newSquareMatrix[(i - 1) * newMatrixSize + ((columnSkip == matrixSize - 1) ? j :((columnSkip == 0)? (j-1) : ((j < columnSkip)? j : j-1)))] = matrix[i * matrixSize + j];
            }
         }
         newMatrixDeterminant = matrix[columnSkip] * calculateDeterminant((int *)newSquareMatrix, newMatrixSize);
         determinant += ((columnSkip % 2 == 0) ? newMatrixDeterminant : newMatrixDeterminant * -1);
         delete[] newSquareMatrix;
      }
   }
   else {
      determinant = (matrix[0] * matrix[matrixSize + 1]) - (matrix[1] * matrix[matrixSize]); //return 2x2 determinant
   }
   return determinant;
}

double * matrixInverse(int * matrix, int matrixSize) {
   int * newcofactorMatrix = nullptr;
   double *newSquareMatrix = nullptr;
   int determinant = 0;

   determinant = calculateDeterminant(matrix, matrixSize);
   newSquareMatrix = new double[matrixSize*matrixSize];
   newcofactorMatrix = cofactorMatrix(matrix, matrixSize);

   for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
         newSquareMatrix[i * matrixSize + j] = newcofactorMatrix[i * matrixSize + j] * (1.0f / determinant);
      }
   }
   return newSquareMatrix;
}

void printSquareMatrix(int * matrix, int matrixSize) {
   for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
         cout << matrix[i * matrixSize + j] << " ";
      }
      cout << endl;
   }
   cout << "---------------------------" << endl;
}

void printSquareMatrix(double * matrix, int matrixSize) {
   cout.precision(17);
   for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
         cout << matrix[i * matrixSize + j] << " ";
      }
      cout << endl;
   }
   cout << "---------------------------" << endl;
}