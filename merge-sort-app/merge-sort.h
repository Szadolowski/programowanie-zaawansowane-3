#pragma once

#include <vector>
#include <iostream>

/**
 * @brief Klasa implementująca algorytm sortowania przez scalanie (Merge Sort).
 * * Klasa wykorzystuje szablony, aby obsługiwać różne typy danych liczbowych.
 * * @tparam T Typ danych przechowywanych w tablicy (np. int, double, float).
 * Typ T musi obsługiwać operatory porównania (<, <=).
 */
template <typename T>
class MergeSorter {
public:
    /**
     * @brief Domyślny konstruktor.
     */
    MergeSorter() = default;

    /**
     * @brief Główna metoda uruchamiająca sortowanie.
     * * Metoda jest interfejsem publicznym. Sprawdza warunki brzegowe (pusta tablica)
     * i wywołuje rekurencyjną metodę sortującą.
     * * @param arr Referencja do wektora, który ma zostać posortowany.
     */
    void sort(std::vector<T>& arr) {
        if (arr.size() <= 1) {
            return; // Tablica pusta lub 1-elementowa jest już posortowana
        }
        // Rzutujemy size() na int, aby uniknąć problemów z typami unsigned w logice indeksów
        sortRecursive(arr, 0, static_cast<int>(arr.size()) - 1);
    }

private:
    /**
     * @brief Rekurencyjna metoda dzieląca tablicę na mniejsze fragmenty.
     * * @param arr Tablica do posortowania.
     * @param left Indeks lewego końca zakresu.
     * @param right Indeks prawego końca zakresu.
     */
    void sortRecursive(std::vector<T>& arr, int left, int right) {
        if (left >= right) {
            return; // Warunek stopu rekurencji
        }

        // Znajdź środek (chroni przed overflow przy dużych liczbach)
        int mid = left + (right - left) / 2;

        // Sortuj lewą połowę
        sortRecursive(arr, left, mid);
        // Sortuj prawą połowę
        sortRecursive(arr, mid + 1, right);

        // Scal obie posortowane połowy
        merge(arr, left, mid, right);
    }

    /**
     * @brief Metoda scalająca dwie posortowane podtablice w jedną.
     * * Scalane są zakresy [left..mid] oraz [mid+1..right].
     * * @param arr Główna tablica.
     * @param left Początek lewej podtablicy.
     * @param mid Koniec lewej podtablicy (środek).
     * @param right Koniec prawej podtablicy.
     */
    void merge(std::vector<T>& arr, int left, int mid, int right) {
        // Rozmiary tymczasowych tablic
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Utworzenie tymczasowych wektorów
        std::vector<T> leftArr(n1);
        std::vector<T> rightArr(n2);

        // Kopiowanie danych do tablic tymczasowych
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];

        // Scalanie tablic tymczasowych z powrotem do arr
        int i = 0; // Indeks początkowy pierwszej podtablicy
        int j = 0; // Indeks początkowy drugiej podtablicy
        int k = left; // Indeks początkowy scalonej podtablicy

        while (i < n1 && j < n2) {
            // Używamy <= aby zachować stabilność algorytmu (dla duplikatów)
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // Skopiuj pozostałe elementy z leftArr, jeśli są
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        // Skopiuj pozostałe elementy z rightArr, jeśli są
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
};