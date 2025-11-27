/**
 * @file test.cpp
 * @brief Plik zawierający testy jednostkowe dla klasy MergeSorter.
 * * Wykorzystuje framework Google Test do weryfikacji poprawności działania algorytmu
 * sortowania przez scalanie. Pokrywa przypadki brzegowe, typowe oraz złożone
 * (duże zbiory danych, liczby ujemne, duplikaty).
 * * @author Twoje Imię
 * @date 2023
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm> // Do std::sort (jako wzorzec do weryfikacji)
#include <random>    // Do generowania losowych liczb
#include "../merge-sort-app/merge-sort.h" // Dołączamy testowaną klasę

/**
 * @test **AlreadySorted**: 
 * Sprawdza, czy algorytm zachowuje tablicę niezmienioną, gdy jest ona już posortowana rosnąco.
 * Weryfikuje stabilność dla najprostszego przypadku pozytywnego.
 */
TEST(MergeSortTest, AlreadySorted) {
    std::vector<int> input = { 1, 2, 3, 4, 5 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **ReverseSorted**: 
 * Sprawdza, czy algorytm potrafi posortować tablicę ułożoną w odwrotnej kolejności (malejąco).
 * Jest to pesymistyczny przypadek dla niektórych algorytmów, choć dla MergeSort złożoność pozostaje O(n log n).
 */
TEST(MergeSortTest, ReverseSorted) {
    std::vector<int> input = { 5, 4, 3, 2, 1 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **RandomArray**: 
 * Weryfikuje sortowanie losowej permutacji liczb.
 * Wynik porównywany jest z wynikiem zaufanego algorytmu std::sort.
 */
TEST(MergeSortTest, RandomArray) {
    std::vector<int> input = { 12, 7, 14, 9, 10, 11 };
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **OnlyNegativeNumbers**: 
 * Sprawdza poprawność sortowania tablicy zawierającej wyłącznie liczby ujemne.
 * Weryfikuje obsługę arytmetyki liczb ze znakiem.
 */
TEST(MergeSortTest, OnlyNegativeNumbers) {
    std::vector<int> input = { -5, -1, -10, -3 };
    std::vector<int> expected = { -10, -5, -3, -1 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **MixedNegativeAndPositive**: 
 * Sprawdza sortowanie tablicy mieszanej (liczby dodatnie, ujemne i zero).
 * Testuje poprawne ustalanie kolejności między liczbami różnych znaków.
 */
TEST(MergeSortTest, MixedNegativeAndPositive) {
    std::vector<int> input = { -2, 5, 0, -10, 3 };
    std::vector<int> expected = { -10, -2, 0, 3, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **EmptyArray**: 
 * Sprawdza odporność algorytmu na pustą tablicę.
 * Oczekuje braku rzucenia wyjątku i pozostawienia tablicy pustej.
 */
TEST(MergeSortTest, EmptyArray) {
    std::vector<int> input = {};
    std::vector<int> expected = {};

    MergeSorter<int> sorter;
    // To nie powinno wyrzucić błędu (segfault)
    EXPECT_NO_THROW(sorter.sort(input)); 
    EXPECT_EQ(input, expected);
}

/**
 * @test **SingleElement**: 
 * Sprawdza przypadek brzegowy tablicy jednoelementowej.
 * Taka tablica jest z definicji posortowana i nie powinna ulec zmianie.
 */
TEST(MergeSortTest, SingleElement) {
    std::vector<int> input = { 42 };
    std::vector<int> expected = { 42 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **Duplicates**: 
 * Sprawdza poprawność sortowania tablicy zawierającej powtarzające się wartości.
 * Kluczowe dla weryfikacji stabilności i warunków w pętli scalającej (<=).
 */
TEST(MergeSortTest, Duplicates) {
    std::vector<int> input = { 5, 1, 5, 2, 1 };
    std::vector<int> expected = { 1, 1, 2, 5, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **NegativeDuplicates**: 
 * Weryfikuje obsługę duplikatów wśród liczb ujemnych.
 */
TEST(MergeSortTest, NegativeDuplicates) {
    std::vector<int> input = { -1, -5, -1, -5 };
    std::vector<int> expected = { -5, -5, -1, -1 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **MixedWithDuplicates**: 
 * Złożony test sprawdzający kombinację liczb ujemnych, dodatnich, zera oraz duplikatów.
 */
TEST(MergeSortTest, MixedWithDuplicates) {
    std::vector<int> input = { -2, 2, 0, -2, 5, 5 };
    std::vector<int> expected = { -2, -2, 0, 2, 5, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **TwoElementsSorted**: 
 * Przypadek brzegowy dla rekurencji - tablica dwuelementowa, która nie wymaga zmian.
 */
TEST(MergeSortTest, TwoElementsSorted) {
    std::vector<int> input = { 1, 2 };
    std::vector<int> expected = { 1, 2 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **LargeArray**: 
 * Test wydajnościowy/poprawnościowy dla większej tablicy (150 elementów).
 * Tablica generowana jest w kolejności malejącej, co wymusza pełną pracę algorytmu.
 */
TEST(MergeSortTest, LargeArray) {
    // Generowanie dużej tablicy (150 elementów)
    std::vector<int> input;
    for (int i = 150; i > 0; --i) {
        input.push_back(i);
    }
    
    // Wzorzec
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @test **LargeArrayMixedComplex**: 
 * Kompleksowy test (Stress Test) na losowych danych.
 * Generuje 200 liczb z zakresu [-50, 50], co gwarantuje wystąpienie duplikatów oraz mieszanki znaków.
 * Wynik weryfikowany względem std::sort.
 */
TEST(MergeSortTest, LargeArrayMixedComplex) {
    std::vector<int> input;
    // Generujemy 200 losowych liczb z zakresu -50 do 50
    std::mt19937 rng(12345); // Stałe ziarno dla powtarzalności testów
    std::uniform_int_distribution<int> dist(-50, 50);

    for(int i = 0; i < 200; i++) {
        input.push_back(dist(rng));
    }

    // Wzorzec (Oracle sort)
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

/**
 * @brief Punkt wejścia dla aplikacji testowej.
 * * Inicjalizuje framework Google Test i uruchamia wszystkie zdefiniowane testy.
 * @param argc Liczba argumentów wiersza poleceń.
 * @param argv Tablica argumentów wiersza poleceń.
 * @return int Kod wyjścia (0 jeśli wszystkie testy przeszły, 1 jeśli wystąpił błąd).
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}