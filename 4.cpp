#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода.
 * @return Введенное значение.
 */
double getValue();

/**
 * @brief Проверяет корректность шага.
 * @param step Значение шага.
 */
void checkStep(const double step);

/**
 * @brief Вычисляет значение функции y = 0.1 * x^2 - x * ln(x).
 * @param x Значение аргумента.
 * @return Значение функции y.
 */
double getY(const double x);

/**
 * @brief Проверяет, принадлежит ли x области определения функции.
 * @param x Значение аргумента.
 * @return true, если x > 0; иначе false.
 */
bool isDomain(const double x);

/**
 * @brief Точка входа в программу.
 * @return 0, если программа выполнена корректно.
 */
int main()
{
    cout << "Enter start value of x: ";
    double xstart = getValue();
    cout << "Enter end value of x: ";
    double xend = getValue();
    cout << "Enter step: ";
    double step = getValue();
    
    checkStep(step);

    for (double x = xstart; x <= xend + step / 2; x += step) // +step/2 для включения конечной точки
    {
        cout << "x = " << x;
        if (isDomain(x))
        {
            cout << " y = " << getY(x) << endl;
        }
        else
        {
            cout << " not in domain" << endl;
        }
    }

    return 0;
}

double getValue()
{
    double value;
    cin >> value;
    if (cin.fail())
    {
        cout << "Incorrect value" << endl;
        abort();
    }
    return value;
}

void checkStep(const double step)
{
    if (step <= 0)
    {
        cout << "Error: step must be positive" << endl;
        abort();
    }
}

double getY(const double x)
{
    return 0.1 * x * x - x * log(x);
}

bool isDomain(const double x)
{
    return x > 0;
}
