/**
 * @author Marcin Dudek
 * @author Mateusz Basiaga (basmateusz@wp.pl)
 * @brief
 * @date 2024-11-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "square_matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <random>

// Helper methods
void SquareMatrix::allocateMemory() {
    try {
        data = new int*[size];
        for (int i = 0; i < size; ++i) {
            data[i] = new int[size]();  // Initialize to 0
        }
        isAllocated = true;
    }
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("Memory allocation failed: " + std::string(e.what()));
    }
}

void SquareMatrix::deallocateMemory() {
    if (isAllocated && data != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
        isAllocated = false;
    }
}

void SquareMatrix::copyData(const SquareMatrix& other) {
    if (!other.isAllocated) {
        throw std::runtime_error("Cannot copy from unallocated matrix");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Constructors and destructor
SquareMatrix::SquareMatrix() : size(0), data(nullptr), isAllocated(false) {}

SquareMatrix::SquareMatrix(int n) : size(n), data(nullptr), isAllocated(false) {
    if (n <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }
    allocateMemory();
}

SquareMatrix::SquareMatrix(int n, int* t) : size(n), data(nullptr), isAllocated(false) {
    if (n <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }
    if (t == nullptr) {
        throw std::invalid_argument("Input array cannot be null");
    }
    allocateMemory();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = t[i * size + j];
        }
    }
}

SquareMatrix::SquareMatrix(const SquareMatrix& m) : size(m.size), data(nullptr), isAllocated(false) {
    if (m.isAllocated) {
        allocateMemory();
        copyData(m);
    }
}

SquareMatrix::~SquareMatrix() {
    deallocateMemory();
}

// Memory management
SquareMatrix& SquareMatrix::allocate(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }
    if (isAllocated) {
        if (size == n) return *this;
        deallocateMemory();
    }
    size = n;
    allocateMemory();
    return *this;
}

// Basic operations
SquareMatrix& SquareMatrix::insert(int x, int y, int value) {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    if (x < 0 || x >= size || y < 0 || y >= size) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    data[x][y] = value;
    return *this;
}

int SquareMatrix::get(int x, int y) const {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    if (x < 0 || x >= size || y < 0 || y >= size) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    return data[x][y];
}

// Add any missing methods from your header file here...

// Random number generation
SquareMatrix& SquareMatrix::randomize() {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = dis(gen);
        }
    }
    return *this;
}

SquareMatrix& SquareMatrix::randomize(int count) {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    if (count > size * size) {
        throw std::invalid_argument("Count exceeds matrix size");
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::uniform_int_distribution<> pos(0, size - 1);
    
    // Reset matrix to zeros
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = 0;
        }
    }
    
    // Fill random positions
    for (int k = 0; k < count; ++k) {
        int i = pos(gen);
        int j = pos(gen);
        data[i][j] = dis(gen);
    }
    return *this;
}

// Matrix operations
SquareMatrix& SquareMatrix::transpose() {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            std::swap(data[i][j], data[j][i]);
        }
    }
    return *this;
}

// Operators
bool SquareMatrix::operator==(const SquareMatrix& other) const {
    if (!isAllocated || !other.isAllocated || size != other.size) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (data[i][j] != other.data[i][j]) return false;
        }
    }
    return true;
}

bool SquareMatrix::operator!=(const SquareMatrix& other) const {
    return !(*this == other);
}

// Output operator
std::ostream& operator<<(std::ostream& os, const SquareMatrix& matrix) {
    if (!matrix.isAllocated) {
        os << "Unallocated matrix";
        return os;
    }
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            os << std::setw(4) << matrix.data[i][j];
        }
        os << std::endl;
    }
    return os;
}

SquareMatrix& SquareMatrix::fillDiagonal() {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = (i == j) ? 1 : 0;
        }
    }
    return *this;
}

SquareMatrix& SquareMatrix::fillChessboardStyle() {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = (i + j) % 2;
        }
    }
    return *this;
}

SquareMatrix& SquareMatrix::operator=(const SquareMatrix& other) {
    if (this != &other) {
        if (!isAllocated || size != other.size) {
            deallocateMemory();
            size = other.size;
            allocateMemory();
        }
        copyData(other);
    }
    return *this;
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    SquareMatrix result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    SquareMatrix result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

SquareMatrix& SquareMatrix::operator+=(int scalar) {
    if (!isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] += scalar;
        }
    }
    return *this;
}

bool SquareMatrix::operator>(const SquareMatrix& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (data[i][j] <= other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool SquareMatrix::operator<(const SquareMatrix& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (data[i][j] >= other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}