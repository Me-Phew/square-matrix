/**
 * @author Marcin Dudek
 * @author Mateusz Basiaga (basmateusz@wp.pl)
 * @brief Klasa reprezentująca macierz kwadratową.
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
    int _size; ///< Rozmiar macierzy.
    int** _data; ///< Wskaźnik na dane macierzy.
    bool _isAllocated; ///< Flaga informująca, czy pamięć została przydzielona.

    /// @brief Przydziela pamięć dla macierzy.
    void allocateMemory();

    /// @brief Zwalnia pamięć zajmowaną przez macierz.
    void deallocateMemory();

    /// @brief Kopiuje dane z innej macierzy.
    /// 
    /// @param other Inna macierz, z której dane mają być skopiowane.
    void copyData(const SquareMatrix& other);

public:
    /// @brief Konstruktor domyślny, tworzy pustą macierz.
    SquareMatrix();

    /// @brief Konstruktor z parametrem rozmiaru macierzy.
    /// 
    /// @param size Rozmiar macierzy.
    explicit SquareMatrix(int size);

    /// @brief Konstruktor z parametrem danych wiersza.
    /// 
    /// @param size Rozmiar macierzy.
    /// @param rowData Dane wiersza do zainicjowania macierzy.
    SquareMatrix(int size, const int* rowData);

    /// @brief Konstruktor kopiujący.
    /// 
    /// @param other Inna macierz, która ma być skopiowana.
    SquareMatrix(SquareMatrix& other);

    /// @brief Destruktor, zwalnia pamięć.
    ~SquareMatrix();

    /// @brief Przydziela pamięć dla macierzy o podanym rozmiarze.
    /// 
    /// @param size Rozmiar macierzy.
    /// @return Referencja do obiektu macierzy.
    SquareMatrix& allocate(int size);

    /// @brief Wstawia wartość do elementu macierzy.
    /// 
    /// @param row Numer wiersza.
    /// @param col Numer kolumny.
    /// @param value Wartość do wstawienia.
    /// @return Referencja do obiektu macierzy.
    SquareMatrix& insert(int row, int col, int value);

    /// @brief Zwraca wartość z elementu macierzy.
    /// 
    /// @param row Numer wiersza.
    /// @param col Numer kolumny.
    /// @return Wartość elementu macierzy.
    int get(int row, int col);

    /// @brief Transponuje macierz.
    /// 
    /// @return Referencja do obiektu macierzy po transpozycji.
    SquareMatrix& transpose();

    /// @brief Losowo wypełnia macierz.
    /// 
    /// @return Referencja do obiektu macierzy po losowym wypełnieniu.
    SquareMatrix& randomize();

    /// @brief Losowo wypełnia macierz określoną liczbą losowych elementów.
    /// 
    /// @param count Liczba losowych elementów.
    /// @return Referencja do obiektu macierzy po losowym wypełnieniu.
    SquareMatrix& randomize(int count);

    /// @brief Wstawia dane na główną przekątną macierzy.
    /// 
    /// @param mainDiagonalData Dane do wstawienia na główną przekątną.
    /// @return Referencja do obiektu macierzy po wstawieniu danych.
    SquareMatrix& insertMainDiagonal(const int* mainDiagonalData);

    /// @brief Wstawia dane na przekątną o określonym przesunięciu.
    /// 
    /// @param offset Przesunięcie dla przekątnej.
    /// @param diagonalData Dane do wstawienia na przekątną.
    /// @return Referencja do obiektu macierzy po wstawieniu danych.
    SquareMatrix& insertDiagonal(int offset, const int* diagonalData);

    /// @brief Wstawia dane do kolumny.
    /// 
    /// @param col Numer kolumny.
    /// @param columnData Dane do wstawienia w kolumnie.
    /// @return Referencja do obiektu macierzy po wstawieniu danych.
    SquareMatrix& insertColumn(int col, const int* columnData);

    /// @brief Wstawia dane do wiersza.
    /// 
    /// @param row Numer wiersza.
    /// @param rowData Dane do wstawienia w wierszu.
    /// @return Referencja do obiektu macierzy po wstawieniu danych.
    SquareMatrix& insertRow(int row, const int* rowData);

    /// @brief Wypełnia macierz przekątną.
    /// 
    /// @return Referencja do obiektu macierzy po wypełnieniu przekątnej.
    SquareMatrix& fillDiagonal();

    /// @brief Wypełnia macierz poniżej przekątnej.
    /// 
    /// @return Referencja do obiektu macierzy po wypełnieniu poniżej przekątnej.
    SquareMatrix& fillUnderDiagonal();

    /// @brief Wypełnia macierz powyżej przekątnej.
    /// 
    /// @return Referencja do obiektu macierzy po wypełnieniu powyżej przekątnej.
    SquareMatrix& fillOverDiagonal();

    /// @brief Wypełnia macierz w stylu szachownicy.
    /// 
    /// @return Referencja do obiektu macierzy po wypełnieniu w stylu szachownicy.
    SquareMatrix& fillChessboardStyle();

    /// @brief Dodaje dwie macierze.
    /// 
    /// @param other Inna macierz do dodania.
    /// @return Nowa macierz po dodaniu.
    SquareMatrix& operator+(const SquareMatrix& other) const;

    /// @brief Mnoży dwie macierze.
    /// 
    /// @param other Inna macierz do pomnożenia.
    /// @return Nowa macierz po mnożeniu.
    SquareMatrix& operator*(const SquareMatrix& other) const;

    /// @brief Dodaje skalara do macierzy.
    /// 
    /// @param scalar Skalar do dodania.
    /// @return Nowa macierz po dodaniu skalara.
    SquareMatrix& operator+(int scalar) const;

    /// @brief Mnoży macierz przez skalar.
    /// 
    /// @param scalar Skalar do mnożenia.
    /// @return Nowa macierz po mnożeniu przez skalar.
    SquareMatrix& operator*(int scalar) const;

    /// @brief Odejmuje skalar od macierzy.
    /// 
    /// @param scalar Skalar do odjęcia.
    /// @return Nowa macierz po odjęciu skalara.
    SquareMatrix& operator-(int scalar) const;

    /// @brief Dodaje skalar do macierzy.
    /// 
    /// @param scalar Skalar do dodania.
    /// @param matrix Macierz do dodania skalara.
    /// @return Nowa macierz po dodaniu skalara.
    friend SquareMatrix operator+(int scalar, const SquareMatrix& matrix);

    /// @brief Mnoży macierz przez skalar.
    /// 
    /// @param scalar Skalar do mnożenia.
    /// @param matrix Macierz do mnożenia przez skalar.
    /// @return Nowa macierz po mnożeniu przez skalar.
    friend SquareMatrix operator*(int scalar, const SquareMatrix& matrix);

    /// @brief Odejmuje macierz od skalara.
    /// 
    /// @param scalar Skalar, od którego odejmujemy macierz.
    /// @param matrix Macierz do odjęcia.
    /// @return Nowa macierz po odjęciu macierzy od skalara.
    friend SquareMatrix operator-(int scalar, const SquareMatrix& matrix);

    /// @brief Zwiększa macierz o 1.
    /// 
    /// @return Referencja do obiektu macierzy po inkrementacji.
    SquareMatrix& operator++(int);

    /// @brief Zmniejsza macierz o 1.
    /// 
    /// @return Referencja do obiektu macierzy po dekrementacji.
    SquareMatrix& operator--(int);

    /// @brief Dodaje skalar do macierzy i zwraca wynik.
    /// 
    /// @param scalar Skalar do dodania.
    /// @return Referencja do obiektu macierzy po dodaniu skalara.
    SquareMatrix& operator+=(int scalar);

    /// @brief Odejmuje skalar od macierzy i zwraca wynik.
    /// 
    /// @param scalar Skalar do odjęcia.
    /// @return Referencja do obiektu macierzy po odjęciu skalara.
    SquareMatrix& operator-=(int scalar);

    /// @brief Mnoży macierz przez skalar i zwraca wynik.
    /// 
    /// @param scalar Skalar do mnożenia.
    /// @return Referencja do obiektu macierzy po mnożeniu przez skalar.
    SquareMatrix& operator*=(int scalar);

    /// @brief Dodaje skalar typu double do macierzy.
    /// 
    /// @param scalar Skalar typu double do dodania.
    /// @return Referencja do obiektu macierzy po dodaniu skalara.
    SquareMatrix& operator+=(double);

    /// @brief Wypisuje macierz na standardowe wyjście.
    /// 
    /// @param os Strumień wyjściowy.
    /// @param matrix Macierz do wypisania.
    /// @return Strumień wyjściowy.
    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& matrix);

    /// @brief Porównuje dwie macierze pod kątem równości.
    /// 
    /// @param other Inna macierz do porównania.
    /// @return Prawda, jeśli macierze są równe, fałsz w przeciwnym przypadku.
    bool operator==(const SquareMatrix& other) const;

    /// @brief Porównuje dwie macierze pod kątem większości.
    /// 
    /// @param other Inna macierz do porównania.
    /// @return Prawda, jeśli pierwsza macierz jest większa od drugiej.
    bool operator>(const SquareMatrix& other) const;

    /// @brief Porównuje dwie macierze pod kątem mniejszości.
    /// 
    /// @param other Inna macierz do porównania.
    /// @return Prawda, jeśli pierwsza macierz jest mniejsza od drugiej.
    bool operator<(const SquareMatrix& other) const;

    /// @brief Porównuje dwie macierze pod kątem nierówności.
    /// 
    /// @param other Inna macierz do porównania.
    /// @return Prawda, jeśli macierze są różne, fałsz w przeciwnym przypadku.
    bool operator!=(const SquareMatrix& other) const;

    /// @brief Wyświetla pełną macierz.
    void displayFull() const;

    /// @brief Wyświetla skróconą wersję macierzy.
    void displayTruncated() const;
};

#endif /* SQUARE_MATRIX_HPP */
