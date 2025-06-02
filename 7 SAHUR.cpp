#include <iostream>
#include <cstdlib>   // Для rand(), srand()
#include <ctime>     // Для time()
#include <cmath>     // Для abs()
#include <limits>    // Для numeric_limits

using namespace std;

enum FillMode {
    Manual = 1,
    Random = 2
};

// ==== Функции ====

int getValidatedInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите положительное целое число.\n";
        } else {
            return value;
        }
    }
}

int** createArray(int n, int m) {
    int** arr = new int*[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new int[m];
    return arr;
}

void fillArray(int** arr, int n, int m, bool random) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            arr[i][j] = random ? rand() % 100 - 50 : getValidatedInput("arr[" + to_string(i) + "][" + to_string(j) + "]: ");
}

void printArray(int** arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << arr[i][j] << ' ';
        cout << endl;
    }
}

int** copyArray(int** arr, int n, int m) {
    int** newArr = createArray(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            newArr[i][j] = arr[i][j];
    return newArr;
}

void replaceColumnMinsWithZero(int** arr, int n, int m) {
    for (int j = 0; j < m; ++j) {
        int minVal = arr[0][j];
        for (int i = 1; i < n; ++i)
            if (arr[i][j] < minVal)
                minVal = arr[i][j];

        for (int i = 0; i < n; ++i)
            if (arr[i][j] == minVal)
                arr[i][j] = 0;
    }
}

int findMaxAbsElement(int** arr, int n, int m) {
    int maxAbs = abs(arr[0][0]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (abs(arr[i][j]) > maxAbs)
                maxAbs = abs(arr[i][j]);
    return maxAbs;
}

void insertAfterRowsWithMax(int**& arr, int& n, int m, int maxAbsVal) {
    int** newArr = new int*[n * 2]; // запас по максимуму
    int newRowIdx = 0;

    for (int i = 0; i < n; ++i) {
        newArr[newRowIdx] = new int[m];
        for (int j = 0; j < m; ++j)
            newArr[newRowIdx][j] = arr[i][j];
        newRowIdx++;

        for (int j = 0; j < m; ++j) {
            if (abs(arr[i][j]) == maxAbsVal) {
                newArr[newRowIdx] = new int[m];
                for (int k = 0; k < m; ++k)
                    newArr[newRowIdx][k] = arr[n - 1][k];  // вставка последней строки
                newRowIdx++;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i)
        delete[] arr[i];
    delete[] arr;

    arr = newArr;
    n = newRowIdx;
}

// ==== Главная функция ====

int main() {
    srand(time(0));

    int n = getValidatedInput("Введите количество строк: ");
    int m = getValidatedInput("Введите количество столбцов: ");

    int** arr = createArray(n, m);

    int choiceInput = getValidatedInput("1 - ввод вручную, 2 - заполнение случайными числами: ");
    FillMode choice = static_cast<FillMode>(choiceInput);
    fillArray(arr, n, m, choice == Random);

    cout << "\nИсходный массив:\n";
    printArray(arr, n, m);

    int** arrCopy = copyArray(arr, n, m);
    replaceColumnMinsWithZero(arrCopy, n, m);
    cout << "\nПосле замены минимумов в столбцах на 0:\n";
    printArray(arrCopy, n, m);

    int maxAbs = findMaxAbsElement(arr, n, m);
    insertAfterRowsWithMax(arr, n, m, maxAbs);
    cout << "\nПосле вставки последней строки после строк с макс. по модулю элементом:\n";
    printArray(arr, n, m);

    for (int i = 0; i < n; ++i)
        delete[] arr[i];
    delete[] arr;

    for (int i = 0; i < n; ++i)
        delete[] arrCopy[i];
    delete[] arrCopy;

    return 0;
}