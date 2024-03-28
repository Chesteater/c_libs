#include "our_decimal.h"

// возвращaемые значения
// 0-FALSE
// 1-TRUE

// Меньше или равно
int our_is_less_or_equal(our_decimal dec_a, our_decimal dec_b) {
  return (our_is_less(dec_a, dec_b) || our_is_equal(dec_a, dec_b)) ? 1 : 0;
}

// Больше или равно
int our_is_greater_or_equal(our_decimal dec_a, our_decimal dec_b) {
  return (our_is_greater(dec_a, dec_b) || our_is_equal(dec_a, dec_b)) ? 1 : 0;
}

// Не равно

int our_is_not_equal(our_decimal dec_a, our_decimal dec_b) {
  return our_is_equal(dec_a, dec_b) ? 0 : 1;
}

// Больше
int our_is_greater(our_decimal dec_a, our_decimal dec_b) {
  int flag = 0;
  if (our_less_great_eq(dec_a, dec_b) == 1) flag = 1;
  return flag;
}

// Меньше

int our_is_less(our_decimal dec_a, our_decimal dec_b) {
  int flag = 0;
  if (our_less_great_eq(dec_a, dec_b) == -1) {
    flag = 1;
  }
  return flag;
}
// Равно

int our_is_equal(our_decimal dec_1, our_decimal dec_2) {
  int flag = 0;
  if (our_less_great_eq(dec_1, dec_2) == 0) flag = 1;
  return flag;
}

int CompInt(int flag, our_decimal dec_a, our_decimal dec_b) {
  for (int i = 2; i >= 0 && !flag;
       i--) {  // сравниваем в цикле по модулю т.к. скейл одинаковый
    int signa = dec_a.bits[i] < 0 ? 1 : 0;
    int signb = dec_b.bits[i] < 0 ? 1 : 0;
    if (signa > signb) {
      flag = 1;
    } else if (signa < signb) {
      flag = -1;
    } else if (abs(dec_a.bits[i]) > abs(dec_b.bits[i]) && signa) {
      flag = -1;  // -A < B
    } else if (abs(dec_a.bits[i]) < abs(dec_b.bits[i]) && signb) {
      flag = 1;  // A > -B
    } else if (abs(dec_a.bits[i]) > abs(dec_b.bits[i])) {
      flag = 1;  // A > B
    } else if (abs(dec_a.bits[i]) < abs(dec_b.bits[i])) {
      flag = -1;  // A < B
    }
  }
  return flag;
}

int CompIntB(int flag, our_big_decimal dec_a, our_big_decimal dec_b) {
  for (int i = 5; i >= 0 && !flag;
       i--) {  // сравниваем в цикле по модулю т.к. скейл одинаковый
    int signa = dec_a.bits[i] < 0 ? 1 : 0;
    int signb = dec_b.bits[i] < 0 ? 1 : 0;
    if (signa > signb) {
      flag = 1;
    } else if (signa < signb) {
      flag = -1;
    } else if (abs(dec_a.bits[i]) > abs(dec_b.bits[i]) && signa) {
      flag = -1;  // -A < B
    } else if (abs(dec_a.bits[i]) < abs(dec_b.bits[i]) && signb) {
      flag = 1;  // A > -B
    } else if (abs(dec_a.bits[i]) > abs(dec_b.bits[i])) {
      flag = 1;  // A > B
    } else if (abs(dec_a.bits[i]) < abs(dec_b.bits[i])) {
      flag = -1;  // A < B
    }
  }
  return flag;
}
/// @return flag = -1  -  A <  B
///         flag = 0  -   A == B
///         flag = 1  -   A >  B
int our_less_great_eq(our_decimal dec_a, our_decimal dec_b) {
  int flag = 0;
  int sdec1 = our_get_sign(dec_a), sdec2 = our_get_sign(dec_b);
  int signa = 0, signb = 0;
  if (our_absolute_zero(dec_a) == 1 && our_absolute_zero(dec_b) == 1) {
    flag = 0;
  } else if (sdec1 != sdec2) {
    flag = sdec1 < sdec2 ? 1 : -1;
  } else {
    if (flag == 0 && our_get_scale(dec_a) > 0 || our_get_scale(dec_b)) {
      our_decimal trunca = {0}, truncb = {0};
      our_truncate(dec_a, &trunca);
      our_truncate(dec_b, &truncb);
      if (flag == 0) flag = CompInt(flag, trunca, truncb);
    }
    our_equal_scales(&dec_a, &dec_b);
    if (flag == 0) flag = CompInt(flag, dec_a, dec_b);
    if (flag == 1) {  // зависимость от знака числа большего по модулю
                      // |A| > |B| если А отрицательное  то результат сравнения
                      // поменяется на обратный если В отрицательное то не
                      // измениться как и при равенстве аналогично при |A| < |B|
      if (sdec1 == 1) flag = -1;
    } else if (flag == -1) {
      if (sdec2 == 1) flag = 1;
    } else if (flag == 0) {  // при равенстве по модулю сравниваем знаки
      if (sdec1 == 1 && sdec2 == 0) flag = -1;
      if (sdec1 == 0 && sdec2 == 1) flag = 1;
    }
  }
  return flag;
}

//  ==Преобразование==  //
int our_from_decimal_to_float(our_decimal src, float *dst) {
  *dst = 0.0;
  int res_code;
  if (dst) {
    res_code = OUR_OK;
    double temp = 0;
    int sign = our_get_sign(src);
    int scale = our_get_scale(src);

    for (int i = 0; i < 96; i++) {
      if (our_get_bit(src, i)) {
        temp += pow(2, i);
      }
    }

    for (int i = 0; i < scale; i++) {
      temp /= 10;
    }

    *dst = (float)temp;
    if (sign) {
      *dst *= -1;
    }
  } else {
    res_code = OUR_CONVERT_ERROR;
  }
  return res_code;
}

int our_from_float_to_decimal(float src, our_decimal *dst) {
  (*dst) = (our_decimal){{0}};
  int res_code = OUR_OK;
  double num = (double)src;
  if (num && dst && src != INFINITY && src != (-INFINITY)) {
    res_code = OUR_OK;
    char sign = 0;
    if (num < 0) {
      sign = 1;
      num = -num;
    }
    char buff[100] = "0", buff2[100] = "0";
    sprintf(buff, "%e", num);
    int limit = strlen(buff);
    int dot = 0, post_dot_counter = 0;
    for (int i = 0; i < limit; i++) {
      if (buff[i] == '.') {
        dot = 1;
        continue;
      }
      buff2[i - dot] = buff[i];
      if (dot == 1) {
        post_dot_counter++;
      }
    }
    int result = atoi(buff2), len = strlen(buff2);
    int scale_e = atoi(buff2 + limit - 3);
    char sign_e = buff[strlen(buff2) - 2];
    if (sign_e == '+') {
    } else if (sign_e == '-') {
      scale_e = -scale_e;
    }
    scale_e = scale_e - post_dot_counter + 4;
    int num = 0;
    while (num == 0) {
      num = result % 10;
      if (num == 0) {
        result /= 10;
        scale_e++;
      }
    }
    dst->bits[0] = result;
    our_set_sign(dst, sign);
    if (abs(scale_e) < 28) {
      if (scale_e >= 0) {
        for (int i = 0; i < scale_e; i++) our_to_ten(dst);
        our_set_scale(dst, 0);
      } else {
        our_set_scale(dst, -scale_e);
      }
    } else {
      res_code = OUR_CONVERT_ERROR;
      our_init_decimal(dst);
    }
  } else {
    res_code = OUR_CONVERT_ERROR;
    our_init_decimal(dst);
  }
  return res_code;
}

//  ==Сравнение==  //
//  ==Прочие функции==  //
int our_floor(our_decimal value, our_decimal *result) {
  int res_code = OUR_OK;
  int scale = our_get_scale(value);
  int sign = our_get_sign(value);
  if (our_absolute_zero(value)) {
    *result = value;
  } else if (scale) {
    res_code = our_truncate(value, result);
    if (sign) {
      our_decimal the_one = {0};
      our_init_decimal(&the_one);
      the_one.bits[3] = 0x80000000;
      the_one.bits[0] = 1;
      res_code = our_add(*result, the_one, result);
    }
  } else {
    *result = value;
  }
  return res_code;
}

int our_round(our_decimal value, our_decimal *result) {
  int res_code = OUR_OK;
  our_decimal floor_result = {0};
  our_decimal temp_result = {0};
  our_decimal standart = {0};
  if (our_get_scale(value) != 0) {
    int sign = our_get_sign(value);
    our_set_bit(&value, 127, 0);
    standart.bits[3] = 0x00010000;
    standart.bits[2] = 0;
    standart.bits[1] = 0;
    standart.bits[0] = 5;  // standart = 0.5
    res_code = our_floor(value, &floor_result);
    our_add(floor_result, standart, &temp_result);
    if (our_is_less_or_equal(temp_result, value)) {
      our_init_decimal(&floor_result);
      res_code = our_add(temp_result, standart, &floor_result);
      our_truncate(floor_result, result);
    } else {
      *result = floor_result;
    }
    if (sign) {
      our_set_sign(result, 1);
    }
  } else {
    *result = value;
  }
  return res_code;
}

int our_truncate(our_decimal value, our_decimal *result) {
  int res_code = OUR_CALC_ERROR;
  if (result) {
    our_init_decimal(result);
    int sign = our_get_sign(value);
    int scale = our_get_scale(value);
    value.bits[3] = 0;
    if (scale) {
      for (int i = 0; i < scale; i++) {
        our_to_ten_div(&value);
      }
      *result = value;
      if (sign) {
        our_set_bit(result, 127, 1);
      }
      res_code = OUR_OK;
    } else {
      *result = value;
      if (sign) {
        our_set_bit(result, 127, 1);
      }
      res_code = OUR_OK;
    }
  } else {
    res_code = OUR_CALC_ERROR;
  }
  return res_code;
}

int our_negate(our_decimal value, our_decimal *result) {
  int res_code = OUR_OK;
  if (result) {
    res_code = OUR_OK;
    result->bits[3] = value.bits[3];
    result->bits[2] = value.bits[2];
    result->bits[1] = value.bits[1];
    result->bits[0] = value.bits[0];
    if (our_get_sign(value)) {
      our_set_bit(result, 127, 0);
    } else {
      our_set_bit(result, 127, 1);
    }
  } else {
    res_code = OUR_CALC_ERROR;
  }
  return res_code;
}

//  ==Арифметика==  //
int our_add(our_decimal value_1, our_decimal value_2, our_decimal *result) {
  int res_code = OUR_OK;
  int scale_1 = our_get_scale(value_1);
  int scale_2 = our_get_scale(value_2);
  if (scale_1 != scale_2) {
    res_code = our_equal_scales(&value_1, &value_2);
    scale_1 = our_get_scale(value_1);
  }
  int sign_1 = our_get_sign(value_1);
  int sign_2 = our_get_sign(value_2);
  our_init_decimal(result);
  if (sign_1 != sign_2) {
    if (our_mant_comp(value_1, value_2) == 1) {
      our_set_sign(&value_2, !sign_2);
      res_code = our_sub(value_1, value_2, result);
    } else if (our_mant_comp(value_1, value_2) == -1) {
      our_set_sign(&value_1, !sign_1);
      res_code = our_sub(value_2, value_1, result);
    } else if (our_mant_comp(value_1, value_2) == 0) {
      (*result) = (our_decimal){{0}};
    }
  } else {
    if (res_code == OUR_OK) {
      our_big_decimal b_value_1 = {0};
      our_big_decimal b_value_2 = {0};
      our_big_decimal b_result = {0};
      our_init_big_decimal(&b_value_1);
      our_init_big_decimal(&b_value_2);
      our_init_big_decimal(&b_result);
      our_from_decimal_to_big_decimal(value_1, &b_value_1);
      our_from_decimal_to_big_decimal(value_2, &b_value_2);
      res_code = our_big_add(b_value_1, b_value_2, &b_result);
      if (res_code == OUR_OK) {
        res_code = our_from_big_decimal_to_decimal(b_result, result);
        our_set_scale(result, scale_1);
        our_set_bit(result, 127, sign_1);
      } else if (res_code == OUR_INF) {
        if (sign_1 == 0) {
          res_code = OUR_INF;
        } else if (sign_1 == 1) {
          res_code = OUR_MINUS_INF;
        }
      }
    }
  }
  return res_code;
}

void our_init_decimal(our_decimal *set_me_free) {
  for (int i = 0; i < 4; i++) set_me_free->bits[i] = 0x0;
}

void our_init_big_decimal(our_big_decimal *set_me_free) {
  for (int i = 0; i < 7; i++) set_me_free->bits[i] = 0x0;
}

void our_set_bit(our_decimal *src, const int n, char bit) {
  if (src) {
    unsigned mask = 1u << (n % 32);
    if (bit == 0) {
      src->bits[n / 32] &= ~mask;
    } else {
      src->bits[n / 32] |= mask;
    }
  }
}

void our_set_bbit(our_big_decimal *src, const int n, char bit) {
  if (src) {
    unsigned mask = 1u << (n % 32);
    if (bit == 0) {
      src->bits[n / 32] &= ~mask;
    } else {
      src->bits[n / 32] |= mask;
    }
  }
}

void our_set_scale(our_decimal *dst, unsigned char mask) {
  unsigned sign = our_get_sign(*dst);
  dst->bits[3] = mask;
  dst->bits[3] = (dst->bits[3] << 16);
  our_set_bit(dst, 127, sign);
}

void our_set_sign(our_decimal *src, char bit) { our_set_bit(src, 127, bit); }

void our_from_decimal_to_big_decimal(our_decimal src, our_big_decimal *dst) {
  our_init_big_decimal(dst);
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[6] = src.bits[3];
}

int our_from_big_decimal_to_decimal(our_big_decimal src, our_decimal *dst) {
  int res_code = OUR_OK;
  our_init_decimal(dst);
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[6];
  if ((src.bits[3] != 0) || (src.bits[4] != 0) || (src.bits[5] != 0)) {
    if (our_get_bsign(src)) {
      res_code = OUR_MINUS_INF;
    } else {
      res_code = OUR_INF;
    }
  } else {
    res_code = OUR_OK;
  }
  return res_code;
}

int our_get_sign(our_decimal src) { return ((src.bits[3] >> 31) & 1); }

int our_get_bsign(our_big_decimal src) { return ((src.bits[6] >> 31) & 1); }

int our_get_scale(our_decimal src) { return ((src.bits[3] & 0xFF0000) >> 16); }

int our_get_bscale(our_big_decimal src) {
  return ((src.bits[6] & 0xFF0000) >> 16);
}

int our_get_bit(our_decimal src, int position) {
  int a = 0;
  int shift_num = 0;
  if (position >= 0 && position <= 31) {
    a = src.bits[0];
    shift_num = position;
  } else if (position >= 32 && position <= 63) {
    a = src.bits[1];
    shift_num = position - 32;
  } else if (position >= 64 && position <= 95) {
    a = src.bits[2];
    shift_num = position - 64;
  } else {
    a = src.bits[3];
    shift_num = position - 96;
  }
  int res = (a >> shift_num) & 1;
  return res;
}

int our_get_bbit(our_big_decimal src, int position) {
  int a = 0;
  int shift_num = 0;
  if (position >= 0 && position <= 31) {
    a = src.bits[0];
    shift_num = position;
  } else if (position >= 32 && position <= 63) {
    a = src.bits[1];
    shift_num = position - 32;
  } else if (position >= 64 && position <= 95) {
    a = src.bits[2];
    shift_num = position - 64;
  } else if (position >= 96 && position <= 127) {
    a = src.bits[3];
    shift_num = position - 96;
  } else if (position >= 128 && position <= 159) {
    a = src.bits[4];
    shift_num = position - 128;
  } else if (position >= 160 && position <= 191) {
    a = src.bits[5];
    shift_num = position - 160;
  } else {
    a = src.bits[6];
    shift_num = position - 192;
  }
  int res = (a >> shift_num) & 1;
  return res;
}

//  ====ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ФУНКЦИИ СЛОЖЕНИЯ====  //
void our_big_add_to_self(our_big_decimal value, our_big_decimal *result) {
  our_big_decimal secunda = {0};
  secunda.bits[6] = result->bits[6];
  secunda.bits[5] = result->bits[5];
  secunda.bits[4] = result->bits[4];
  secunda.bits[3] = result->bits[3];
  secunda.bits[2] = result->bits[2];
  secunda.bits[1] = result->bits[1];
  secunda.bits[0] = result->bits[0];
  our_init_big_decimal(result);
  result->bits[6] = value.bits[6];
  int x = 0;
  int y = 0;
  char mark = 0;
  for (int i = 0; i < 192; i++) {
    x = our_get_bbit(value, i);
    y = our_get_bbit(secunda, i);
    if (x && y) {
      if (mark) {
        our_set_bbit(result, i, 1);
      } else {
        mark = 1;
      }
    } else if (x || y) {
      if (!mark) {
        our_set_bbit(result, i, 1);
      }
    } else {
      if (mark) {
        our_set_bbit(result, i, 1);
        mark = 0;
      }
    }
  }
}

void our_big_left_shift(our_big_decimal *b_value) {
  int thirty_one = our_get_bbit(*b_value, 31);
  int sixty_three = our_get_bbit(*b_value, 63);
  int ninety_five = our_get_bbit(*b_value, 95);
  int one_two_seven = our_get_bbit(*b_value, 127);
  int one_five_nine = our_get_bbit(*b_value, 159);
  b_value->bits[5] <<= 1;
  b_value->bits[4] <<= 1;
  b_value->bits[3] <<= 1;
  b_value->bits[2] <<= 1;
  b_value->bits[1] <<= 1;
  b_value->bits[0] <<= 1;
  if (thirty_one) our_set_bbit(b_value, 32, 1);
  if (sixty_three) our_set_bbit(b_value, 64, 1);
  if (ninety_five) our_set_bbit(b_value, 96, 1);
  if (one_two_seven) our_set_bbit(b_value, 128, 1);
  if (one_five_nine) our_set_bbit(b_value, 160, 1);
}

int our_to_ten(our_decimal *value) {
  int res_code = OUR_OK;
  int sign = our_get_sign(*value);
  int scale = our_get_scale(*value);
  our_big_decimal b_value = {0};
  our_big_decimal result = {0};
  our_init_big_decimal(&result);
  our_init_big_decimal(&b_value);
  our_from_decimal_to_big_decimal(*value, &b_value);
  int b = 10;
  while (b != 0) {
    if ((b & 0x1) == 0x1) {
      our_big_add_to_self(b_value, &result);
    }
    b >>= 1;
    our_big_left_shift(&b_value);
  }
  res_code = our_from_big_decimal_to_decimal(result, value);
  if (res_code == OUR_OK) {
    our_set_bit(value, 127, sign);
    our_set_scale(value, ++scale);
  }
  return res_code;
}

int our_equal_scales(our_decimal *value_1, our_decimal *value_2) {
  int res_code = 1;
  int scale_1 = our_get_scale(*value_1);
  int scale_2 = our_get_scale(*value_2);

  if (scale_1 < scale_2) {
    while (res_code || (scale_1 != scale_2)) {
      res_code = our_to_ten(value_1);

      scale_1 = our_get_scale(*value_1);
    }
  } else if (scale_2 < scale_1) {
    while (res_code || scale_1 != scale_2) {
      res_code = our_to_ten(value_2);
      scale_2 = our_get_scale(*value_2);
    }
  }
  return res_code;
}

int our_big_add(our_big_decimal value_1, our_big_decimal value_2,
                our_big_decimal *result) {
  int res_code = OUR_OK;
  our_init_big_decimal(result);
  char x = 0;
  char y = 0;
  char mark = 0;
  for (int i = 0; i < 192; i++) {
    x = our_get_bbit(value_1, i);
    y = our_get_bbit(value_2, i);
    int sc1 = our_get_bscale(value_1), sc2 = our_get_bscale(value_2);
    if (x && y) {
      if (mark) {
        our_set_bbit(result, i, 1);
      } else {
        mark = 1;
      }
    } else if (x || y) {
      if (!mark) {
        our_set_bbit(result, i, 1);
      }
    } else {
      if (mark) {
        our_set_bbit(result, i, 1);
        mark = 0;
      }
    }
  }
  /// тут надо сравнить результат с our_big_decimal
  int sc1 = our_get_bscale(value_1), sc2 = our_get_bscale(value_2);
  if (sc1 == 0 && sc2 == 0) {
    if (result->bits[5] == 0b11111111111111111111111111111111) {
      res_code = OUR_INF;
    }
    if (result->bits[3] >= 0b00000000000000000000000000000001) {
      res_code = OUR_INF;
    }
    if (result->bits[2] >= 0b11111111111111111111111111111111) {
      res_code = OUR_INF;
    }
  }
  return res_code;
}

//  ====ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ФУНКЦИИ TRUNCATE====  //

void our_char_shift_set_bit(char *dst, char bit) {
  *dst <<= 1;
  char mask = 1;
  if (bit) {
    *dst |= mask;
  } else {
    *dst &= ~mask;
  }
}

int our_to_ten_div(our_decimal *value) {
  our_decimal result = {0};
  our_init_decimal(&result);
  char ten = 10;
  char temp = 0;
  char buff = 0;
  int count = 95;
  while (count != -1) {
    temp = our_get_bit(*value, count);
    if (temp || buff) {
      while (buff < ten && count > -1) {
        our_char_shift_set_bit(&buff, temp);
        temp = our_get_bit(*value, --count);
      }
      ++count;
      if (buff >= ten) our_set_bit(&result, count, 1);
      buff = buff - ten;
    }
    count--;
  }
  value->bits[2] = result.bits[2];
  value->bits[1] = result.bits[1];
  value->bits[0] = result.bits[0];
  return buff;
}

int our_mant_comp(our_decimal value_1,
                  our_decimal value_2) {  // mantissa compare
  int a, b, result = 0;
  for (int i = 95; i >= 0; i--) {
    a = our_get_bit(value_1, i);
    b = our_get_bit(value_2, i);
    if (a > b) {
      result = 1;
      break;
    } else if (b > a) {
      result = -1;
      break;
    }
  }
  return result;
}

//  ====ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ФУНКЦИИ ROUND====  //
int our_absolute_zero(our_decimal value) {
  int res = 1;
  if (value.bits[2] != 0 || value.bits[1] != 0 || value.bits[0] != 0) res = 0;
  return res;
}

int our_from_int_to_decimal(int src, our_decimal *dst) {
  int res_code = OUR_OK;
  our_init_decimal(dst);
  if (dst) {
    if (src >= 0) {
      (*dst).bits[0] = src;
    } else {
      (*dst).bits[0] = -src;
      our_set_bit(dst, 127, 1);
    }
    res_code = OUR_OK;
  } else {
    res_code = OUR_CONVERT_ERROR;
  }
  return res_code;
}

int our_from_decimal_to_int(our_decimal src, int *dst) {
  int res_code = OUR_OK;
  our_truncate(src, &src);
  if (dst) {
    *dst = src.bits[0];
    if (our_get_sign(src) == 1) {
      *dst = -*dst;
    }
    res_code = OUR_OK;
  } else {
    res_code = OUR_CONVERT_ERROR;
  }
  return res_code;
}

int our_mul(our_decimal value_1, our_decimal value_2, our_decimal *result) {
  int res_code = OUR_OK, scale;
  int sign_1 = our_get_sign(value_1);
  int sign_2 = our_get_sign(value_2);
  our_init_decimal(result);
  if (sign_1 != sign_2) {
    sign_1 = 1;
  } else {
    sign_1 = 0;
  }
  int scale_1 = our_get_scale(value_1);
  int scale_2 = our_get_scale(value_2);
  scale = scale_1 + scale_2;
  if (res_code == OUR_OK) {
    our_big_decimal b_value_1 = {0};
    our_big_decimal b_value_2 = {0};
    our_big_decimal b_result = {0};
    our_from_decimal_to_big_decimal(value_1, &b_value_1);
    our_from_decimal_to_big_decimal(value_2, &b_value_2);
    char y = 0;
    for (int i = 0; i < 192; i++) {
      y = our_get_bbit(b_value_2, i);
      if (y == 1) {
        res_code = our_big_add(b_value_1, b_result, &b_result);
      } else {
      }
      our_big_left_shift(&b_value_1);
    }
    if (res_code == OUR_OK) {
      res_code = our_from_big_decimal_to_decimal(b_result, result);
      our_set_scale(result, scale);
      our_set_bit(result, 127, sign_1);
    } else {
      if (sign_1 == 1) {
        res_code = OUR_MINUS_INF;
      } else {
        res_code = OUR_INF;
      }
    }
  }
  return res_code;
}

// lightang

int our_sub(our_decimal value_1, our_decimal value_2, our_decimal *result) {
  int res_code = OUR_OK;
  int sign_1 = our_get_sign(value_1);
  int sign_2 = our_get_sign(value_2);
  char greater_flag = 0;  // зачем эта переменная
  our_init_decimal(result);
  if (sign_1 != sign_2) {
    // меняем знак второй переменной и отправляем на сложение - a
    // - + b = - a - b //  + a - - b = + a + b
    our_set_sign(&value_2, sign_1);
    sign_2 = sign_1;
    res_code = our_add(value_1, value_2, result);
  } else if (sign_1 == sign_2) {
    int h = our_mant_comp(value_1, value_2);
    if (our_mant_comp(value_1, value_2) == 1) {
      // эта часть кода определяет старшее число
      // если а > b то оставить как есть
    } else if (our_mant_comp(value_1, value_2) == -1) {
      // если а < b то через buffer меняем местами value_1 с value_2
      our_decimal buffer = value_1;
      value_1 = value_2;
      our_set_sign(&value_1, !sign_2);
      sign_2 = !sign_2;
      value_2 = buffer;
    }
    int sign_1 = our_get_sign(value_1);
    our_set_sign(result, sign_1);
    int scale_1 = our_get_scale(value_1);
    int scale_2 = our_get_scale(value_2);
    if (scale_1 != scale_2) {
      res_code = our_equal_scales(&value_1, &value_2);
      scale_1 = our_get_scale(value_1);
    }
    if (res_code == OUR_OK) {
      char a = 0;
      char b = 0;
      char count_mem = 0;
      for (int i = 0; i < 96; i++) {
        a = our_get_bit(value_1, i);
        b = our_get_bit(value_2, i);
        if (a && !b) {
          our_set_bit(result, i, 1);
        } else if (b && !a) {
          while (!a) {
            a = our_get_bit(value_1, ++i);
            count_mem++;
          }
          our_set_bit(&value_1, i, 0);
          while (count_mem) {
            i--;
            if (count_mem != 1) {
              our_set_bit(&value_1, i, 1);
            }
            count_mem--;
          }
          our_set_bit(result, i, 1);
        }
      }
    }
    if (res_code == OUR_OK) {
      if (scale_1) {
        our_set_scale(result, scale_1);
      }
      if (!sign_1 && greater_flag == 1) {
        our_set_bit(result, 127, 1);
      }
    } else {
      if (!sign_1 && greater_flag == 1) {
        res_code = OUR_MINUS_INF;

        our_init_decimal(result);
      }
    }
  }
  if (!sign_1 && res_code != 0) {
    res_code = OUR_MINUS_INF;
    our_init_decimal(result);
  }
  return res_code;
}

// div

int our_div(our_decimal value_1, our_decimal value_2, our_decimal *result) {
  /*Инициализация знаков и степеней*/
  int res_code = OUR_OK, flag = 0;
  our_set_zero_dec(result);
  if (our_absolute_zero(value_2) == 1) {
    res_code = OUR_NAN;
    flag = 1;
  }
  int co2 = -1;
  if (flag == 0) {
    if (!(value_1.bits[2] == 0 && value_1.bits[1] == 0 &&
          value_1.bits[0] == 0)) {
      int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
      int scale_1 = get_scale(value_1), scale_2 = get_scale(value_2);
      set_sign(0, &value_1);
      set_sign(0, &value_2);
      set_scale(0, &value_1);
      set_scale(0, &value_2);
      int desired_scale = 28, count = 0;
      our_big_decimal b_value_1 = {0};
      our_big_decimal b_value_2 = {0};
      our_from_decimal_to_big_decimal(value_1, &b_value_1);
      our_from_decimal_to_big_decimal(value_2, &b_value_2);
      our_big_decimal b_result = {0};
      while (desired_scale - scale_1) {
        our_to_ten_big(&b_value_1);
        scale_1++;
      }
      while (desired_scale - scale_2) {
        our_to_ten_big(&b_value_2);
        scale_2++;
      }
      our_big_decimal tmp = {0};
      while (our_is_greater_big(b_value_1, b_value_2)) {
        our_to_ten_big(&b_value_2);
        co2--;
      }
      while (!(our_absolute_zero_b(b_value_1)) &&
             !(our_absolute_zero_b(b_value_2))) {
        our_to_ten_big(&b_result);
        while (our_is_greater_or_equal_big(b_value_1, b_value_2)) {
          our_big_sub(b_value_1, b_value_2, &tmp);
          our_b_decimal_copy(&b_value_1, &tmp);
          count++;
        }
        our_to_ten_div_b(&b_value_2);  // для биг децимал
        co2++;
        our_decimal dec_count = {0};
        our_big_decimal b_dec_count = {0};
        our_from_int_to_decimal(count, &dec_count);
        our_from_decimal_to_big_decimal(dec_count, &b_dec_count);
        our_big_add(b_result, b_dec_count, &b_result);
        count = 0;
      }
      co2 = -co2;
      while (co2 > 0) {
        our_to_ten_big(&b_result);
        co2--;
      }
      while (co2 <= 0) {
        if (co2 == 0 && !our_check_overflow(b_result)) {
          res_code = OUR_INF;
          return res_code;
        }
        if (our_check_overflow(b_result)) {
          break;
        } else {
          our_to_ten_div_b(&b_result);
          co2++;
        }
      }
      our_from_big_decimal_to_decimal(b_result, result);
      set_scale(abs(co2), result);
      (sign_1 == sign_2) ? set_sign(0, result) : set_sign(1, result);
    }
  }
  return res_code;
}

void our_set_zero_mantisa_big(our_uint96_t v) {
  for (uint8_t i = 0; i < 5; i++) v[i] = 0;
}

void our_set_zero_big_decimal(our_big_decimal *v) {
  v->bits[6] = 0;
  our_set_zero_mantisa_big(v->bits);
}

void our_set_zero_int96(our_uint96_t v) {
  for (uint8_t i = 0; i < 3; i++) v[i] = 0;
}

void our_set_zero_dec(our_decimal *v) {
  v->bits[3] = 0;
  our_set_zero_int96(v->bits);
}

int get_sign(our_decimal dst) { return (dst.bits[3] & SIGN) == SIGN; }

void set_sign(int s, our_decimal *dst) {
  if (s == 0)
    dst->bits[3] = (dst->bits[3] << 1) >> 1;
  else
    dst->bits[3] |= SIGN;
}

int get_scale(our_decimal dst) {
  uint8_t s = dst.bits[3] >> 16;
  return s;
}

void set_scale(int sc, our_decimal *dst) {
  int s = dst->bits[3] & SIGN;
  dst->bits[3] = s | sc << 16;
}

int our_to_ten_big(our_big_decimal *value) {
  int res_code = OUR_OK;
  our_big_decimal b_value = {0};
  our_big_decimal result = {0};
  our_init_big_decimal(&result);
  our_init_big_decimal(&b_value);
  our_b_decimal_copy(&b_value, value);
  int b = 10;
  while (b != 0) {
    if ((b & 0x1) == 0x1) {
      our_big_add_to_self(b_value, &result);
    }
    b >>= 1;
    our_big_left_shift(&b_value);
  }
  our_b_decimal_copy(value, &result);
  return res_code;
}

int our_is_greater_big(our_big_decimal dec_a, our_big_decimal dec_b) {
  int flag = 0;

  if (our_less_great_eq_big(dec_a, dec_b) == 1) flag = 1;
  return flag;
}

int our_is_greater_or_equal_big(our_big_decimal dec_a, our_big_decimal dec_b) {
  return (our_is_greater_big(dec_a, dec_b) || our_is_equal_big(dec_a, dec_b))
             ? 1
             : 0;
}

int our_is_equal_big(our_big_decimal dec_a, our_big_decimal dec_b) {
  int flag = 0;
  if (our_less_great_eq_big(dec_a, dec_b) == 0) flag = 1;
  return flag;
}

int our_big_sub(our_big_decimal value_1, our_big_decimal value_2,
                our_big_decimal *result) {
  our_big_decimal inverse_value_2 = {0};
  our_set_zero_big_decimal(&inverse_value_2);
  if (our_is_greater_or_equal_big(value_1, value_2)) {
    for (uint8_t i = 0; i < 7; i++) {
      if (i < 6) {
        inverse_value_2.bits[i] = ~value_2.bits[i];
      }
      if (i == 6) {
        inverse_value_2.bits[i] = value_2.bits[i] ^ bit_31;
      }
    }
  }
  int one = 1;
  our_decimal one1 = {0};
  our_big_decimal one11 = {0};
  our_from_int_to_decimal(one, &one1);
  our_from_decimal_to_big_decimal(one1, &one11);
  our_big_decimal real_value_2 = {0};
  our_big_add(inverse_value_2, one11, &real_value_2);
  int res = our_big_add(value_1, real_value_2, result);
  return res;
}

int our_absolute_zero_b(our_big_decimal value) {
  int res = 1;
  if (value.bits[5] != 0 || value.bits[4] != 0 || value.bits[3] != 0 ||
      value.bits[2] != 0 || value.bits[1] != 0 || value.bits[0] != 0)
    res = 0;
  return res;
}

void our_b_decimal_copy(our_big_decimal *dec_1, our_big_decimal *dec_2) {
  for (int i = 0; i < 7; i++) dec_1->bits[i] = dec_2->bits[i];
}

int our_to_ten_div_b(our_big_decimal *value) {
  our_big_decimal result = {0};
  our_init_big_decimal(&result);
  char ten = 10;
  char temp = 0;
  char buff = 0;
  int count = 191;
  while (count != -1) {
    temp = our_get_bbit(*value, count);
    if (temp || buff) {
      while (buff < ten && count > -1) {
        our_char_shift_set_bit(&buff, temp);
        temp = our_get_bbit(*value, --count);
      }
      ++count;
      if (buff >= ten) our_set_bbit(&result, count, 1);
      buff = buff - ten;
    }
    count--;
  }
  value->bits[5] = result.bits[5];
  value->bits[4] = result.bits[4];
  value->bits[3] = result.bits[3];
  value->bits[2] = result.bits[2];
  value->bits[1] = result.bits[1];
  value->bits[0] = result.bits[0];
  return buff;
}

int our_check_overflow(our_big_decimal value) {
  int res = 0;
  if (value.bits[5] == 0 && value.bits[4] == 0 && value.bits[3] == 0) res = 1;
  return res;
}

#include "our_decimal.h"

int our_less_great_eq_big(our_big_decimal dec_a, our_big_decimal dec_b) {
  int flag = 0;
  int sdec1 = our_get_sign_big(dec_a), sdec2 = our_get_sign_big(dec_b);
  int signa, signb;
  if (our_absolute_zero_b(dec_a) == 1 && our_absolute_zero_b(dec_b) == 1) {
    flag = 0;
  } else if (sdec1 != sdec2) {
    flag = sdec1 < sdec2 ? 1 : -1;
  }
  if (flag == 0) {
    flag = CompIntB(flag, dec_a, dec_b);
    if (flag == 1) {
      if (sdec1 == 1) flag = -1;
    } else if (flag == -1) {
      if (sdec2 == 1) flag = 1;
    } else if (flag == 0) {  // при равенстве по модулю сравниваем знаки
      if (sdec1 == 1 && sdec2 == 0) flag = -1;
      if (sdec1 == 0 && sdec2 == 1) flag = 1;
    }
  }
  return flag;
}

int our_get_sign_big(our_big_decimal src) { return ((src.bits[6] >> 31) & 1); }
