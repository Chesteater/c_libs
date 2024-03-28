#ifndef SRC_OUR_MATH_H_
#define SRC_OUR_MATH_H_

#include <stdio.h>
#include <stdlib.h>

#define OUR_EPSILON 1E20
#define OUR_D_EPS 1e-15
#define OUR_NAN (0.0 / 0.0L)
#define OUR_P_INF (1.0 / 0.0L)
#define OUR_N_INF (-1.0 / 0.0L)

#define OUR_NANF __builtin_nanf("0x7ff800000000000f")
#define OUR_PI 3.1415926535897932384626433832795
#define OUR_PI_2 OUR_PI / 2.0
#define OUR_IS_NAN(x) x != x

#define OUR_EPS 1.00e-16

//  вычисляет арксинус
long double our_asin(double x);

//  вычисляет арккосинус
long double our_acos(double x);

//  вычисляет арктангенс
long double our_atan(double x);

//  вычисляет абсолютное значение целого числа (модуль)
int our_abs(int x);

//  вычисляет абсолютное значение числа с плавающей точкой (модуль)
long double our_fabs(double x);

//  возвращает ближайшее целое число, не превышающее заданное значение
long double our_floor(double x);

//  остаток операции деления с плавающей точкой
long double our_fmod(double x, double y);

//  возвращает ближайшее целое число, не меньшее заданного значения
long double our_ceil(double x);

//  вычисляет косинус
long double our_cos(double x);

//  операция деления без остатка
long double our_fdiv(double x, double y);

//  возвращает значение e, возведенное в заданную степень
long double our_exp(double x);

//  вычисляет натуральный логарифм
long double our_log(double x);

//  возводит число в заданную степень
long double our_pow(double base, double exp);

//  вычисляет синус
long double our_sin(double x);

//  вычисляет квадратный корень
long double our_sqrt(double x);

//  вычисляет тангенс
long double our_tan(double x);

//  возводит число в заданную целую степень
long double our_npow(long double x, int n);

double ostatok(double x);

#endif  // SRC_OUR_MATH_H_
