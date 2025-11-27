#include <gtest/gtest.h>
#include <vector>
#include <algorithm> // Do std::sort (jako wzorzec do weryfikacji)
#include <random>    // Do generowania losowych liczb
#include "../merge-sort-app/merge-sort.h" // Dołączamy Twoją klasę

// --- Klasa Testowa (opcjonalna, ale dobra praktyka) ---
// W tym przypadku użyjemy prostych makr TEST, bo klasa MergeSorter jest bezstanowa.

// 1. Zachowuje tablicę niezmienioną, gdy ona jest już posortowana rosnąco
TEST(MergeSortTest, AlreadySorted) {
    std::vector<int> input = { 1, 2, 3, 4, 5 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 2. Potrafi posortować tablicę, która jest posortowana w odwrotnej kolejności
TEST(MergeSortTest, ReverseSorted) {
    std::vector<int> input = { 5, 4, 3, 2, 1 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 3. Poprawnie sortuje losową tablicę liczb
TEST(MergeSortTest, RandomArray) {
    std::vector<int> input = { 12, 7, 14, 9, 10, 11 };
    // Tworzymy kopię i sortujemy ją "wzorcowym" algorytmem z biblioteki standardowej
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 4. Poprawnie sortuje tablice tylko z liczbami ujemnymi
TEST(MergeSortTest, OnlyNegativeNumbers) {
    std::vector<int> input = { -5, -1, -10, -3 };
    std::vector<int> expected = { -10, -5, -3, -1 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 5. Poprawnie sortuje tablice z liczbami ujemnymi i liczbami dodatnimi
TEST(MergeSortTest, MixedNegativeAndPositive) {
    std::vector<int> input = { -2, 5, 0, -10, 3 };
    std::vector<int> expected = { -10, -2, 0, 3, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 6. Obsługuje pustą tablicę bez rzucania wyjątkiem
TEST(MergeSortTest, EmptyArray) {
    std::vector<int> input = {};
    std::vector<int> expected = {};

    MergeSorter<int> sorter;
    // To nie powinno wyrzucić błędu (segfault)
    EXPECT_NO_THROW(sorter.sort(input)); 
    EXPECT_EQ(input, expected);
}

// 7. Nie zmienia tablicy, która zawiera tylko jeden element
TEST(MergeSortTest, SingleElement) {
    std::vector<int> input = { 42 };
    std::vector<int> expected = { 42 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 8. Poprawnie sortuje tablicę z duplikatami liczb
TEST(MergeSortTest, Duplicates) {
    std::vector<int> input = { 5, 1, 5, 2, 1 };
    std::vector<int> expected = { 1, 1, 2, 5, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 9. Poprawnie sortuje tablice ujemną z duplikatami
TEST(MergeSortTest, NegativeDuplicates) {
    std::vector<int> input = { -1, -5, -1, -5 };
    std::vector<int> expected = { -5, -5, -1, -1 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 10. Poprawnie sortuje tablice z liczbami ujemnymi, dodatnimi oraz duplikatami
TEST(MergeSortTest, MixedWithDuplicates) {
    std::vector<int> input = { -2, 2, 0, -2, 5, 5 };
    std::vector<int> expected = { -2, -2, 0, 2, 5, 5 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 11. Poprawnie sortuje tablicę zawierającą tylko dwa elementy w kolejności rosnącej
TEST(MergeSortTest, TwoElementsSorted) {
    std::vector<int> input = { 1, 2 };
    std::vector<int> expected = { 1, 2 };

    MergeSorter<int> sorter;
    sorter.sort(input);

    EXPECT_EQ(input, expected);
}

// 12. Poprawnie sortuje dużą tablicę zawierającą ponad 100 elementów
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

// 13. Poprawnie sortuje dużą tablicę (>100) z liczbami ujemnymi, dodatnimi oraz duplikatami
TEST(MergeSortTest, LargeArrayMixedComplex) {
    std::vector<int> input;
    // Generujemy 200 losowych liczb z zakresu -50 do 50
    // Używamy silnika losowego C++11 dla lepszej jakości (choć rand() też by zadziałał)
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

// --- Main dla Google Test ---
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << RUN_ALL_TESTS();
    std::cin.get();
    return 0;
}