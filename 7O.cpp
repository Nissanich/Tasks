#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

/**
 * @brief оператор выбора способа заполнения массива
 * @param Manual = 1 ручное заполнение
 * @param Random = 2 автоматическое заполнение
 */
enum FillMode
{
    Manual = 1,
    Random = 2
};

/**
 * @brief считывает значение типа int
 * @return считанное значение целочисленное
 */
int getValue();

/**
 * @brief проверяет размер массива
 * @param n - размер массива
 */
void checkSizeArr(const int n);

/**
 * @brief проверяет диапазон
 * @param min - минимальное значение диапазона значений элементов массива
 * @param max - максимальное значение диапазона значений элементов массива
 */
void checkRange(const int min, const int max);

/**
 * @brief создаёт новый двумерный массив.
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 * @return - новый массив
 */
int** createArray(int const n, int const m);

/**
 * @brief заполнение массива вручную
 * @param arr - массив
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 * @param min - минимальное значение диапазона
 * @param max - максимальное значение диапазона
 */
void fillArray(int** arr, int const n, int const m, int const min, int const max);

/**
 * @brief заполняет массив случайными числами
 * @param arr - массив
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 * @param min - минимальное значение диапазона
 * @param max - максимальное значение диапазона
 */
void fillArrayRandom(int** arr, int const n, int const m, int const min, int const max);

/**
 * @brief очищает массив
 * @param arr - массив
 * @param n - кол-во строк массива
 */
void delArray(int** arr, const int n);

/**
 * @brief выводит массив на экран
 * @param arr - массив
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 */
void printArray(int** arr, int const n, int const m);

/**
 * @brief копирует исходный массив и возвращает копию
 * @param arr - массив
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 * @return - новый массив
 */
int** copyArray(int** arr, const int n, const int m);

/**
 * @brief заменяет минимум в столбце на 0
 * @param arr - массив
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 */
void replaceColumnMinsWithZero(int** arr, int const n, int const m);

/**
 * @brief вставляет последнюю строку после строк с макс. по модулю элементом
 * @param arr - массив
 * @param n - кол-во строк массива
 * @param m - кол-во столбцов массива
 */
void insertNewArrAfterRowsWithMax(int** arr, const int n, const int m);

/**
* @brief точка входа в программу
* @return 0 - если программа выполнена корректно, иначе - 1
*/
int main() {
    setlocale(LC_ALL, "rus");

    cout << "Введите количество строк: ";
    int n = getValue();
    checkSizeArr(n);
    cout << "Введите количество столбцов: ";
    int m = getValue();
    checkSizeArr(m);

    int** arr = createArray(n, m);

    cout << "Введите минимальное и максимальное значение диапазона: ";
    int minValue = getValue();
    int maxValue = getValue();
    checkRange(minValue, maxValue);

    cout << "Введите выбор для заполнения двумерного массива: " << endl
        << Manual << " Для ручного заполнения" << endl
        << Random << " Для случайного заполнения" << endl;

    int choice = getValue();
    switch ((enum FillMode)choice) {
        case Manual:
            fillArray(arr, n, m, minValue, maxValue);
            break;
        case Random:
            fillArrayRandom(arr, n, m, minValue, maxValue);
            break;
        default:
            cout << "Неверный выбор!" << endl;
            delArray(arr, n);
            return 0;
    }

    cout << "Исходный массив:" << endl;
    printArray(arr, n, m);

    cout << "Новый массив после замены минимумов в столбцах на 0:" << endl;
    int** arrCopy = copyArray(arr, n, m);
    replaceColumnMinsWithZero(arrCopy, n, m);
    printArray(arrCopy, n, m);

    cout << "Новый массив после вставки последней строки после строк с макс. по модулю элементом:" << endl;
    insertNewArrAfterRowsWithMax(arr, n, m);

    delArray(arrCopy, n);
    delArray(arr, n);

    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Неправильный ввод данных";
        abort();
    }
    return value;
}

void checkSizeArr(const int n)
{
    if (n <= 0)
    {
        cout << "Неправильный размер массива" << endl;
        abort();
    }
}

void checkRange(const int min, const int max)
{
    if (min > max)
    {
        cout << "Введен неправильный диапазон" << endl;
        abort();
    }
}

int** createArray(int const n, int const m)
{
    int** arr = new int*[n];
    for (size_t i = 0; i < n; ++i)
        arr[i] = new int[m];
    return arr;
}

void fillArray(int** arr, int const n, int const m, int const min, int const max)
{
    cout << "Введите элементы массива (диапазон [" << min << ".." << max << "]):" << endl;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cout << "arr[" << i << "][" << j << "]: ";
            int value = getValue();

            if (value >= min && value <= max) {
                arr[i][j] = value;
            } else {
                cout << "Ошибка: значение должно быть между " << min << " и " << max << endl;
                abort();
            }
        }
    }
}

void fillArrayRandom(int** arr, int const n, int const m, int const min, int const max)
{
    srand((time(0)));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            arr[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void delArray(int** arr, int const n)
{
    for (size_t i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

void printArray(int** arr, const int n, const int m)
{
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cout << setw(5) << arr[i][j];
        }
        cout << '\n';
    }
    cout << endl;
}

int** copyArray(int** arr, int const n, int const m) {
    int** newArr = new int*[n];
    for (size_t i = 0; i < n; ++i) {
        newArr[i] = new int[m];
        copy(arr[i], arr[i] + m, newArr[i]);
    }
    return newArr;
}

void replaceColumnMinsWithZero(int** arr, int const n, int const m) {
    for (size_t j = 0; j < m; ++j) {
        int minVal = arr[0][j];
        for (size_t i = 1; i < n; ++i)
            if (arr[i][j] < minVal)
                minVal = arr[i][j];

        for (size_t i = 0; i < n; ++i)
            if (arr[i][j] == minVal)
                arr[i][j] = 0;
    }
}

void insertNewArrAfterRowsWithMax(int** arr, int const n, int const m) {
    int maxAbs = abs(arr[0][0]);
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < m; ++j) {
        if (abs(arr[i][j]) > maxAbs) {
          maxAbs = abs(arr[i][j]);
        }
      }
    }

    int rowsToInsert = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (abs(arr[i][j]) == maxAbs) {
                rowsToInsert++;
                break;  // одна строка может содержать несколько maxAbs, но вставляем только одну копию
            }
        }
    }

    int newRowCount = n + rowsToInsert;
    int** newArr = new int*[newRowCount];

    int newRowIdx = 0;
    for (size_t i = 0; i < n; ++i) {
        newArr[newRowIdx] = new int[m];
        for (size_t j = 0; j < m; ++j) {
            newArr[newRowIdx][j] = arr[i][j];
        }
        newRowIdx++;

        bool containsMax = false;
        for (size_t j = 0; j < m; ++j) {
            if (abs(arr[i][j]) == maxAbs) {
                containsMax = true;
                break;
            }
        }

        if (containsMax) {
            newArr[newRowIdx] = new int[m];
            for (size_t k = 0; k < m; ++k) {
                newArr[newRowIdx][k] = arr[n - 1][k];  // вставка последней строки
            }
            newRowIdx++;
        }
    }

    printArray(newArr, newRowCount, m);
    delArray(newArr, newRowCount);
}
