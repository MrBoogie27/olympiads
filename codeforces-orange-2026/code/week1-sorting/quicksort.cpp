#include <bits/stdc++.h>
using namespace std;

// Быстрая сортировка (Quick Sort)
// Разбиение массива относительно опорного элемента
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Рекурсивная сортировка левой части
        quickSort(arr, low, pi - 1);
        
        // Рекурсивная сортировка правой части
        quickSort(arr, pi + 1, high);
    }
}

// Альтернативная реализация с выбором случайного опорного элемента
int randomPartition(vector<int>& arr, int low, int high) {
    // Выбираем случайный индекс
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);
    
    return partition(arr, low, high);
}

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

// Three-way partition (для массивов с повторениями)
void threeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt) {
    if (low >= high) {
        lt = low;
        gt = high;
        return;
    }
    
    int pivot = arr[high];
    int i = low;
    lt = low - 1;
    gt = high;
    
    while (i < gt) {
        if (arr[i] < pivot) {
            swap(arr[++lt], arr[i++]);
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[--gt]);
        } else {
            i++;
        }
    }
    swap(arr[i], arr[high]);
    gt = i;
    lt = i - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример 1: Базовая быстрая сортировка
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Массив до сортировки: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";
    
    quickSort(arr1, 0, arr1.size() - 1);
    
    cout << "Массив после Quick Sort: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";
    
    // Пример 2: Рандомизированная быстрая сортировка
    vector<int> arr2 = {3, 7, 1, 9, 2, 5, 8, 4, 6};
    
    cout << "Массив до сортировки: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";
    
    randomizedQuickSort(arr2, 0, arr2.size() - 1);
    
    cout << "Массив после Randomized Quick Sort: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n\n";
    
    // Пример 3: Массив с повторениями
    vector<int> arr3 = {1, 4, 2, 4, 2, 4, 1, 2, 4};
    
    cout << "Массив с повторениями: ";
    for (int x : arr3) cout << x << " ";
    cout << "\n";
    
    int lt, gt;
    threeWayPartition(arr3, 0, arr3.size() - 1, lt, gt);
    
    cout << "После three-way partition: ";
    for (int x : arr3) cout << x << " ";
    cout << "\n";
    cout << "Меньше опорного: [0, " << lt << "], равны: [" << lt+1 << ", " << gt << "], больше: [" << gt+1 << ", " << arr3.size()-1 << "]\n";
    
    return 0;
}
