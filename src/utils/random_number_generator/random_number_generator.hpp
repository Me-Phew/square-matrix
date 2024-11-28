/**
 * @author Marcin Dudek
 * @author Mateusz Basiaga (basmateusz@wp.pl)
 * @brief
 * @date 2024-11-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

 /// @brief Klasa do generowania liczb losowych w określonym zakresie.
 /// 
 /// Klasa zawiera metody umożliwiające generowanie liczb pseudolosowych 
 /// w zadanym przedziale. Korzysta z mechanizmu inicjalizacji generatora za pomocą ziarna.
class RandomNumberGenerator {
private:
  static bool isSeeded; ///< Flaga wskazująca, czy generator został zainicjalizowany z ziarnem.

  /// @brief Konstruktor usunięty, ponieważ klasa zawiera wyłącznie statyczne metody.
  RandomNumberGenerator() = delete;

  /// @brief Usunięty konstruktor kopiujący.
  RandomNumberGenerator(const RandomNumberGenerator&) = delete;

  /// @brief Usunięty operator przypisania.
  RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;


  /// @brief Inicjalizuje generator liczb losowych.
  /// 
  /// Funkcja ustawia ziarno generatora liczb losowych na podstawie czasu systemowego.
  /// Jest wywoływana automatycznie, gdy generator nie został jeszcze zainicjalizowany.
  static void seed();

public:
  /// @brief Generuje liczbę losową z podanego zakresu.
  /// 
  /// Funkcja zwraca liczbę całkowitą losową z przedziału [min, max].
  /// Jeśli generator nie został wcześniej zainicjalizowany, funkcja wywołuje `seed()`.
  /// 
  /// @param min Dolna granica zakresu (włącznie).
  /// @param max Górna granica zakresu (włącznie).
  /// @return Liczba całkowita losowa z przedziału [min, max].
  static int getRandomNumber(int min, int max);
};

#endif /* RANDOM_NUMBER_GENERATOR_HPP */
