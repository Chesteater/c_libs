#ifndef SRC_OUR_DECIMAL_H
#define SRC_OUR_DECIMAL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUR_CONVERT_ERROR 1
#define OUR_CALC_ERROR 1

#define SIGN 0x80000000
#define MAX4 0xFFFFFFFF
#define bit_31 0x7FFFFFFF
typedef int32_t *our_uint96_t;

#define MAX_SCALE 28

#define OUR_OK 0
#define OUR_INF 1
#define OUR_MINUS_INF 2
#define OUR_NAN 3

#define OUR_CONVERT_ERROR 1
#define OUR_CALC_ERROR 1


typedef struct {
  int bits[4];
} our_decimal;

typedef struct {
  int bits[7];
} our_big_decimal;
//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -
//                                                                         -
//                 == CONVERTING ==                                        -
//                                                                         -
//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -

/**
 * @brief Преобразователь из int в decimal
 * @param src int
 * @param dst pointer to decimal
 * @return 0 - success, 1 - error
 */
int our_from_int_to_decimal(int src, our_decimal *dst);

/**
 * @brief Преобразователь из float в decimal
 * @param src float
 * @param dst pointer to decimal
 * @return 0 - success, 1 - error
 */
int our_from_float_to_decimal(float src, our_decimal *dst);

/**
 * @brief Преобразователь из decimal в int
 * @param src decimal
 * @param dst pointer to int
 * @return 0 - success, 1 - error
 */
int our_from_decimal_to_int(our_decimal src, int *dst);

/**
 * @brief Преобразователь из decimal в float
 * @param src decimal
 * @param dst pointer to float
 * @return 0 - success, 1 - error
 */
int our_from_decimal_to_float(our_decimal src, float *dst);

//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -
//                                                                         -
//                 == COMPARISON OPERATORS ==                              -
//                                                                         -
//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -

/**
 * @brief Меньше
 * @param value_1 first number
 * @param value_2 second number
 * @return 0 - false, 1 - true
 */
int our_is_less(our_decimal dec_a, our_decimal dec_b);

/**
 * @brief Меньше или равно
 * @param value_1 first number
 * @param value_2 second numberl
 * @return 0 - false, 1 - true
 */
int our_is_less_or_equal(our_decimal dec_a, our_decimal dec_b);

/**
 * @brief Больше
 * @param value_1 first number
 * @param value_2 second number
 * @return 0 - false, 1 - true
 */
int our_is_greater(our_decimal dec_a, our_decimal dec_b);

/**
 * @brief Больше или равно
 * @param value_1 first number
 * @param value_2 second number
 * @return 0 - false, 1 - true
 */
int our_is_greater_or_equal(our_decimal dec_a, our_decimal dec_b);

/**
 * @brief Равно
 * @param value_1 first number
 * @param value_2 second number
 * @return 0 - false, 1 - true
 */
int our_is_equal(our_decimal dec_a, our_decimal dec_b);

/**
 * @brief Не равно
 * @param value_1 first number
 * @param value_2 second number
 * @return 0 - false, 1 - true
 */
int our_is_not_equal(our_decimal dec_a, our_decimal dec_b);

//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -
//                                                                         -
//                 == OTHER FUN ==                                         -
//                                                                         -
//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -

/**
 * @brief Округляет указанное Decimal число до ближайшего целого числа
 * в сторону отрицательной бесконечности
 * @param value decimal num to be rounded
 * @param result pointer to decimal num to be filled by rouned num
 * @return 0 - ok, 1 - error
 */
int our_floor(our_decimal value, our_decimal *result);

/**
 * @brief Округляет Decimal до ближайшего целого числа
 * @param value decimal num to be rounded
 * @param result pointer to decimal num to be filled by rouned num
 * @return 0 - ok, 1 - error
 */
int our_round(our_decimal value, our_decimal *result);

/**
 * @brief Возвращает целые цифры указанного Decimal числа; любые дробные
 * цифры отбрасываются, включая конечные нули.
 * @param value decimal num who will take integer digits
 * @param result pointer to decimal num to be filled by integer digits by value
 * @return 0 - ok, 1 - error
 */
int our_truncate(our_decimal value, our_decimal *result);

/**
 * @brief Возвращает результат умножения указанного Decimal на -1
 * @param value decimal num to be multiplying by -1
 * @param result pointer to decimal num to be filled by multiplyed num
 * @return 0 - ok, 1 - error
 */
int our_negate(our_decimal value, our_decimal *result);

//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -
//                                                                         -
//                 == ARITHMETIC ==                                        -
//                                                                         -
//- - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - -

/**
 * @brief Сложение
 * @param value_1 first number
 * @param value_2 second number
 * @param result pointer to decimal for add result
 * @return 0 - success, 1 - result too big, 2 - result too small
 */
int our_add(our_decimal value_1, our_decimal value_2, our_decimal *result);

/**
 * @brief Вычитание
 * @param value_1 first number
 * @param value_2 second number
 * @param result pointer to decimal for sub result
 * @return 0 - success, 1 - too big, 2 - too small
 */
int our_sub(our_decimal value_1, our_decimal value_2, our_decimal *result);

/**
 * @brief Умножение
 * @param value_1 first number
 * @param value_2 second number
 * @param result pointer to decimal for mul result
 * @return 0 - success, 1 - too big, 2 - too small
 */
int our_mul(our_decimal value_1, our_decimal value_2, our_decimal *result);

/**
 * @brief Деление
 * @param value_1 first number
 * @param value_2 second number
 * @param result pointer to decimal for div result
 * @return 0 - success, 1 - too big, 2 - too small, 3 - div on zero
 */
int our_div(our_decimal value_1, our_decimal value_2, our_decimal *result);

//..........................................................................
//                                                                         .
//                 == AUXILIARY FUNCTIONS ==                               .
//                                                                         .
//..........................................................................

void our_init_decimal(our_decimal *set_me_free);
void our_init_big_decimal(our_big_decimal *set_me_free);
void our_set_bit(our_decimal *src, const int n, char bit);
void our_set_bbit(our_big_decimal *src, const int n, char bit);
void our_set_scale(our_decimal *dst, unsigned char mask);
void our_set_sign(our_decimal *src, char bit);
void our_from_decimal_to_big_decimal(our_decimal src, our_big_decimal *dst);
int our_from_big_decimal_to_decimal(our_big_decimal src, our_decimal *dst);
int our_get_sign(our_decimal src);
int our_get_bsign(our_big_decimal src);
int our_get_scale(our_decimal src);
int our_get_bscale(our_big_decimal src);
int our_get_bit(our_decimal src, int position);
int our_get_bbit(our_big_decimal src, int position);

//..........................................................................
//                                                                         .
//                 == FOR THE ADDITION FUNCTION ==                         .
//                                                                         .
//..........................................................................

void our_big_add_to_self(our_big_decimal value, our_big_decimal *result);
void our_big_left_shift(our_big_decimal *b_value);
int our_to_ten(our_decimal *value);
int our_equal_scales(our_decimal *value_1, our_decimal *value_2);
int our_big_add(our_big_decimal value_1, our_big_decimal value_2,
                our_big_decimal *result);

//..........................................................................
//                                                                         .
//          == AUXILIARY FUNCTIONS FOR THE TRUNCATE FUNCTION ==            .
//                                                                         .
//..........................................................................

int our_to_ten_div(our_decimal *value);
void our_char_shift_set_bit(char *dst, char bit);

//..........................................................................
//                                                                         .
//          == AUXILIARY FUNCTIONS FOR THE SUBTRACT FUNCTION ==            .
//                                                                         .
//..........................................................................

int our_mant_comp(our_decimal value_1, our_decimal value_2);

//..........................................................................
//                                                                         .
//          == AUXILIARY FUNCTIONS FOR THE ROUND FUNCTION ==               .
//                                                                         .
//..........................................................................

int our_absolute_zero(our_decimal value);

//..........................................................................
//                                                                         .
//              == AUXILIARY FUNCTIONS FOR COMPARISON ==                   .
//                                                                         .
//..........................................................................

int our_less_great_eq(our_decimal dec_a, our_decimal dec_b);

//..........................................................................
//                                                                         .
//                          == OTHER ==                                    .
//                                                                         .
//..........................................................................


int our_less_great_eq_big(our_big_decimal dec_a, our_big_decimal dec_b);

int our_get_sign_big(our_big_decimal src);


// utherydg

// set and get
void our_set_zero_int96(our_uint96_t v);
void our_set_zero_dec(our_decimal *v);
void our_set_scale_b(int sc, our_big_decimal *dst);
void our_set_zero_mantisa_big(our_uint96_t v);
void our_set_zero_big_decimal(our_big_decimal *v);
int get_sign(our_decimal dst);
void set_sign(int s, our_decimal *dst);
int get_scale(our_decimal dst);
void set_scale(int sc, our_decimal *dst);

// check
int our_absolute_zero_b(our_big_decimal value);
int our_is_greater_big(our_big_decimal dec_a, our_big_decimal dec_b);
int our_is_greater_or_equal_big(our_big_decimal dec_a, our_big_decimal dec_b);
int our_is_equal_big(our_big_decimal dec_a, our_big_decimal dec_b);

// other
void our_b_decimal_copy(our_big_decimal *dec_1, our_big_decimal *dec_2);
int our_to_ten_div_b(our_big_decimal *value);
int our_to_ten_big(our_big_decimal *value);
int our_big_sub(our_big_decimal value_1, our_big_decimal value_2,
                our_big_decimal *result);
int CompInt(int flag, our_decimal dec_a, our_decimal dec_b);                
int our_check_overflow(our_big_decimal value);
int CompIntB(int flag, our_big_decimal dec_a, our_big_decimal dec_b);
#endif  // SRC_OUR_DECIMAL_H