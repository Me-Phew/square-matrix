/**
 * @author Marcin Dudek
 * @author Mateusz Basiaga (basmateusz@wp.pl)
 * @brief
 * @date 2024-11-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <fstream>
#include <random>

#include "square_matrix.hpp"
#include "utils/common/common.hpp"

int main() {
  const int SIZE = 50;

  SquareMatrix matrix1(SIZE);

  printSeparator();
  std::cout << "Initial empty matrix 1:" << std::endl;
  std::cout << matrix1;

  // Fill matrix1 with random values
  matrix1.randomize();
  printSeparator();
  std::cout << "Matrix 1 after randomization:" << std::endl;
  std::cout << matrix1;

  SquareMatrix matrix2(SIZE);

  // Fill matrix2 with chess pattern
  matrix2.fillChessboardStyle();
  printSeparator();
  std::cout << "Matrix 2 with chessboard pattern:" << std::endl;
  std::cout << matrix2;

  SquareMatrix matrix3;

  // Test matrix addition
  matrix3 = matrix1 + matrix2;
  printSeparator();
  std::cout << "Matrix 3 (Matrix 1 + Matrix 2):" << std::endl;
  std::cout << matrix3;

  // Test scalar operations
  matrix1 = matrix1 * 2;
  printSeparator();
  std::cout << "Matrix 1 multiplied by 2:" << std::endl;
  std::cout << matrix1;

  matrix1 = matrix1 + 5;
  printSeparator();
  std::cout << "Matrix 1 plus 5:" << std::endl;
  std::cout << matrix1;

  // Test diagonal operations
  int* diagonal = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    diagonal[i] = i + 1;
  }

  matrix2.insertMainDiagonal(diagonal);
  printSeparator();
  std::cout << "Matrix 2 with numbered main diagonal:" << std::endl;
  std::cout << matrix2;

  // Test diagonal fills
  matrix3.fillDiagonal();
  printSeparator();
  std::cout << "Matrix 3 with filled diagonal:" << std::endl;
  std::cout << matrix3;

  matrix3.fillOverDiagonal();
  printSeparator();
  std::cout << "Matrix 3 with filled over-diagonal:" << std::endl;
  std::cout << matrix3;

  matrix3.fillUnderDiagonal();
  printSeparator();
  std::cout << "Matrix 3 with filled under-diagonal:" << std::endl;
  std::cout << matrix3;

  // Test transpose
  matrix1.transpose();
  printSeparator();
  std::cout << "Matrix 1 transposed:" << std::endl;
  std::cout << matrix1;

  // Test comparison operators
  printSeparator();
  std::cout << "Matrix comparisons:" << std::endl;
  std::cout << "Matrix 1 == Matrix 2: " << (matrix1 == matrix2) << std::endl;
  std::cout << "Matrix 1 > Matrix 2: " << (matrix1 > matrix2) << std::endl;
  std::cout << "Matrix 1 < Matrix 2: " << (matrix1 < matrix2) << std::endl;
  std::cout << "Matrix 1 != Matrix 2: " << (matrix1 != matrix2) << std::endl;

  // Test increment/decrement
  matrix1++;
  printSeparator();
  std::cout << "Matrix 1 after increment:" << std::endl;
  std::cout << matrix1;

  matrix1--;
  printSeparator();
  std::cout << "Matrix 1 after decrement:" << std::endl;
  std::cout << matrix1;

  // Clean up
  delete[] diagonal;

  // Test constructors
  int* data = new int[SIZE * SIZE];
  for (int i = 0; i < SIZE * SIZE; i++) {
    data[i] = i;
  }

  SquareMatrix matrix4(SIZE, data);
  printSeparator();
  std::cout << "Matrix 4 created with data array:" << std::endl;
  std::cout << matrix4;

  // Copy constructor
  SquareMatrix matrix5(matrix4);
  printSeparator();
  std::cout << "Matrix 5 copied from Matrix 4:" << std::endl;
  std::cout << matrix5;

  // Test allocate
  SquareMatrix matrix6;
  matrix6.allocate(SIZE);
  printSeparator();
  std::cout << "Matrix 6 after allocation:" << std::endl;
  std::cout << matrix6;

  // Test insert and get
  matrix6.insert(0, 0, 42);
  printSeparator();
  std::cout << "Value at (0,0): " << matrix6.get(0, 0) << std::endl;

  // Test randomize with count
  matrix6.randomize(SIZE * SIZE / 2); // Fill half the matrix with random values
  printSeparator();
  std::cout << "Matrix 6 partially randomized:" << std::endl;
  std::cout << matrix6;

  // Test insertDiagonal with offset
  int* offsetDiagonal = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    offsetDiagonal[i] = i * 2;
  }
  matrix6.insertDiagonal(1, offsetDiagonal);
  printSeparator();
  std::cout << "Matrix 6 with offset diagonal:" << std::endl;
  std::cout << matrix6;

  // Test insertColumn and insertRow
  int* columnData = new int[SIZE];
  int* rowData = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    columnData[i] = 99;
    rowData[i] = 88;
  }
  matrix6.insertColumn(0, columnData);
  matrix6.insertRow(0, rowData);
  printSeparator();
  std::cout << "Matrix 6 with new column and row:" << std::endl;
  std::cout << matrix6;

  // Test matrix multiplication
  SquareMatrix matrix7(SIZE);
  matrix7.fillDiagonal();
  SquareMatrix result = matrix6 * matrix7;
  printSeparator();
  std::cout << "Result of Matrix 6 * Matrix 7:" << std::endl;
  std::cout << result;

  // Test scalar operations with friends and compound operators
  matrix6 = 2 + matrix6;
  printSeparator();
  std::cout << "After scalar addition (friend):" << std::endl;
  std::cout << matrix6;

  matrix6 = 2 * matrix6;
  printSeparator();
  std::cout << "After scalar multiplication (friend):" << std::endl;
  std::cout << matrix6;

  matrix6 = 10 - matrix6;
  printSeparator();
  std::cout << "After scalar subtraction (friend):" << std::endl;
  std::cout << matrix6;

  matrix6 += 5;
  printSeparator();
  std::cout << "After compound addition:" << std::endl;
  std::cout << matrix6;

  matrix6 -= 3;
  printSeparator();
  std::cout << "After compound subtraction:" << std::endl;
  std::cout << matrix6;

  matrix6 *= 2;
  printSeparator();
  std::cout << "After compound multiplication:" << std::endl;
  std::cout << matrix6;

  matrix6 += 1.5;
  printSeparator();
  std::cout << "After compound addition with double:" << std::endl;
  std::cout << matrix6;

  // Clean up
  delete[] data;
  delete[] offsetDiagonal;
  delete[] columnData;
  delete[] rowData;

  return 0;
}
