/**
 * @file main.cpp
 * @brief Główny plik programu demonstracyjnego algorytmu Merge Sort.
 * * Plik zawiera implementację funkcji main, która realizuje wymagania projektowe:
 * utworzenie instancji tablic dla typów int oraz double i ich posortowanie.
 * @author Twoje Imię i Nazwisko
 * @date 2023
 */

#include <iostream>
#include <vector>
#include <iomanip> // Do ładnego formatowania double
#include "merge-sort.h" // Dzięki zmianom w tasks.json to wystarczy

/**
 * @brief Funkcja pomocnicza do wyświetlania zawartości wektora na standardowe wyjście.
 * * Jest to szablon funkcji, który iteruje po elementach wektora i wypisuje je
 * w jednej linii oddzielone spacjami.
 * * @tparam T Typ danych przechowywanych w wektorze. Typ T musi obsługiwać operator strumieniowy << (np. int, double).
 * @param vec Referencja do stałego wektora (const std::vector<T>&), którego zawartość ma zostać wyświetlona.
 */
template <typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Główna funkcja programu (Punkt wejścia).
 * * Funkcja realizuje scenariusz testowy wymagany w zadaniu:
 * 1. Inicjalizuje tablicę liczb całkowitych (int).
 * 2. Inicjalizuje tablicę liczb zmiennoprzecinkowych (double).
 * 3. Wykorzystuje klasę MergeSorter do posortowania obu tablic.
 * 4. Prezentuje wyniki "przed" i "po" na konsoli.
 * * @return int Zwraca 0, sygnalizując poprawne zakończenie programu.
 */
int main() {
    std::cout << "=== TESTOWANIE MERGE SORT ===\n\n";

    // --- PRZYPADEK 1: Liczby całkowite (INT) ---
    std::cout << "1. Test dla int:\n";
    
    // Tworzymy instancję klasy dla typu int
    MergeSorter<int> intSorter;
    
    // Tworzymy tablicę (wektor)
    std::vector<int> intTablica = { 38, 27, 43, 3, 9, 82, 10 };
    
    std::cout << "Przed: ";
    printVector(intTablica);

    // Sortujemy
    intSorter.sort(intTablica);

    std::cout << "Po:    ";
    printVector(intTablica);
    std::cout << "\n-----------------------------\n";


    // --- PRZYPADEK 2: Liczby zmiennoprzecinkowe (DOUBLE) ---
    std::cout << "2. Test dla double:\n";
    
    // Tworzymy instancję klasy dla typu double
    MergeSorter<double> doubleSorter;
    
    // Tworzymy tablicę z liczbami ujemnymi i ułamkami
    std::vector<double> doubleTablica = { 2.5, -1.1, 3.14, 0.0, -5.5, 2.5 };

    std::cout << "Przed: ";
    printVector(doubleTablica);

    // Sortujemy
    doubleSorter.sort(doubleTablica);

    std::cout << "Po:    ";
    printVector(doubleTablica);
    std::cout << "\n";

    return 0;
}