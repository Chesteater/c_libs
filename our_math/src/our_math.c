#define OUR_EPSILON 1E20
#define OUR_D_EPS 1e-20
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

long double our_exp(double x) {
  long double ex = 1;
  if (x == x && x != OUR_P_INF && x != OUR_N_INF) {
    long double el = 1, n = 1;
    while (our_fabs(el) > OUR_D_EPS && our_fabs(el) < OUR_EPSILON) {
      el = el * (our_fabs(x) / n);
      ex = ex + el;
      n++;
    }
    if (x < 0) {
      ex = 1 / ex;
    }
  } else {
    x != x ? ex = OUR_NAN : 0;
    x == OUR_P_INF ? ex = OUR_P_INF : 0;
    x == OUR_N_INF ? ex = 0 : 1;
  }
  return ex;
}

long double our_pow(double base, double exp) {
  long double res;
  if (exp == 0 || base == 1) {
    res = 1;
  } else {
    if (base == 0) {
      res = 0;
    } else if (base != base) {
      res = OUR_NAN;
    } else if (exp == OUR_N_INF) {
      res = 0;
    } else if (exp == OUR_P_INF) {
      res = OUR_P_INF;
    } else if (ostatok(exp) != 0 && base < 0) {
      res = OUR_NAN;
    } else {
      res = our_exp((exp - our_floor(exp)) * our_log(our_fabs(base))) *
            our_npow(our_fabs(base), our_floor(exp));
      if (base < 0) {
        if (our_fmod(our_fabs(exp), 2) == 1) {
          res = res * (-1);
        }
      }
    }
  }
  return res;
}

long double our_log(double x) {
  long double s, p = 1, nx;
  if (x != x || x < 0.0) {
    s = OUR_NAN;
  } else if (x == OUR_P_INF) {
    s = OUR_P_INF;
  } else if (!x) {
    s = OUR_N_INF;
  } else {
    nx = ((x - 1) / (x + 1));
    s = 2 * nx;
    long double el = nx;
    while (our_fabs(el * (2 / p)) > OUR_D_EPS &&
           our_fabs(el * 2 / p) < OUR_EPSILON) {
      p = p + 2;
      el = el * nx * nx;
      s = s + el * 2 / p;
    }
  }
  return s;
}

long double our_sqrt(double x) {
  double res;
  if (x == OUR_P_INF) {
    res = OUR_P_INF;
  } else {
    if (x == OUR_N_INF) {
      res = OUR_NAN;
    } else {
      res = our_pow(x, 0.5);
    }
  }
  return res;
}

long double our_npow(long double x, int n) {
  long double res = 1;
  for (int i = 1; i <= our_abs(n); i++) {
    res = res * x;
  }
  if (n < 0) {
    res = 1 / res;
  }
  return res;
}

long double our_fdiv(double x, double y) { return (x - our_fmod(x, y)) / y; }

double ostatok(double x) {
  int a = x;
  double b = x - a;
  return b;
}

int our_abs(int x) {
  int a;
  if (x < 0) {
    a = x * (-1);
  } else {
    a = x;
  }
  return a;
}

long double our_fabs(double x) {
  long double a;
  if (x < 0) {
    a = x * (-1);
  } else {
    a = x;
  }
  return a;
}

long double our_floor(double x) {
  long double a;
  if (x == OUR_P_INF) {
    a = OUR_P_INF;
  } else if (x != x) {
    a = OUR_NAN;
  } else if (x == OUR_N_INF) {
    a = OUR_N_INF;
  } else {
    if (x < 0) {
      if (ostatok(x) != 0) {
        a = our_abs(x) * (-1) - 1;
      } else {
        a = our_abs(x) * (-1);
      }
    } else {
      a = our_abs(x);
    }
  }
  return a;
}

long double our_ceil(double x) {
  long double a;
  if (x == OUR_P_INF) {
    a = OUR_P_INF;
  } else if (x == OUR_N_INF) {
    a = OUR_N_INF;
  } else if (x != x) {
    a = OUR_NAN;
  } else if (x < 0) {
    a = our_abs(x) * (-1);
  } else if (ostatok(x) != 0) {
    a = our_abs(x) + 1;
  } else {
    a = x;
  }
  return a;
}

long double our_fmod(double x, double y) {
  long double b;
  double a = our_fabs(x / y);
  if (y == 0) b = OUR_NAN;
  if (x == OUR_P_INF && y == OUR_N_INF) b = OUR_NAN;
  if (x == OUR_N_INF && y == OUR_P_INF) b = OUR_NAN;
  if (a == OUR_P_INF) b = OUR_NAN;
  if (a == OUR_NAN) b = OUR_NAN;
  if (x < 0) {
    b = x + our_floor(a) * our_fabs(y);
  } else {
    b = x - our_floor(a) * our_fabs(y);
  }
  if (our_fabs(x) == our_fabs(y)) b = 0;
  if (our_fabs(x) < our_fabs(y)) b = x;
  return b;
}

long double our_asin(double x) {
  long double res = 0;
  if (OUR_IS_NAN(x)) {
    res = x;
  } else {
    int sign = x <= 0 ? 1 : 0;  // запоминаем был ли знак, если х меньше 0, то
                                // сигн = 1, иначе сигн = 0
    x = our_fabs(x);  // модуль (заменить)
    if (x > 1) {
      res = OUR_NANF;
    } else if (x <= 0.5) {
      double tmp = x;  // временная переменная
      long long int n = 1;
      res = x;
      while (our_fabs(tmp) > OUR_EPS) {
        tmp = (tmp * ((2 * n * (2 * n - 1)) * x * x) / (4 * n * n));
        res += tmp / (2 * n + 1);
        n++;
      }
    } else {
      res =
          OUR_PI_2 -
          (2 * our_asin(our_sqrt((1 - x) / 2)));  // квадратный корень заменить
    }
    res *= sign ? -1 : 1;  // если сигн есть то рес умножаем на -1, если не
                           // было то умножаем на 1
  }
  return res;
}

long double our_acos(double x) {
  return x <= 1 && x >= -1 ? OUR_PI_2 - our_asin(x) : OUR_NANF;
}

long double our_atan(double x) {
  long double res = 0, el;
  if (OUR_IS_NAN(x)) {
    res = x;
  } else {
    int sign = x <= 0 ? 1 : 0;  // запоминаем был ли знак, если х меньше 0, то
                                // сигн = 1, иначе сигн = 0
    x = our_fabs(x);  // модуль (заменить)
    el = x;
    if (x < 0.98) {
      for (int n = 0; n < 5000; n++) {
        res += el / (2 * n + 1);
        el = el * x * (-x);
      }
    } else if (x >= 0.98 && x <= 1) {
      res = x / our_sqrt(our_pow(x, 2) + 1);  // пов,скрт заменить
      res = our_asin(res);
    } else {
      res = OUR_PI_2 - our_atan(1 / x);
    }
    res *= sign ? -1 : 1;  // если сигн есть то рес умножаем на -1, если не
                           // было то умножаем на 1
  }
  return res;
}

long double our_sin(double x) {
  long double sin = 0, el;
  if (x != x) {
    sin = OUR_NAN;
  } else if (x == OUR_P_INF) {
    sin = OUR_NAN;
  } else if (x == OUR_N_INF) {
    sin = OUR_NAN;
  } else {
    double t = our_fmod(x, 2 * OUR_PI);
    el = t;
    sin = el;
    for (int i = 1; i < 200; i++) {
      el *= t * (-t) / (((2 * i + 1) * 2 * i));
      sin += el;
    }
  }
  return sin;
}

long double our_cos(double x) {
  long double cos = 0, el = 1;
  if (x != x) {
    cos = OUR_NAN;
  } else if (x == OUR_P_INF) {
    cos = OUR_NAN;
  } else if (x == OUR_N_INF) {
    cos = OUR_NAN;
  } else {
    double t = our_fmod(x, 2 * OUR_PI);
    cos += el;
    for (int k = 1; k < 200; k++) {
      el *= (t * (-t)) / ((2 * k - 1) * 2 * k);
      cos += el;
    }
  }
  return cos;
}

long double our_tan(double x) {
  long double res = our_sin(x) / our_cos(x);
  if (our_fdiv(res, 1e-16) == 0) {
    res = our_fdiv(res, 1e-16);
  }
  return res;
}
