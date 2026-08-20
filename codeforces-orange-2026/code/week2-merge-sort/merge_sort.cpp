#include <bits/stdc++.h>
using namespace std;

// Слияние двух отсортированных массивов
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (int i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

// Сортировка слиянием (Merge Sort)
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Сортируем левую половину
        mergeSort(arr, left, mid);
        
        // Сортируем правую половину
        mergeSort(arr, mid + 1, right);
        
        // Слияние отсортированных половин
        merge(arr, left, mid, right);
    }
}

// Подсчёт инверсий с помощью merge sort
long long countInversions(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    long long inv_count = 0;
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);  // Все оставшиеся элементы слева образуют инверсии
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (int i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
    
    return inv_count;
}

// Подсчёт инверсий
long long mergeSortAndCountInversions(vector<int>& arr, int left, int right) {
    long long inv_count = 0;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        inv_count += mergeSortAndCountInversions(arr, left, mid);
        inv_count += mergeSortAndCountInversions(arr, mid + 1, right);
        inv_count += countInversions(arr, left, mid, right);
    }
    
    return inv_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример 1: Базовая сортировка слиянием
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Массив до сортировки: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";
    
    mergeSort(arr1, 0, arr1.size() - 1);
    
    cout << "Массив после сортировки слиянием: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";
    
    // Пример 2: Подсчёт инверсий
    vector<int> arr2 = {1, 20, 6, 4, 5};
    
    cout << "Массив: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";
    
    long long inversions = mergeSortAndCountInversions(arr2, 0, arr2.size() - 1);
    
    cout << "Количество инверсий: " << inversions << "\n";
    cout << "Массив после сортировки: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";
    
    return 0;
}
