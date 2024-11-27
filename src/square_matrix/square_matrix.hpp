/**
 * @author Marcin Dudek
 * @author Mateusz Basiaga (basmateusz@wp.pl)
 * @brief
 * @date 2024-11-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include <iostream>

class SquareMatrix {
public:
  SquareMatrix();

  SquareMatrix(int size);

  SquareMatrix(int size, int* data);

  SquareMatrix(SquareMatrix& other);

  ~SquareMatrix();

  SquareMatrix& allocate(int size);

  SquareMatrix& insert(int row, int col, int value);

  int get(int row, int col);

  SquareMatrix& transpose();

  SquareMatrix& randomize();

  SquareMatrix& randomize(int count);

  SquareMatrix& insertMainDiagonal(int* data);

  SquareMatrix& insertDiagonal(int offset, int* data);

  SquareMatrix& insertColumn(int col, int* data);

  SquareMatrix& insertRow(int row, int* data);

  SquareMatrix& fillDiagonal();

  SquareMatrix& fillUnderDiagonal();

  SquareMatrix& fillOverDiagonal();

  SquareMatrix& fillChessboardStyle();

  SquareMatrix& operator+(SquareMatrix& other);

  SquareMatrix& operator*(SquareMatrix& other);

  SquareMatrix& operator+(int scalar);

  SquareMatrix& operator*(int scalar);

  SquareMatrix& operator-(int scalar);

  friend SquareMatrix operator+(int scalar, SquareMatrix& matrix);

  friend SquareMatrix operator*(int scalar, SquareMatrix& matrix);

  friend SquareMatrix operator-(int scalar, SquareMatrix& matrix);

  SquareMatrix& operator++(int);

  SquareMatrix& operator--(int);

  SquareMatrix& operator+=(int scalar);

  SquareMatrix& operator-=(int scalar);

  SquareMatrix& operator*=(int scalar);

  // todo: not sure about this
  SquareMatrix& operator+=(double);

  friend std::ostream& operator<<(std::ostream& os, SquareMatrix& matrix);

  bool operator==(const SquareMatrix& other);

  bool operator>(const SquareMatrix& other);

  bool operator<(const SquareMatrix& other);

  bool operator!=(const SquareMatrix& other);
};

#endif /* SQUARE_MATRIX_HPP */
