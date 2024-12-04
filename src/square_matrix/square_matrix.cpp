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

int SquareMatrix::getSize() const {
    return _size;
}

bool SquareMatrix::getIsAllocated() const {
    return _isAllocated;
}

void SquareMatrix::allocateMemory() {
    try {
        _data = new int* [_size];
        for (int i = 0; i < _size; ++i) {
            _data[i] = new int[_size]();  // Initialize to 0
        }
        _isAllocated = true;
    }
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("Memory allocation failed: " + std::string(e.what()));
    }
}

void SquareMatrix::deallocateMemory() {
    if (_isAllocated && _data != nullptr) {
        for (int i = 0; i < _size; ++i) {
            delete[] _data[i];
        }

        delete[] _data;
        _data = nullptr;
        _isAllocated = false;
    }
}

void SquareMatrix::copyData(const SquareMatrix& other) {
    if (!other._isAllocated) {
        throw std::runtime_error("Cannot copy from unallocated matrix");
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = other._data[i][j];
        }
    }
}

SquareMatrix::SquareMatrix() : _size(0), _data(nullptr), _isAllocated(false) {}

SquareMatrix::SquareMatrix(int size) : _size(size), _data(nullptr), _isAllocated(false) {
    if (size <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }
    allocateMemory();
}

SquareMatrix::SquareMatrix(int size, const int* rowData) : _size(size), _data(nullptr), _isAllocated(false) {
    if (size <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }

    if (rowData == nullptr) {
        throw std::invalid_argument("Input array cannot be null");
    }

    allocateMemory();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            _data[i][j] = rowData[i * size + j];
        }
    }
}

SquareMatrix::SquareMatrix(SquareMatrix& other) : _size(other._size), _data(nullptr), _isAllocated(false) {
    if (other._isAllocated) {
        allocateMemory();
        copyData(other);
    }
}

SquareMatrix::~SquareMatrix() {
    deallocateMemory();
}

SquareMatrix& SquareMatrix::allocate(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }

    if (_isAllocated) {
        if (size == size) return *this;
        deallocateMemory();
    }

    size = size;
    allocateMemory();

    return *this;
}

SquareMatrix& SquareMatrix::insert(int row, int col, int value) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    if (row < 0 || row >= _size || col < 0 || col >= _size) {
        throw std::out_of_range("Matrix indices out of bounds");
    }

    _data[row][col] = value;

    return *this;
}

int SquareMatrix::get(int row, int col) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    if (row < 0 || row >= _size || col < 0 || col >= _size) {
        throw std::out_of_range("Matrix indices out of bounds");
    }

    return _data[row][col];
}

SquareMatrix& SquareMatrix::transpose() {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = i + 1; j < _size; ++j) {
            std::swap(_data[i][j], _data[j][i]);
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::randomize() {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = dis(gen);
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::randomize(int count) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    if (count > _size * _size) {
        throw std::invalid_argument("Count exceeds matrix size");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::uniform_int_distribution<> pos(0, _size - 1);

    // Reset matrix to zeros
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = 0;
        }
    }

    // Fill random positions
    for (int k = 0; k < count; ++k) {
        int i = pos(gen);
        int j = pos(gen);
        _data[i][j] = dis(gen);
    }

    return *this;
}

SquareMatrix& SquareMatrix::insertMainDiagonal(const int* mainDiagonalData) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < _size; ++i) {
        _data[i][i] = mainDiagonalData[i];
    }

    return *this;
}

SquareMatrix& SquareMatrix::insertDiagonal(int offset, const int* diagonalData) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    if (offset >= _size || offset <= -_size) {
        throw std::invalid_argument("Offset out of bounds");
    }

    int startRow = (offset >= 0) ? 0 : -offset;
    int startCol = (offset >= 0) ? offset : 0;
    int count = (offset >= 0) ? _size - offset : _size + offset;

    for (int i = 0; i < count; ++i) {
        _data[startRow + i][startCol + i] = diagonalData[i];
    }

    return *this;
}

SquareMatrix& SquareMatrix::insertColumn(int col, const int* columnData) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    if (col < 0 || col >= _size) {
        throw std::out_of_range("Column index out of bounds");
    }

    for (int i = 0; i < _size; ++i) {
        _data[i][col] = columnData[i];
    }

    return *this;
}

SquareMatrix& SquareMatrix::insertRow(int row, const int* rowData) {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    if (row < 0 || row >= _size) {
        throw std::out_of_range("Row index out of bounds");
    }

    for (int i = 0; i < _size; ++i) {
        _data[row][i] = rowData[i];
    }

    return *this;
}

SquareMatrix& SquareMatrix::fillDiagonal() {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = (i == j) ? 1 : 0;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::fillUnderDiagonal() {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = (i > j) ? 1 : 0;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::fillOverDiagonal() {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = (i < j) ? 1 : 0;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::fillChessboardStyle() {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] = (i + j) % 2;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::operator+(const SquareMatrix& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    SquareMatrix* result = new SquareMatrix(_size);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            result->_data[i][j] = _data[i][j] + other._data[i][j];
        }
    }

    return *result;
}

SquareMatrix& SquareMatrix::operator*(const SquareMatrix& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    SquareMatrix* result = new SquareMatrix(_size);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            result->_data[i][j] = 0;
            for (int k = 0; k < _size; ++k) {
                result->_data[i][j] += _data[i][k] * other._data[k][j];
            }
        }
    }

    return *result;
}

SquareMatrix& SquareMatrix::operator+(int scalar) const {
    SquareMatrix* result = new SquareMatrix(_size);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            result->_data[i][j] = _data[i][j] + scalar;
        }
    }

    return *result;
}

SquareMatrix& SquareMatrix::operator*(int scalar) const {
    SquareMatrix* result = new SquareMatrix(_size);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            result->_data[i][j] = _data[i][j] * scalar;
        }
    }

    return *result;
}

SquareMatrix& SquareMatrix::operator-(int scalar) const {
    SquareMatrix* result = new SquareMatrix(_size);

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            result->_data[i][j] = _data[i][j] - scalar;
        }
    }

    return *result;
}

SquareMatrix operator+(int scalar, const SquareMatrix& matrix) {
    return matrix + scalar;
}

SquareMatrix operator*(int scalar, const SquareMatrix& matrix) {
    return matrix * scalar;
}

SquareMatrix& SquareMatrix::operator++(int) {
    return *this += 1;
}

SquareMatrix& SquareMatrix::operator--(int) {
    return *this -= 1;
}

SquareMatrix& SquareMatrix::operator+=(int scalar) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] += scalar;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::operator-=(int scalar) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] -= scalar;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::operator*=(int scalar) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] *= scalar;
        }
    }

    return *this;
}

SquareMatrix& SquareMatrix::operator+=(double scalar) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            _data[i][j] += scalar;
        }
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const SquareMatrix& matrix) {
    if (!matrix._isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    for (int i = 0; i < matrix._size; ++i) {
        for (int j = 0; j < matrix._size; ++j) {
            os << std::setw(4) << matrix._data[i][j];
        }
        os << "\n";
    }

    return os;
}

bool SquareMatrix::operator==(const SquareMatrix& other) const {
    if (_size != other._size) {
        return false;
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (_data[i][j] != other._data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool SquareMatrix::operator>(const SquareMatrix& other) const {
    if (_size != other._size) {
        return false;
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (_data[i][j] <= other._data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool SquareMatrix::operator<(const SquareMatrix& other) const {
    if (_size != other._size) {
        return false;
    }

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if (_data[i][j] >= other._data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool SquareMatrix::operator!=(const SquareMatrix& other) const {
    return !(*this == other);
}

void SquareMatrix::displayFull() const {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    // Display column headers
    std::cout << "     ";
    for (int j = 0; j < _size; ++j) {
        std::cout << std::setw(4) << j;
    }
    std::cout << "\n";

    // Display separator
    std::cout << "    ";
    for (int j = 0; j < _size * 4 + 1; ++j) {
        std::cout << "-";
    }
    std::cout << "\n";

    // Display matrix with row numbers
    for (int i = 0; i < _size; ++i) {
        std::cout << std::setw(3) << i << " |";
        for (int j = 0; j < _size; ++j) {
            std::cout << std::setw(4) << _data[i][j];
        }
        std::cout << "\n";
    }
}

void SquareMatrix::displayTruncated() const {
    if (!_isAllocated) {
        throw std::runtime_error("Matrix not allocated");
    }

    const int show_rows = 8; // Number of rows to show at start and end

    // Display first rows
    for (int i = 0; i < std::min(show_rows, _size); ++i) {
        std::cout << std::setw(3) << i << " |";
        for (int j = 0; j < std::min(show_rows, _size); ++j) {
            std::cout << std::setw(4) << _data[i][j];
        }
        if (_size > show_rows) {
            std::cout << " ... " << std::setw(4) << _data[i][_size - 1];
        }
        std::cout << "\n";
    }

    // Display middle separator if needed
    if (_size > show_rows * 2) {
        std::cout << "     ...\n";
    }

    // Display last rows
    if (_size > show_rows) {
        for (int i = _size - show_rows; i < _size; ++i) {
            std::cout << std::setw(3) << i << " |";
            for (int j = 0; j < std::min(show_rows, _size); ++j) {
                std::cout << std::setw(4) << _data[i][j];
            }

            std::cout << " ... " << std::setw(4) << _data[i][_size - 1];
            std::cout << "\n";
        }
    }
}
