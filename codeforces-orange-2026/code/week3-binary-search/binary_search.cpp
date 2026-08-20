#include <bits/stdc++.h>
using namespace std;

// Двоичный поиск - базовая версия
int binary_search_basic(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Не найдено
}

// Поиск первого элемента >= target
int lower_bound_custom(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Поиск первого элемента > target
int upper_bound_custom(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Двоичный поиск по ответу - проверка возможности
// Пример: найти минимум x такой, что f(x) истинна
// f - монотонная функция (false -> true)
int binary_search_answer(int left, int right, function<bool(int)> check) {
    int answer = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (check(mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return answer;
}

// Пример: найти максимум x такой, что f(x) истинна
int binary_search_answer_max(int left, int right, function<bool(int)> check) {
    int answer = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (check(mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return answer;
}

// Двоичный поиск на real числах
double binary_search_real(double left, double right, function<bool(double)> check, int iterations = 100) {
    while (iterations--) {
        double mid = (left + right) / 2;
        
        if (check(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return (left + right) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Пример 1: базовый двоичный поиск
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    
    cout << "Массив: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    cout << "Поиск 7: " << binary_search_basic(arr, 7) << "\n";
    cout << "Поиск 10: " << binary_search_basic(arr, 10) << "\n\n";
    
    // Пример 2: lower_bound и upper_bound
    cout << "Lower bound для 7: " << lower_bound_custom(arr, 7) << "\n";
    cout << "Upper bound для 7: " << upper_bound_custom(arr, 7) << "\n";
    cout << "Lower bound для 6: " << lower_bound_custom(arr, 6) << "\n";
    cout << "Upper bound для 6: " << upper_bound_custom(arr, 6) << "\n\n";
    
    // Пример 3: двоичный поиск по ответу
    // Найти минимум x такой, что x*x >= 20
    auto check = [](int x) { return x * x >= 20; };
    
    int result = binary_search_answer(0, 10, check);
    cout << "Минимум x такой, что x^2 >= 20: " << result << "\n";
    cout << "Проверка: " << result << "^2 = " << result * result << "\n\n";
    
    // Пример 4: поиск на real числах
    // Найти sqrt(2) с точностью
    auto check_sqrt = [](double x) { return x * x >= 2.0; };
    
    double sqrt_result = binary_search_real(0, 2, check_sqrt);
    cout << "sqrt(2) ≈ " << fixed << setprecision(10) << sqrt_result << "\n";
    
    return 0;
}
