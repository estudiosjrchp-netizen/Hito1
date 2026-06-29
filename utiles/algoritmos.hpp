#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <vector>
#include <functional>

// Plantilla generica para el Merge
template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right, std::function<bool(T, T)> comparador) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comparador(L[i], R[j])) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Plantilla generica para el MergeSort
template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right, std::function<bool(T, T)> comparador) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comparador);
    mergeSort(arr, mid + 1, right, comparador);
    merge(arr, left, mid, right, comparador);
}

#endif // ALGORITMOS_HPP