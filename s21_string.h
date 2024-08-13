#ifndef S21_STRING_H
#define S21_STRING_H

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8192
#define s21_NULL (void *)0
#define s21_size_t unsigned long long
#define S21_ERRNO_COUNT 134

typedef struct format_option_struct {
  int width;
  int precision;
  char length;
  int left_justify;
  int show_sign;
  int space_sign;
  int alternate_form;
  int zero_pad;
  char specifier;
} format_option;

// STRING FUNCTION

int s21_sprintf(char *str, const char *format, ...);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
s21_size_t s21_strlen(const char *string);
int s21_check_mem(const char *str1, const char *str2, int n);
char *s21_strstr(const char *haystask, const char *needle);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strtok(char *str, const char *delim);
void *s21_to_lower(const char *str);
char to_lower_char(char ch);
void s21_strcpy(char *dest, const char *src);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_to_upper(const char *str);
char to_upper_char(char ch);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void s21_errnum_tostring(char *str, int num);
char *s21_strcat(char *dest, const char *src);

// HANDLERS

void handle_specifier_c(char **str, format_option *opts, va_list args,
                        int *length);

void handle_specifier_s(char **str, format_option *opts, va_list args,
                        int *length);

void handle_specifier_d(char **str, format_option *opts, va_list args,
                        int *length);
long int extract_arg_d(format_option *opts, va_list args);
char process_sign_d(long int *n, format_option *opts);

void handle_specifier_u(char **str, format_option *opts, va_list args,
                        int *length);

void handle_specifier_f(char **str, format_option *opts, va_list args,
                        int *length);
int process_special_values_f(long double value, format_option *opts, char *sign,
                             char *temp_str);

void handle_specifier_o(char **str, format_option *opts, va_list args,
                        int *length);

void handle_specifier_p(char **str, format_option *opts, va_list args,
                        int *length);

void handle_specifier_e(char **str, format_option *opts, va_list args,
                        int *length);
int process_special_values_e(long double value, format_option *opts,
                             char *temp_str);

void handle_specifier_g(char **str, format_option *opts, va_list args,
                        int *length);
int process_special_values_g(long double value, format_option *opts,
                             char *temp_str);

void handle_specifier_x(char **str, format_option *opts, va_list args,
                        int *length);
void process_precision_x(char *temp_str, int *temp_len, int precision);
void process_alternate_form_x(char *temp_str, int *temp_len, char specifier);

void parse_format_options(const char **format, format_option *opts,
                          va_list *args);

// COMMON FUNCTIONS

unsigned long int extract_arg_uox(format_option *opts, va_list args);
long double extract_arg_feg(format_option *opts, va_list args);
char process_sign_feg(long double *value, format_option *opts);
int add_sign_dfeg(char *temp_str, int *temp_len, char sign,
                  format_option *opts);
int add_left_justify(char **str, const char *temp_str, int temp_len,
                     format_option *opts);
void add_padding(char **str, char *temp_str, int temp_len, int total_len,
                 char pad_char);

// CONVERTERS

void int_to_str(long long int n, char *str, int *len);
void uint_to_str(unsigned long long int n, char *str, int *len);
void double_to_str(long double n, char *str, int *len, format_option *opts);
void pointer_to_hex_str(void *ptr, char *str, int *len, format_option *opts);
void uint_to_octal_str(unsigned long long int n, char *str, int *len);
void double_to_exp_str(long double value, char *str, format_option *opts);
void double_to_str_g(long double n, char *str, int *len, format_option *opts);
void handle_zero_value(char *str, int *len, format_option *opts);
void format_normal(long double n, char *str, int *len, format_option *opts);
void format_exponential(long double n, char *str, int *len, format_option *opts,
                        int exponent);
void uint_to_hex_str(unsigned long long int num, char *str, int *len,
                     format_option *opts);

void round_fraction(char *str, int *len);
void reverse_str(char *str, int len);

#endif