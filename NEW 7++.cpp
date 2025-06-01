#include <iostream>
#include <cstdlib>   // Для rand(), srand()
#include <ctime>     // Для time()
#include <cmath>     // Для abs()

using namespace std;

int** createArray(int& n, int& m);
void fillArray(int** arr, int n, int m, bool random);
void printArray(int** arr, int n, int m);
void replaceColumnMinsWithZero(int** arr, int n, int m);
int findMaxAbsElement(int** arr, int n, int m);
void insertAfterRowsWithMax(int**& arr, int& n, int m, int maxAbsVal);

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int n, m;
    cout << "Введите количество строк: ";
    cin >> n;
    cout << "Введите количество столбцов: ";
    cin >> m;

    if (n <= 0 || m <= 0) {
        cout << "Размеры массива должны быть положительными." << endl;
        return 1;
    }

    int** arr = createArray(n, m);

    int choice;
    cout << "1 - ввод вручную, 2 - заполнение случайными числами: ";
    cin >> choice;
    fillArray(arr, n, m, choice == 2);

    cout << "\nИсходный массив:\n";
    printArray(arr, n, m);

    replaceColumnMinsWithZero(arr, n, m);
    cout << "\nПосле замены минимумов в столбцах на 0:\n";
    printArray(arr, n, m);

    int maxAbs = findMaxAbsElement(arr, n, m);
    insertAfterRowsWithMax(arr, n, m, maxAbs);
    cout << "\nПосле вставки последней строки после строк с макс. по модулю элементом:\n";
    printArray(arr, n, m);

    // Освобождение памяти
    for (int i = 0; i < n; ++i)
        delete[] arr[i];
    delete[] arr;

    return 0;
}

// Создание двумерного массива
int** createArray(int& n, int& m) {
    int** arr = new int*[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new int[m];
    return arr;
}

// Заполнение массива вручную или случайно
void fillArray(int** arr, int n, int m, bool random) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            arr[i][j] = random ? rand() % 41 - 20 : (cout << "[" << i << "][" << j << "]: ", cin >> arr[i][j], arr[i][j]);
}

// Печать массива
void printArray(int** arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << arr[i][j] << "\t";
        cout << endl;
    }
}

// Замена минимального элемента в каждом столбце нулём
void replaceColumnMinsWithZero(int** arr, int n, int m) {
    for (int j = 0; j < m; ++j) {
        int minVal = arr[0][j];
        int minIdx = 0;
        for (int i = 1; i < n; ++i) {
            if (arr[i][j] < minVal) {
                minVal = arr[i][j];
                minIdx = i;
            }
        }
        arr[minIdx][j] = 0;
    }
}

// Поиск максимального по модулю элемента
int findMaxAbsElement(int** arr, int n, int m) {
    int maxVal = abs(arr[0][0]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (abs(arr[i][j]) > maxVal)
                maxVal = abs(arr[i][j]);
    return maxVal;
}

// Вставка последней строки после каждой строки с макс. по модулю элементом
void insertAfterRowsWithMax(int**& arr, int& n, int m, int maxAbsVal) {
    int** newArr = new int*[n * 2]; // Потенциально максимум n вставок
    int newRowCount = 0;

    for (int i = 0; i < n; ++i) {
        // Копируем текущую строку
        newArr[newRowCount] = new int[m];
        for (int j = 0; j < m; ++j)
            newArr[newRowCount][j] = arr[i][j];
        ++newRowCount;

        // Проверка: содержит ли строка элемент с модулем равным maxAbsVal
        for (int j = 0; j < m; ++j) {
            if (abs(arr[i][j]) == maxAbsVal) {
                newArr[newRowCount] = new int[m];
                for (int k = 0; k < m; ++k)
                    newArr[newRowCount][k] = arr[n - 1][k]; // последняя строка
                ++newRowCount;
                break; // Вставляем только один раз
            }
        }
    }

    // Удаляем старый массив
    for (int i = 0; i < n; ++i)
        delete[] arr[i];
    delete[] arr;

    arr = newArr;
    n = newRowCount; // Обновляем количество строк
}