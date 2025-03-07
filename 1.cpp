#include <iostream>
#include <cmath>
using namespace std;

/**
 *@brief - Функция для вычисления A по заданному уравнению 
 *@param x - значение переменной x
 *@param y - значение переменной y
 *@param z - значение переменной z
 *@return - возвращает рассчитанное значение
 */
double getA(const double x, const double y, const double z);

/**
 *@brief - Функция для вычисления B по заданному уравнению 
 *@param x - значение переменной x
 *@param y - значение переменной y
 *@param z - значение переменной z
 *@return - возвращает рассчитанное значение
 */
double getB(const double x, const double y, const double z);
/**
 *@brief - Точка входа в программу 
 *@return - возвращает 0, если программа выполнена корректно
 */
int main()
{
    const double x = 0.2;
    const double y = 0.004;
    const double z = 1.1;
    cout<<"A = "<<getA(x,y,z)<<endl;
    cout<<"B = "<<getB(x,y,z);
    return 0;
}

double getA(const double x, const double y, const double z) 
{
    return pow(sin(pow(x,2)/z),3)-sqrt(x/y);

}

double getB(const double x, const double y, const double z) 
{
    return (pow(x,2)/z)+pow(cos(x+y), 3);
}
