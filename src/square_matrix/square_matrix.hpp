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
private:
    int _size;
    int** _data;
    bool _isAllocated;

    void allocateMemory();
    void deallocateMemory();
    void copyData(const SquareMatrix& other);

public:
    int getSize() const;
    bool getIsAllocated() const;

    SquareMatrix();

    explicit SquareMatrix(int size);

    SquareMatrix(int size, const int* rowData);

    SquareMatrix(SquareMatrix& other);

    ~SquareMatrix();

    SquareMatrix& allocate(int size);

    SquareMatrix& insert(int row, int col, int value);

    int get(int row, int col);

    SquareMatrix& transpose();

    SquareMatrix& randomize();

    SquareMatrix& randomize(int count);

    SquareMatrix& insertMainDiagonal(const int* mainDiagonalData);

    SquareMatrix& insertDiagonal(int offset, const int* diagonalData);

    SquareMatrix& insertColumn(int col, const int* columnData);

    SquareMatrix& insertRow(int row, const int* rowData);

    SquareMatrix& fillDiagonal();

    SquareMatrix& fillUnderDiagonal();

    SquareMatrix& fillOverDiagonal();

    SquareMatrix& fillChessboardStyle();

    SquareMatrix& operator+(const SquareMatrix& other) const;

    SquareMatrix& operator*(const SquareMatrix& other) const;

    SquareMatrix& operator+(int scalar) const;

    SquareMatrix& operator*(int scalar) const;

    SquareMatrix& operator-(int scalar) const;

    friend SquareMatrix operator+(int scalar, const SquareMatrix& matrix);

    friend SquareMatrix operator*(int scalar, const SquareMatrix& matrix);

    friend SquareMatrix operator-(int scalar, const SquareMatrix& matrix);

    SquareMatrix& operator++(int);

    SquareMatrix& operator--(int);

    SquareMatrix& operator+=(int scalar);

    SquareMatrix& operator-=(int scalar);

    SquareMatrix& operator*=(int scalar);

    // todo: not sure about this
    SquareMatrix& operator+=(double);

    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& matrix);

    bool operator==(const SquareMatrix& other) const;

    bool operator>(const SquareMatrix& other) const;

    bool operator<(const SquareMatrix& other) const;

    bool operator!=(const SquareMatrix& other) const;

    void displayFull() const;
    void displayTruncated() const;
};

#endif /* SQUARE_MATRIX_HPP */
