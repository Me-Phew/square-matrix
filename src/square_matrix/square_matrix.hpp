/**
 * @author Marcin Dudek
 * @author Mateusz Basiaga (basmateusz@wp.pl)
 * @brief Klasa reprezentująca macierz kwadratową z funkcjonalnościami do modyfikacji i operacji arytmetycznych.
 * @date 2024-11-27
 *
 * @copyright Copyright (c) 2024
 */

#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include <iostream>

 /**
  * @brief Klasa SquareMatrix - implementacja macierzy kwadratowej.
  */
class SquareMatrix {
private:
    int _size; ///< Rozmiar macierzy (liczba wierszy i kolumn).
    int** _data; ///< Wskaźnik na tablicę dwuwymiarową przechowującą dane macierzy.
    bool _isAllocated; ///< Flaga wskazująca, czy pamięć dla macierzy została zaalokowana.

    /// @brief Alokuje pamięć dla danych macierzy.
    void allocateMemory();

    /// @brief Dealokuje pamięć zaalokowaną dla macierzy.
    void deallocateMemory();

    /// @brief Kopiuje dane z innej macierzy.
    /// @param other Obiekt macierzy, z którego dane mają zostać skopiowane.
    void copyData(const SquareMatrix& other);

public:
    /// @brief Zwraca rozmiar macierzy.
    /// @return Rozmiar macierzy (liczba wierszy/kolumn).
    int getSize() const;

    /// @brief Sprawdza, czy pamięć dla macierzy została zaalokowana.
    /// @return True, jeśli pamięć została zaalokowana, w przeciwnym razie False.
    bool getIsAllocated() const;

    /// @brief Konstruktor domyślny.
    SquareMatrix();

    /// @brief Konstruktor tworzący macierz o zadanym rozmiarze.
    /// @param size Rozmiar macierzy.
    explicit SquareMatrix(int size);

    /// @brief Konstruktor tworzący macierz z danymi wiersza.
    /// @param size Rozmiar macierzy.
    /// @param rowData Tablica danych wiersza.
    SquareMatrix(int size, const int* rowData);

    /// @brief Konstruktor kopiujący.
    /// @param other Obiekt macierzy do skopiowania.
    SquareMatrix(SquareMatrix& other);

    /// @brief Destruktor zwalniający zaalokowaną pamięć.
    ~SquareMatrix();

    /// @brief Alokuje pamięć dla macierzy o zadanym rozmiarze.
    /// @param size Rozmiar macierzy.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& allocate(int size);

    /// @brief Wstawia wartość do macierzy.
    /// @param row Indeks wiersza.
    /// @param col Indeks kolumny.
    /// @param value Wartość do wstawienia.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& insert(int row, int col, int value);

    /// @brief Pobiera wartość z macierzy.
    /// @param row Indeks wiersza.
    /// @param col Indeks kolumny.
    /// @return Wartość zadanego elementu macierzy.
    int get(int row, int col);

    /// @brief Transponuje macierz.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& transpose();

    /// @brief Losowo wypełnia macierz.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& randomize();

    /// @brief Losowo wypełnia macierz z ograniczeniem liczby elementów do zmiany.
    /// @param count Liczba elementów do zmiany.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& randomize(int count);

    /// @brief Wstawia dane do głównej przekątnej macierzy.
    /// @param mainDiagonalData Tablica danych do wstawienia.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& insertMainDiagonal(const int* mainDiagonalData);

    /// @brief Wstawia dane do przekątnej z przesunięciem.
    /// @param offset Przesunięcie od głównej przekątnej.
    /// @param diagonalData Tablica danych do wstawienia.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& insertDiagonal(int offset, const int* diagonalData);

    /// @brief Wstawia dane do kolumny macierzy.
    /// @param col Indeks kolumny.
    /// @param columnData Tablica danych do wstawienia.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& insertColumn(int col, const int* columnData);

    /// @brief Wstawia dane do wiersza macierzy.
    /// @param row Indeks wiersza.
    /// @param rowData Tablica danych do wstawienia.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& insertRow(int row, const int* rowData);

    /// @brief Wypełnia główną przekątną macierzy.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& fillDiagonal();

    /// @brief Wypełnia obszar pod główną przekątną macierzy.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& fillUnderDiagonal();

    /// @brief Wypełnia obszar nad główną przekątnią macierzy.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& fillOverDiagonal();

    /// @brief Wypełnia macierz w stylu szachownicy.
    /// @return Referencja do bieżącego obiektu.
    SquareMatrix& fillChessboardStyle();

    /// @brief Operator dodawania macierzy.
    /// @param other Druga macierz do dodania.
    /// @return Nowa macierz będąca wynikiem operacji.
    SquareMatrix& operator+(const SquareMatrix& other) const;

    /// @brief Operator mnożenia macierzy.
    /// @param other Druga macierz do pomnożenia.
    /// @return Nowa macierz będąca wynikiem operacji.
    SquareMatrix& operator*(const SquareMatrix& other) const;

    /// @brief Operator dodawania skalaru do macierzy.
    /// @param scalar Skalar do dodania.
    /// @return Nowa macierz będąca wynikiem operacji.
    SquareMatrix& operator+(int scalar) const;

    /// @brief Operator mnożenia macierzy przez skalar.
    /// @param scalar Skalar do pomnożenia.
    /// @return Nowa macierz będąca wynikiem operacji.
    SquareMatrix& operator*(int scalar) const;

    /// @brief Dodaje wartość skalarną do każdego elementu macierzy kwadratowej.
    /// 
    /// @param value Wartość skalarna do dodania.
    /// @return Referencja do zmodyfikowanej macierzy kwadratowej.
    SquareMatrix& operator+=(double value);

    /// @brief Wypisuje macierz kwadratową do podanego strumienia wyjściowego.
    /// 
    /// @param os Strumień wyjściowy.
    /// @param matrix Macierz kwadratowa do wypisania.
    /// @return Referencja do strumienia wyjściowego.
    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& matrix);

    /// @brief Porównuje dwie macierze kwadratowe pod kątem równości.
    /// 
    /// @param other Macierz kwadratowa do porównania.
    /// @return True, jeśli macierze są równe, w przeciwnym razie false.
    bool operator==(const SquareMatrix& other) const;

    /// @brief Porównuje, czy ta macierz kwadratowa jest większa od innej.
    /// 
    /// @param other Macierz kwadratowa do porównania.
    /// @return True, jeśli ta macierz jest większa, w przeciwnym razie false.
    bool operator>(const SquareMatrix& other) const;

    /// @brief Porównuje, czy ta macierz kwadratowa jest mniejsza od innej.
    /// 
    /// @param other Macierz kwadratowa do porównania.
    /// @return True, jeśli ta macierz jest mniejsza, w przeciwnym razie false.
    bool operator<(const SquareMatrix& other) const;

    /// @brief Porównuje dwie macierze kwadratowe pod kątem nierówności.
    /// 
    /// @param other Macierz kwadratowa do porównania.
    /// @return True, jeśli macierze nie są równe, w przeciwnym razie false.
    bool operator!=(const SquareMatrix& other) const;

    /// @brief Wyświetla pełną macierz kwadratową.
    void displayFull() const;

    /// @brief Wyświetla skróconą wersję macierzy kwadratowej.
    void displayTruncated() const;
};

#endif /* SQUARE_MATRIX_HPP */
