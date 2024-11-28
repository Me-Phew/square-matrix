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
    int size;
    int** data;
    bool isAllocated;
    static int displayWidth;

    void allocateMemory();
    void deallocateMemory();
    void copyData(const SquareMatrix& other);
    

public:
    // Constructors and destructor
    SquareMatrix();  // Default constructor
    SquareMatrix(int n);  // Size constructor
    SquareMatrix(int n, int* t);  // Data constructor
    SquareMatrix(const SquareMatrix& m);  // Copy constructor
    ~SquareMatrix();  // Destructor

    void displayFull() const;
    void displayTruncated() const;
    static void setDisplayPrecision(int width);

    // Memory management
    SquareMatrix& allocate(int n);
    
    // Basic operations
    SquareMatrix& insert(int x, int y, int value);
    int get(int x, int y) const;
    SquareMatrix& transpose();
    
    // Filling methods
    SquareMatrix& randomize();
    SquareMatrix& randomize(int count);
    SquareMatrix& insertMainDiagonal(int* t);
    SquareMatrix& insertDiagonal(int k, int* t);
    SquareMatrix& insertColumn(int x, int* t);
    SquareMatrix& insertRow(int y, int* t);
    SquareMatrix& fillDiagonal();
    SquareMatrix& fillUnderDiagonal();
    SquareMatrix& fillOverDiagonal();
    SquareMatrix& fillChessboardStyle();

    // Operators
    SquareMatrix& operator=(const SquareMatrix& other);
    SquareMatrix operator+(const SquareMatrix& other) const;
    SquareMatrix operator*(const SquareMatrix& other) const;
    SquareMatrix operator+(int scalar) const;
    SquareMatrix operator-(int scalar) const;
    SquareMatrix operator*(int scalar) const;
    SquareMatrix& operator+=(int scalar);
    SquareMatrix& operator-=(int scalar);
    SquareMatrix& operator*=(int scalar);
    SquareMatrix& operator++();
    SquareMatrix operator++(int);
    SquareMatrix& operator--();
    SquareMatrix operator--(int);

    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& matrix);
    friend SquareMatrix operator+(int scalar, const SquareMatrix& matrix);
    friend SquareMatrix operator-(int scalar, const SquareMatrix& matrix);
    friend SquareMatrix operator*(int scalar, const SquareMatrix& matrix);

    // Comparison operators
    bool operator==(const SquareMatrix& other) const;
    bool operator!=(const SquareMatrix& other) const;  // Add this line
    bool operator>(const SquareMatrix& other) const;
    bool operator<(const SquareMatrix& other) const;

    // Utility methods
    int getSize() const { return size; }
    bool isInitialized() const { return isAllocated; }
};

#endif // SQUARE_MATRIX_HPP