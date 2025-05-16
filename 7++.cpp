#include <iostream>
using namespace std;

/**
 * @brief Считывает значиния с клавиатуры с проверкой ввода
 * @return возвращает значение, если оно правильное , иначе завершает программу
 */
double getValue();

/**
 * @brief Проверяет, что количество строк и столбцов являются положительными числами.
 * @param max_rows Максимальное количество строк.
 * @param max_cols Максимальное количество столбцов.
 * @return true, если оба значения положительные; false в противном случае.
 */
bool checkPositiveValues(const int max_rows, const int max_cols);

/**
 * @brief Заполняет двумерный массив случайными значениями.
 * @param array Указатель на двумерный массив.
 * @param rows Количество строк в массиве.
 * @param cols Количество столбцов в массиве.
 */
void fillArrayRandomly(int** array, const int rows, const int cols);

/**
 * @brief Заменяет минимальное значение в каждом столбце двумерного массива на ноль.
 * @param array Указатель на двумерный массив.
 * @param rows Количество строк в массиве.
 * @param cols Количество столбцов в массиве.
 */
void replaceMinWithZero(int** array, const int rows, const int cols);

/**
 * @brief Вставляет последнюю строку после каждой строк, содержащей максимальный по модулю элемент.
 * @param arr3 Указатель на двумерный массив новый.
 * @param array Указатель на двумерный массив шаблонный.
 * @param new_rows Количество строк в новом массиве.
 * @param rows Количество строк в массиве.
 * @param cols Количество столбцов в массиве.
 */
void insertLastRowAfterMaxAbsElement(int** arr3, int** array, const int new_rows, const int rows, const int cols);

/**
 * @brief Выводит двумерный массив на экран.
 * @param array Указатель на двумерный массив.
 * @param rows Количество строк в массиве.
 * @param cols Количество столбцов в массиве.
 */
void printArray(int** array, const int rows, const int cols);

/**
 * @brief Создает новый двумерный массив с заданным количеством строк и столбцов.
 * @param rows Количество строк в новом массиве.
 * @param columns Количество столбцов в новом массиве.
 * @return Указатель на новый двумерный массив типа int.
 */
int** getNewArray(const int rows, const int columns);

/**
 * @brief Создает копию существующего двумерного массива с заданным количеством строк и столбцов.
 * @param arr Указатель на существующий двумерный массив типа int, который нужно скопировать.
 * @param rows Количество строк в существующем массиве.
 * @param columns Количество столбцов в существующем массиве.
 * @return Указатель на новую копию двумерного массива типа int.
 */
int** copyArray(int** arr, const int rows, const int columns);

/**
 * @brief Освобождает память, выделенную под двумерный массив типа int.
 * @param arr Указатель на двумерный массив типа int, который нужно освободить.
 * @param rows Количество строк в двумерном массиве.
 */
void deleteArray(int** arr, const int rows);

/**
 * @brief Проверка, является ли первое число по модулю больше второго.
 * @param num1 Первое число.
 * @param num2 Второе число.
 * @return true, если первое число по модулю больше второго; false в противном случае.
 */
bool isFirstAbsoluteValueGreaterThanSecond(const int num1, const int num2);

/**
 * @brief Возвращает, сколько строк нужно добавить для нового массива из задания 2.
 * @param array Указатель на двумерный массив типа int.
 * @param rows Количество строк в массиве.
 * @param cols Количество столбцов в массиве.
 * @return Количество строк.
 */
int countRowsWithMaxAbsElement(int** array, const int rows, const int cols);

/**
 * @brief Возвращает максимальный элемент по модулю в двумерном массиве.
 * @param array Указатель на двумерный массив типа int.
 * @param rows Количество строк в массиве.
 * @param cols Количество столбцов в массиве.
 * @return Максимальный элемент по модулю.
 */
int getMaxAbsElementInMatrix(int** array, const int rows, const int cols);

/**
 * @brief Точка входа в программу.
 * @return 0.
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    cout << "Введите количество строк: ";
    int max_rows = getValue();

    cout << "Введите количество столбцов: ";
    int max_cols = getValue();

    if (!checkPositiveValues(max_rows, max_cols))
    {
        return 1;
    }

    int** array = getNewArray(max_rows, max_cols);
    fillArrayRandomly(array, max_rows, max_cols);

    cout << "Случайно заполненный массив:" << endl;
    printArray(array, max_rows, max_cols);

    int** secondArr = copyArray(array, max_rows, max_cols);
    replaceMinWithZero(secondArr, max_rows, max_cols);

    cout << "\nМассив после замены минимального элемента столбца на 0:" << endl;
    printArray(secondArr, max_rows, max_cols);

    deleteArray(secondArr, max_rows);

    cout << "\nВставка последней строки после каждой строки, содержащей максимальный по модулю элемент:" << endl;
    int new_rows = max_rows + countRowsWithMaxAbsElement(array, max_rows, max_cols);
    int** arr3 = getNewArray(new_rows, max_cols);
    insertLastRowAfterMaxAbsElement(arr3, array, new_rows, max_rows, max_cols);

    printArray(arr3, new_rows, max_cols);

    deleteArray(arr3, new_rows);
    deleteArray(array, max_rows);

    return 0;
}

void fillArrayRandomly(int** array, const int rows, const int cols)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            array[i][j] = rand() % (100 - -100 + 1) + -100;
        }
    }
}

void replaceMinWithZero(int** array, const int rows, const int cols)
{
    for (size_t j = 0; j < cols; ++j) {
        int min_value = array[0][j];
        int min_index = 0;
        for (size_t i = 1; i < rows; ++i) {
            if (array[i][j] < min_value) {
                min_value = array[i][j];
                min_index = i;
            }
        }
        array[min_index][j] = 0;
    }
}

bool isFirstAbsoluteValueGreaterThanSecond(const int num1, const int num2)
{
    return (abs(num1) > abs(num2));
}

void insertLastRowAfterMaxAbsElement(int** arr3, int** array, const int new_rows, const int rows, const int cols)
{
    int max_abs_element = getMaxAbsElementInMatrix(array, rows, cols);
    int last_row_index = rows - 1;

    for (size_t i = 0, new_i = 0; i < rows && new_i < new_rows; ++i) {
        bool is_max_abs_element_in_row = false;

        for (size_t j = 0; j < cols; ++j) {
            if (abs(array[i][j]) == max_abs_element) {
                is_max_abs_element_in_row = true;
                break;
            }
        }

        for (size_t j = 0; j < cols; ++j) {
            arr3[new_i][j] = array[i][j];
        }
        ++new_i;

        if (is_max_abs_element_in_row) {
            for (size_t j = 0; j < cols; ++j) {
                arr3[new_i][j] = array[last_row_index][j];
            }
            ++new_i;
        }
    }
}

void printArray(int** array, const int rows, const int cols)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

double getValue()
{
    double value;
    cin >> value;
    if (cin.fail()) {
        cout << "Некорректное значение" << endl;
        abort();
    }
    return value;
}

int** getNewArray(const int rows, const int columns)
{
    int** array = new int* [rows];
    for (size_t i = 0; i < rows; ++i) {
        array[i] = new int[columns];
    }
    return array;
}

int** copyArray(int** arr, const int rows, const int columns)
{
    int** resultArray = getNewArray(rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            resultArray[i][j] = arr[i][j];
        }
    }
    return resultArray;
}

void deleteArray(int** arr, const int rows)
{
    for (size_t i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

bool checkPositiveValues(const int max_rows, const int max_cols)
{
    if (max_rows > 0 && max_cols > 0) {
        return true; // Оба значения положительные
    }
    else {
        cout << "Ошибка: Количество строк и столбцов должно быть положительным числом." << endl;
        return false; // Хотя бы одно значение не положительное
    }
}

int countRowsWithMaxAbsElement(int** array, const int rows, const int cols)
{
    int rowsWithMaxElement = 0;
    int maxElement = getMaxAbsElementInMatrix(array, rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (abs(array[i][j]) == maxElement) {
                rowsWithMaxElement++;
                break;
            }
        }
    }

    return rowsWithMaxElement;
}

int getMaxAbsElementInMatrix(int** array, const int rows, const int cols)
{
    int maxAbsElement = abs(array[0][0]);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (abs(array[i][j]) > maxAbsElement) {
                maxAbsElement = abs(array[i][j]);
            }
        }
    }

    return maxAbsElement;
}