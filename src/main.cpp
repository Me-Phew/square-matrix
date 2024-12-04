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
#include <stdexcept>
#include <vector>

#include "square_matrix.hpp"
#include "common/common.hpp"

void testConstructors() {
    try {
        std::cout << "\n=== Testing Constructors ===\n";

        SquareMatrix m2(4);
        std::cout << "Size constructor (4x4):\n" << m2 << "\n";

        int data[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
        SquareMatrix m3(4, data);
        std::cout << "Data constructor:\n" << m3 << "\n";

        SquareMatrix m4(m3);
        std::cout << "Copy constructor:\n" << m4 << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error in constructors: " << e.what() << "\n";
    }
}

void testMatrixOperations() {
    try {
        std::cout << "\n=== Testing Matrix Operations ===\n";

        SquareMatrix m(4);
        m.randomize();
        std::cout << "Original matrix:\n" << m << "\n";

        m.transpose();
        std::cout << "Transposed matrix:\n" << m << "\n";

        m.fillDiagonal();
        std::cout << "Diagonal matrix:\n" << m << "\n";

        m.fillChessboardStyle();
        std::cout << "Chessboard pattern:\n" << m << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error in matrix operations: " << e.what() << "\n";
    }
}

void testArithmeticOperators() {
    try {
        std::cout << "\n=== Testing Arithmetic Operators ===\n";

        SquareMatrix m1(4), m2(4);
        m1.randomize();
        m2.randomize();

        std::cout << "Matrix 1:\n" << m1 << "\n";
        std::cout << "Matrix 2:\n" << m2 << "\n";

        SquareMatrix m3 = m1 + m2;
        std::cout << "M1 + M2:\n" << m3 << "\n";

        SquareMatrix m4 = m1 * m2;
        std::cout << "M1 * M2:\n" << m4 << "\n";

        m1 += 5;
        std::cout << "M1 += 5:\n" << m1 << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error in arithmetic operations: " << e.what() << "\n";
    }
}

void testComparisonOperators() {
    try {
        std::cout << "\n=== Testing Comparison Operators ===\n";

        SquareMatrix m1(4), m2(4);
        m1.randomize();
        m2 = m1;

        std::cout << "Testing equality (should be true): " << (m1 == m2) << "\n";
        m2.insert(0, 0, 999);
        std::cout << "Testing inequality (should be true): " << (m1 != m2) << "\n";
        std::cout << "Testing less than: " << (m1 < m2) << "\n";
        std::cout << "Testing greater than: " << (m1 > m2) << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error in comparison operations: " << e.what() << "\n";
    }
}

void testLargeMatrix() {
    try {
        std::cout << "\n=== Testing Large Matrix (30x30) ===\n";

        SquareMatrix large(30);
        large.randomize();

        std::cout << "Full matrix display:\n";
        large.displayFull();

        std::cout << "\nTruncated matrix display:\n";
        large.displayTruncated();

        large.transpose();
        std::cout << "\nTruncated transposed matrix:\n";
        large.displayTruncated();

    }
    catch (const std::exception& e) {
        std::cerr << "Error in large matrix operations: " << e.what() << "\n";
    }
}

int main() {
    try {
        testConstructors();

        printSeparator();
        testMatrixOperations();

        printSeparator();
        testArithmeticOperators();

        printSeparator();
        testComparisonOperators();

        printSeparator();
        testLargeMatrix();

        std::cout << "\nAll tests completed successfully!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}
