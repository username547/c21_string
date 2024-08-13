#include <check.h>

#include "s21_string.h"

void test_c(const char *format, char value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_s(const char *format, const char *value) {
  char expected[SIZE];
  char result[SIZE];
  sprintf(expected, format, value);
  s21_sprintf(result, format, value);
  ck_assert_str_eq(expected, result);
}

void test_d(const char *format, int value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_u(const char *format, unsigned int value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_f(const char *format, double value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_o(const char *format, unsigned int value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_p(const char *format, void *value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_e(const char *format, double value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_g(const char *format, double value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(expected, result);
  ck_assert_int_eq(num1, num2);
}

void test_g_long(const char *format, long double value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(expected, result);
  ck_assert_int_eq(num1, num2);
}

void test_x(const char *format, unsigned int value) {
  char expected[SIZE];
  char result[SIZE];
  int num1 = sprintf(expected, format, value);
  int num2 = s21_sprintf(result, format, value);
  ck_assert_str_eq(result, expected);
  ck_assert_int_eq(num1, num2);
}

void test_memchr(const char *str, int c, s21_size_t n) {
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}

void test_memcmp(const char *str1, const char *str2, s21_size_t n) {
  int expected = memcmp(str1, str2, n);
  int result = s21_memcmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}

void test_memcpy(const char *str, s21_size_t n) {
  char expected[SIZE];
  char result[SIZE];
  s21_memcpy(result, str, n);
  memcpy(expected, str, n);
  ck_assert_mem_eq(expected, result, n);
}

void test_memset(char *str, int c, s21_size_t n) {
  char result[SIZE];
  char expected[SIZE];
  strncpy(result, str, SIZE);
  strncpy(expected, str, SIZE);
  s21_memset(result, c, n);
  memset(expected, c, n);
  ck_assert_mem_eq(result, expected, SIZE);
}

void test_strchr(const char *str, int c) {
  char *expected = strchr(str, c);
  char *result = s21_strchr(str, c);
  ck_assert_ptr_eq(expected, result);
}

void test_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int expected = strncmp(str1, str2, n);
  int result = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(expected, result);
}

void test_strcspn(const char *str1, const char *str2) {
  s21_size_t expected = strcspn(str1, str2);
  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(expected, result);
}

void test_strerror(int errnum) {
  char *result = s21_strerror(errnum);
  char *expected = strerror(errnum);
  ck_assert_str_eq(result, expected);
}

void test_strlen(const char *str) {
  s21_size_t expected = strlen(str);
  s21_size_t result = s21_strlen(str);
  ck_assert_int_eq(expected, result);
}

void test_strpbrk(const char *str1, const char *str2) {
  const char *expected = strpbrk(str1, str2);
  const char *result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(expected, result);
}

void test_strrchr(const char *str, int c) {
  char *result = s21_strrchr(str, c);
  char *expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}

void test_strstr(const char *haystack, const char *needle) {
  char *result = s21_strstr(haystack, needle);
  char *expected = strstr(haystack, needle);
  ck_assert_ptr_eq(result, expected);
}

void test_strtok(char *str1, char *str2, const char *delim) {
  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(NULL, delim);
    token2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token1, token2);
}

void test_to_upper(char *str, const char *expected) {
  char *result = (char *)s21_to_upper(str);

  if (expected != NULL) {
    for (int i = 0; str[i] != '\0'; i++) {
      ck_assert_int_eq(toupper(str[i]), result[i]);
    }
    ck_assert_str_eq(result, expected);
  } else {
    ck_assert_ptr_eq(result, s21_NULL);
  }

  free(result);
}

void test_to_lower(char *str, const char *expected) {
  char *result = (char *)s21_to_lower(str);

  if (expected != NULL) {
    for (int i = 0; str[i] != '\0'; i++) {
      if (isalpha(str[i])) {
        ck_assert_int_eq(tolower(str[i]), result[i]);
      } else {
        ck_assert_int_eq(str[i], result[i]);
      }
    }
    ck_assert_str_eq(result, expected);
  } else {
    ck_assert_ptr_eq(result, NULL);
  }

  free(result);
}

void test_insert(const char *src, const char *str, size_t start_index,
                 const char *expected) {
  char *result = (char *)s21_insert(src, str, start_index);
  if (expected == NULL) {
    ck_assert_ptr_eq(result, NULL);
  } else {
    ck_assert_str_eq(result, expected);
    free(result);
  }
}

void trim_test(char *src, char *trim_chars, const char *expected) {
  char *result = (char *)s21_trim(src, trim_chars);

  if (expected != NULL) {
    ck_assert_str_eq(result, expected);
  } else {
    ck_assert_ptr_eq(result, NULL);
  }

  free(result);
}

void test_strncat(char *dest, const char *src, size_t n) {
  char expected[SIZE];
  char result[SIZE];
  strcpy(result, dest);
  strcpy(expected, dest);
  strncat(expected, src, n);
  s21_strncat(result, src, n);
  ck_assert_str_eq(result, expected);
}

void test_strncpy(const char *src, size_t n) {
  char result[SIZE];
  char expected[SIZE];
  strncpy(expected, src, n);
  s21_strncpy(result, src, n);
  ck_assert_str_eq(result, expected);
}

START_TEST(s21_sprintf_test_c) {
  test_c("%c", 'q');
  test_c("%5c", 'q');
  test_c("%-5c", 'q');
  char expected[SIZE];
  char result[SIZE];
  sprintf(expected, "%*c", 5, 'q');
  s21_sprintf(result, "%*c", 5, 'q');
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
  test_s("%s", NULL);
  test_s("%s", "Hello, World!");
  test_s("Hello %%s world", "Hello, World!");
  test_s("Hello % %s world", "Hello, World!");
  test_s("Hello % % s world", "Hello, World!");
  test_s("Hello   %   %   s world", "Hello, World!");
  test_s("Hello   %   %   s % sworld", "Hello, World!");
  test_s("%s", "");
  test_s("%s", " ");
  test_s("%10.5s", "Hello, World!");
  test_s("%-10.5s", "Hello, World!");
  test_s("%.5s", "Hello, World!");
  test_s("%5s", "Hello, World!");
  test_s("%-5s", "Hello, World!");
  test_s("%s", "This is a very long string to test s21_sprintf.");
  test_s("%20.10s", "This is a very long string to test s21_sprintf.");
  test_s("%-20.10s", "This is a very long string to test s21_sprintf.");
  test_s("%.10s", "This is a very long string to test s21_sprintf.");
  test_s("%50s", "This is a very long string to test s21_sprintf.");
  test_s("%-50s", "This is a very long string to test s21_sprintf.");
  test_s("%.0s", "Hello, World!");
  test_s("%10.0s", "Hello, World!");
  test_s("%-10.0s", "Hello, World!");
}
END_TEST

START_TEST(s21_sprintf_test_d) {
  test_d("%d", 123);
  test_d("%10d", 123);
  test_d("%-10d", 123);
  test_d("%010d", 123);
  test_d("%+10d", 123);
  test_d("% 10d", 123);
  test_d("%.5d", 123);
  test_d("%10.5d", 123);
  test_d("%-10.5d", 123);
  test_d("%+10.5d", 123);
  test_d("% 10.5d", 123);
  test_d("%-+10.5d", 123);
  test_d("%- 10.5d", 123);
  test_d("%-010.5d", 123);
  test_d("%0+10d", 123);
  test_d("%d", -123);
  test_d("%10d", -123);
  test_d("%-10d", -123);
  test_d("%010d", -123);
  test_d("%+10d", -123);
  test_d("% 10d", -123);
  test_d("%.5d", -123);
  test_d("%10.5d", -123);
  test_d("%-10.5d", -123);
  test_d("%+10.5d", -123);
  test_d("% 10.5d", -123);
  test_d("%-+10.5d", -123);
  test_d("%- 10.5d", -123);
  test_d("%-010.5d", -123);
  test_d("%hd", (short)123);
  test_d("%10hd", (short)123);
  test_d("%-10hd", (short)123);
  test_d("%010hd", (short)123);
  test_d("%+10hd", (short)123);
  test_d("% 10hd", (short)123);
  test_d("%.5hd", (short)123);
  test_d("%10.5hd", (short)123);
  test_d("%-10.5hd", (short)123);
  test_d("%+10.5hd", (short)123);
  test_d("% 10.5hd", (short)123);
  test_d("%-+10.5hd", (short)123);
  test_d("%- 10.5hd", (short)123);
  test_d("%-010.5hd", (short)123);
  test_d("%0+10hd", (short)123);
  test_d("%ld", 123L);
  test_d("%10ld", 123L);
  test_d("%-10ld", 123L);
  test_d("%010ld", 123L);
  test_d("%+10ld", 123L);
  test_d("% 10ld", 123L);
  test_d("%.5ld", 123L);
  test_d("%10.5ld", 123L);
  test_d("%-10.5ld", 123L);
  test_d("%+10.5ld", 123L);
  test_d("% 10.5ld", 123L);
  test_d("%-+10.5ld", 123L);
  test_d("%- 10.5ld", 123L);
  test_d("%-010.5ld", 123L);
  test_d("%0+10ld", 123L);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  test_u("%u", 123);
  test_u("%10u", 123);
  test_u("%-10u", 123);
  test_u("%010u", 123);
  test_u("%.5u", 123);
  test_u("%10.5u", 123);
  test_u("%-10.5u", 123);
  test_u("%010.5u", 123);
  test_u("%u", 123456789);
  test_u("%20u", 123456789);
  test_u("%-20u", 123456789);
  test_u("%020u", 123456789);
  test_u("%.10u", 123456789);
  test_u("%20.10u", 123456789);
  test_u("%-20.10u", 123456789);
  test_u("%020.10u", 123456789);
  test_u("%hu", (unsigned short)123);
  test_u("%10hu", (unsigned short)123);
  test_u("%-10hu", (unsigned short)123);
  test_u("%010hu", (unsigned short)123);
  test_u("%.5hu", (unsigned short)123);
  test_u("%10.5hu", (unsigned short)123);
  test_u("%-10.5hu", (unsigned short)123);
  test_u("%010.5hu", (unsigned short)123);
  test_u("%lu", 123UL);
  test_u("%10lu", 123UL);
  test_u("%-10lu", 123UL);
  test_u("%010lu", 123UL);
  test_u("%.5lu", 123UL);
  test_u("%10.5lu", 123UL);
  test_u("%-10.5lu", 123UL);
  test_u("%010.5lu", 123UL);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
  test_f("%f", 123.456);
  test_f("%.2f", 123.456);
  test_f("%10f", 123.456);
  test_f("%+f", 123.456);
  test_f("% f", 123.456);
  test_f("%+010.2f", 123.456);
  test_f("%-#12.4f", 123.456);
  test_f("%20.15f", 0.000012345);
  test_f("%#20.15f", 0.000012345);
  test_f("%020.15f", 0.000012345);
  test_f("%30.10f", 123456789.987654321);
  test_f("%+30.10f", 123456789.987654321);
  test_f("% 30.10f", 123456789.987654321);
  test_f("%f", -123.456);
  test_f("%.2f", -123.456);
  test_f("%10f", -123.456);
  test_f("%+f", -123.456);
  test_f("% f", -123.456);
  test_f("%+010.2f", -123.456);
  test_f("%-#12.4f", -123.456);
  test_f("%f", 0.0);
  test_f("%.2f", 0.0);
  test_f("%10f", 0.0);
  test_f("%+f", 0.0);
  test_f("% f", 0.0);
  test_f("%+010.2f", 0.0);
  test_f("%-#12.4f", 0.0);
  test_f("%#.0f", 0.0);
  test_f("%.0f", 0.0);
  test_f("%#10.0f", 0.0);
  test_f("%-10.0f", 0.0);
  test_f("%10.2f", 0.0);
  test_f("%#10.2f", 0.0);
  test_f("%020.5f", 0.0);
  test_f("%+020.2f", 0.0);
  test_f("%-020.2f", 0.0);
  test_f("%-10.0f", 0.0);
  test_f("%50.40f", 123.456);
  test_f("%#50.40f", 123.456);
  test_f("%050.40f", 123.456);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
  test_o("%o", 123);
  test_o("%#o", 123);
  test_o("%10o", 123);
  test_o("%-10o", 123);
  test_o("%010o", 123);
  test_o("%.5o", 123);
  test_o("%10.5o", 123);
  test_o("%-10.5o", 123);
  test_o("%ho", (unsigned short)123);
  test_o("%lo", (unsigned long)123);
  test_o("%10ho", (unsigned short)123);
  test_o("%10lo", (unsigned long)123);
  test_o("%10.5ho", (unsigned short)123);
  test_o("%10.5lo", (unsigned long)123);
  test_o("%#10.5o", 123);
  test_o("%#-10.5o", 123);
  test_o("%#10ho", (unsigned short)123);
  test_o("%#10lo", (unsigned long)123);
  test_o("%#10.5ho", (unsigned short)123);
  test_o("%#10.5lo", (unsigned long)123);
  test_o("%-15lo", (unsigned long)41293764);
  test_o("%o", 0);
  test_o("%#o", 0);
  test_o("%010o", 0);
  test_o("%#.0o", 0);
  test_o("%o", 0xFFFFFFFF);
  test_o("%#o", 0xFFFFFFFF);
  test_o("%20o", 0xFFFFFFFF);
  test_o("%#20o", 0xFFFFFFFF);
  test_o("%020o", 0xFFFFFFFF);
  test_o("%#020o", 0xFFFFFFFF);
  test_o("%.20o", 0xFFFFFFFF);
  test_o("%20.20o", 0xFFFFFFFF);
  test_o("%#20.20o", 0xFFFFFFFF);
  test_o("%#-0 20.20o", 0xFFFFFFFF);
  test_o("%#-0 20.20ho", (unsigned short)0xFFFF);
  test_o("%#-0 20.20lo", (unsigned long)0xFFFFFFFF);
  test_o("%5.20o", 123);
  test_o("%5.20ho", (unsigned short)123);
  test_o("%5.20lo", (unsigned long)123);
  test_o("%50.40o", 0xFFFFFFFF);
  test_o("%50.40ho", (unsigned short)0xFFFF);
  test_o("%50.40lo", (unsigned long)0xFFFFFFFF);
  test_o("%-#8.5o", 123);
  test_o("%-#8.5ho", (unsigned short)123);
  test_o("%-#8.5lo", (unsigned long)123);
  test_o("%32o", 0xFFFFFFFF);
  test_o("%32ho", (unsigned short)0xFFFF);
  test_o("%32lo", (unsigned long)0xFFFFFFFF);
  test_o("%#50.50o", 0xFFFFFFFF);
  test_o("%#50.50ho", (unsigned short)0xFFFF);
  test_o("%#50.50lo", (unsigned long)0xFFFFFFFF);
  test_o("%#-0 32.32o", 0xFFFFFFFF);
  test_o("%#-0 32.32ho", (unsigned short)0xFFFF);
  test_o("%#-0 32.32lo", (unsigned long)0xFFFFFFFF);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
  int a = 42;
  void *ptr1 = &a;
  void *ptr2 = NULL;
  test_p("%p", ptr1);
  test_p("%p", ptr2);
  test_p("%10p", ptr1);
  test_p("%10p", ptr2);
  test_p("%-10p", ptr1);
  test_p("%-10p", ptr2);
  test_p("%20p", ptr1);
  test_p("%20p", ptr2);
  test_p("%-20p", ptr1);
  test_p("%-20p", ptr2);
  test_p("%.20p", ptr1);
  test_p("%.20p", ptr2);
  test_p("%20.20p", ptr1);
  test_p("%20.20p", ptr2);
  test_p("%-20.20p", ptr1);
  test_p("%-20.20p", ptr2);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
  test_e("%e", 1234.567);
  test_e("%.2e", 1234.567);
  test_e("%10.2e", 1234.567);
  test_e("%-10.2e", 1234.567);
  test_e("%10.2e", -1234.567);
  test_e("%010.2e", 1234.567);
  test_e("%+.2e", 1234.567);
  test_e("% e", 1234.567);
  test_e("%E", 1234.567);
  test_e("%.2E", 1234.567);
  test_e("%10.2E", 1234.567);
  test_e("%-10.2E", 1234.567);
  test_e("%10.2E", -1234.567);
  test_e("%010.2E", 1234.567);
  test_e("%+.2E", 1234.567);
  test_e("% E", 1234.567);
  test_e("%20.5e", 1234.567);
  test_e("%-20.5e", 1234.567);
  test_e("%+20.5e", 1234.567);
  test_e("% 20.5e", 1234.567);
  test_e("%020.5e", 1234.567);
  test_e("%-+20.5e", 1234.567);
  test_e("%- 20.5e", 1234.567);
  test_e("%+020.5e", 1234.567);
  test_e("% 020.5e", 1234.567);
  test_e("%20.5e", -1234.567);
  test_e("%-20.5e", -1234.567);
  test_e("%+20.5e", -1234.567);
  test_e("% 20.5e", -1234.567);
  test_e("%020.5e", -1234.567);
  test_e("%-+20.5e", -1234.567);
  test_e("%- 20.5e", -1234.567);
  test_e("%+020.5e", -1234.567);
  test_e("% 020.5e", -1234.567);
  test_e("%20.5E", 1234.567);
  test_e("%-20.5E", 1234.567);
  test_e("%+20.5E", 1234.567);
  test_e("% 20.5E", 1234.567);
  test_e("%020.5E", 1234.567);
  test_e("%-+20.5E", 1234.567);
  test_e("%- 20.5E", 1234.567);
  test_e("%+020.5E", 1234.567);
  test_e("% 020.5E", 1234.567);
  test_e("%20.5E", -1234.567);
  test_e("%-20.5E", -1234.567);
  test_e("%+20.5E", -1234.567);
  test_e("% 20.5E", -1234.567);
  test_e("%020.5E", -1234.567);
  test_e("%-+20.5E", -1234.567);
  test_e("%- 20.5E", -1234.567);
  test_e("%+020.5E", -1234.567);
  test_e("% 020.5E", -1234.567);
  test_e("%5.0e", 1234.567);
  test_e("%5.1e", 1234.567);
  test_e("%5.2e", 1234.567);
  test_e("%5.3e", 1234.567);
  test_e("%5.4e", 1234.567);
  test_e("%5.5e", 1234.567);
  test_e("%5.6e", 1234.567);
  test_e("%5.0E", 1234.567);
  test_e("%5.1E", 1234.567);
  test_e("%5.2E", 1234.567);
  test_e("%5.3E", 1234.567);
  test_e("%5.4E", 1234.567);
  test_e("%5.5E", 1234.567);
  test_e("%5.6E", 1234.567);
  test_e("%.0e", 1234.567);
  test_e("%.1e", 1234.567);
  test_e("%.2e", 1234.567);
  test_e("%.3e", 1234.567);
  test_e("%.4e", 1234.567);
  test_e("%.5e", 1234.567);
  test_e("%.6e", 1234.567);
  test_e("%.0E", 1234.567);
  test_e("%.1E", 1234.567);
  test_e("%.2E", 1234.567);
  test_e("%.3E", 1234.567);
  test_e("%.4E", 1234.567);
  test_e("%.5E", 1234.567);
  test_e("%.6E", 1234.567);
  test_e("%#e", 1234.567);
  test_e("%#.2e", 1234.567);
  test_e("%#10.2e", 1234.567);
  test_e("%#-10.2e", 1234.567);
  test_e("%#10.2e", -1234.567);
  test_e("%#010.2e", 1234.567);
  test_e("%#+.2e", 1234.567);
  test_e("%# e", 1234.567);
  test_e("%#E", 1234.567);
  test_e("%#.2E", 1234.567);
  test_e("%#10.2E", 1234.567);
  test_e("%#-10.2E", 1234.567);
  test_e("%#10.2E", -1234.567);
  test_e("%#010.2E", 1234.567);
  test_e("%#+.2E", 1234.567);
  test_e("%# E", 1234.567);
  test_e("%#20.5e", 1234.567);
  test_e("%#-20.5e", 1234.567);
  test_e("%#+20.5e", 1234.567);
  test_e("%# 20.5e", 1234.567);
  test_e("%#020.5e", 1234.567);
  test_e("%#-+20.5e", 1234.567);
  test_e("%#- 20.5e", 1234.567);
  test_e("%#+020.5e", 1234.567);
  test_e("%# 020.5e", 1234.567);
  test_e("%#20.5e", -1234.567);
  test_e("%#-20.5e", -1234.567);
  test_e("%#+20.5e", -1234.567);
  test_e("%# 20.5e", -1234.567);
  test_e("%#020.5e", -1234.567);
  test_e("%#-+20.5e", -1234.567);
  test_e("%#- 20.5e", -1234.567);
  test_e("%#+020.5e", -1234.567);
  test_e("%# 020.5e", -1234.567);
  test_e("%#20.5E", 1234.567);
  test_e("%#-20.5E", 1234.567);
  test_e("%#+20.5E", 1234.567);
  test_e("%# 20.5E", 1234.567);
  test_e("%#020.5E", 1234.567);
  test_e("%#-+20.5E", 1234.567);
  test_e("%#- 20.5E", 1234.567);
  test_e("%#+020.5E", 1234.567);
  test_e("%# 020.5E", 1234.567);
  test_e("%#20.5E", -1234.567);
  test_e("%#-20.5E", -1234.567);
  test_e("%#+20.5E", -1234.567);
  test_e("%# 20.5E", -1234.567);
  test_e("%#020.5E", -1234.567);
  test_e("%#-+20.5E", -1234.567);
  test_e("%#- 20.5E", -1234.567);
  test_e("%#+020.5E", -1234.567);
  test_e("%# 020.5E", -1234.567);
  test_e("%#.0e", 1234.567);
  test_e("%#.1e", 1234.567);
  test_e("%#.2e", 1234.567);
  test_e("%#.3e", 1234.567);
  test_e("%#.4e", 1234.567);
  test_e("%#.5e", 1234.567);
  test_e("%#.6e", 1234.567);
  test_e("%#.0E", 1234.567);
  test_e("%#.1E", 1234.567);
  test_e("%#.2E", 1234.567);
  test_e("%#.3E", 1234.567);
  test_e("%#.4E", 1234.567);
  test_e("%#.5E", 1234.567);
  test_e("%#.6E", 1234.567);
  test_e("%#.0e", 1234.567);
  test_e("%#.1e", 1234.567);
  test_e("%#.2e", 1234.567);
  test_e("%#.3e", 1234.567);
  test_e("%#.4e", 1234.567);
  test_e("%#.5e", 1234.567);
  test_e("%#.6e", 1234.567);
  test_e("%#.0E", 1234.567);
  test_e("%#.1E", 1234.567);
  test_e("%#.2E", 1234.567);
  test_e("%#.3E", 1234.567);
  test_e("%#.4E", 1234.567);
  test_e("%#.5E", 1234.567);
  test_e("%#.6E", 1234.567);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
  test_g("%g", 123.456);
  test_g("%g", 0.0);
  test_g("%.2g", 123.456);
  test_g("%10.2g", 123.456);
  test_g("%-10.2g", 123.456);
  test_g("%010.2g", 123.456);
  test_g("%+g", 123.456);
  test_g("% g", 123.456);
  test_g("%g", 0.000123456);
  test_g("%.2g", 0.000123456);
  test_g("%10.2g", 0.000123456);
  test_g("%-10.2g", 0.000123456);
  test_g("%010.2g", 0.000123456);
  test_g("%+010.4g", 0.000123456);
  test_g("%+g", -123.456);
  test_g("% g", -123.456);
  test_g("%g", -0.000123456);
  test_g("%.2g", -0.000123456);
  test_g("%10.2g", -0.000123456);
  test_g("%-10.2g", -0.000123456);
  test_g("%010.2g", -0.000123456);
  test_g("%g", 0.0);
  test_g("%.2g", 0.0);
  test_g("%10.2g", 0.0);
  test_g("%-10.2g", 0.0);
  test_g("%010.2g", 0.0);
  test_g("%g", 9876543210.987654321);
  test_g("%.5g", 9876543210.987654321);
  test_g("%15.8g", 9876543210.987654321);
  test_g("%010.5g", 9876543210.987654321);
  test_g("%+g", 9876543210.987654321);
  test_g("% g", 9876543210.987654321);
  test_g("%g", -9876543210.987654321);
  test_g("%.5g", -9876543210.987654321);
  test_g("%15.8g", -9876543210.987654321);
  test_g("%010.5g", -9876543210.987654321);
  test_g("%+g", -9876543210.987654321);
  test_g("% g", -9876543210.987654321);
  test_g("%-20.12g", 9876543210.987654321);
  test_g("%-20.12g", -9876543210.987654321);
  test_g("%-20.12g", 1234567890.0987654321);
  test_g("%-20.12g", -1234567890.0987654321);
  test_g("%-20.12g", 12345678901234567890.12345678901234567890);
  test_g("%-20.12g", -12345678901234567890.12345678901234567890);
  test_g("%-20.12g", 123.456789012345678901234567890);
  test_g("%-20.12g", -123.456789012345678901234567890);
  test_g("%-20.12g", 0.123456789012345678901234567890);
  test_g("%-20.12g", -0.123456789012345678901234567890);
  test_g("%+g", 12345678901234567890.12345678901234567890);
  test_g("%+10.12g", 12345678901234567890.12345678901234567890);
  test_g("%+010.12g", 12345678901234567890.12345678901234567890);
  test_g("% +g", 12345678901234567890.12345678901234567890);
  test_g("% +10.12g", 12345678901234567890.12345678901234567890);
  test_g("% +010.12g", 12345678901234567890.12345678901234567890);
  test_g("%+g", -12345678901234567890.12345678901234567890);
  test_g("%+10.12g", -12345678901234567890.12345678901234567890);
  test_g("%+010.12g", -12345678901234567890.12345678901234567890);
  test_g("% +g", -12345678901234567890.12345678901234567890);
  test_g("% +10.12g", -12345678901234567890.12345678901234567890);
  test_g("% +010.12g", -12345678901234567890.12345678901234567890);
  test_g("%-20.12G", 12345678901234567890.12345678901234567890);
  test_g("%-20.12G", -12345678901234567890.12345678901234567890);
  test_g("%-20.12G", 123.456789012345678901234567890);
  test_g("%-20.12G", -123.456789012345678901234567890);
  test_g("%-20.12G", 0.123456789012345678901234567890);
  test_g("%-20.12G", -0.123456789012345678901234567890);
  test_g("%#g", 123.456);
  test_g("%#.2g", 123.456);
  test_g("%#10.2g", 123.456);
  test_g("%#-10.2g", 123.456);
  test_g("%#010.2g", 123.456);
  test_g("%#+g", 123.456);
  test_g("%# g", 123.456);
  test_g("%#g", 0.000123456);
  test_g("%#.2g", 0.000123456);
  test_g("%#10.2g", 0.000123456);
  test_g("%#-10.2g", 0.000123456);
  test_g("%#010.2g", 0.000123456);
  test_g("%#+010.4g", 0.000123456);
  test_g("%#+g", -123.456);
  test_g("%# g", -123.456);
  test_g("%#g", -0.000123456);
  test_g("%#.2g", -0.000123456);
  test_g("%#10.2g", -0.000123456);
  test_g("%#-10.2g", -0.000123456);
  test_g("%#010.2g", -0.000123456);
  test_g("%#g", 0.0);
  test_g("%#.2g", 0.0);
  test_g("%#10.2g", 0.0);
  test_g("%#-10.2g", 0.0);
  test_g("%#010.2g", 0.0);
  test_g("%#-20.12g", 12345678901234567890.12345678901234567890);
  test_g("%#-20.12g", -12345678901234567890.12345678901234567890);
  test_g("%#-20.12g", 123.456789012345678901234567890);
  test_g("%#-20.12g", -123.456789012345678901234567890);
  test_g("%#-20.12g", 0.123456789012345678901234567890);
  test_g("%#-20.12g", -0.123456789012345678901234567890);
  test_g_long("%Lg", 0.0L);
  test_g_long("%.2Lg", 0.0L);
  test_g_long("%10.2Lg", 0.0L);
  test_g_long("%-10.2Lg", 0.0L);
  test_g_long("%010.2Lg", 0.0L);
  test_g_long("%#010.0Lg", 0.0L);
  test_g_long("%#+10.4Lg", 0.0L);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
  test_x("%x", 123);
  test_x("%X", 123);
  test_x("%5x", 123);
  test_x("%5X", 123);
  test_x("%-5x", 123);
  test_x("%-5X", 123);
  test_x("%#x", 123);
  test_x("%#X", 123);
  test_x("%08x", 123);
  test_x("%08X", 123);
  test_x("%#08x", 123);
  test_x("%#08X", 123);
  test_x("%.5x", 123);
  test_x("%.5X", 123);
  test_x("%#08.5x", 123);
  test_x("%#08.5X", 123);
  test_x("%-#8.5x", 123);
  test_x("%-#8.5X", 123);
  test_x("%x", 0);
  test_x("%#x", 0);
  test_x("%08x", 0);
  test_x("%#08x", 0);
  test_x("%#-0 8.5x", 0xFFFFFFFF);
  test_x("%#32x", 0xFFFFFFFF);
  test_x("%50.40x", 0xFFFFFFFF);
  test_x("%-#8.5x", 0xFFFFFFFF);
  test_x("%#08.5x", 0xFFFFFFFF);
  test_x("%0128x", 0xFFFFFFFF);
  test_x("%32x", 0xFFFFFFFF);
  test_x("%#50.50x", 0xFFFFFFFF);
  test_x("%#-0 32.32x", 0xFFFFFFFF);
  test_x("% 128x", 0xFFFFFFFF);
  test_x("%5.20x", 0x1234);
  test_x("%20.10x", 0x1234);
  test_x("%#-0 12.5x", 123);
  test_x("%#08x", 0);
  test_x("%08x", 0);
  test_x("%-8x", 0);
  test_x("%hx", (unsigned short)123);
  test_x("%#hx", (unsigned short)123);
  test_x("%5hx", (unsigned short)123);
  test_x("%-5hx", (unsigned short)123);
  test_x("%08hx", (unsigned short)123);
  test_x("%#08hx", (unsigned short)123);
  test_x("%.5hx", (unsigned short)123);
  test_x("%#08.5hx", (unsigned short)123);
  test_x("%-#8.5hx", (unsigned short)123);
  test_x("%lx", (unsigned long)123);
  test_x("%#lx", (unsigned long)123);
  test_x("%5lx", (unsigned long)123);
  test_x("%-5lx", (unsigned long)123);
  test_x("%08lx", (unsigned long)123);
  test_x("%#08lx", (unsigned long)123);
  test_x("%.5lx", (unsigned long)123);
  test_x("%#08.5lx", (unsigned long)123);
  test_x("%-#8.5lx", (unsigned long)123);
  test_x("%hx", (unsigned short)0);
  test_x("%#hx", (unsigned short)0);
  test_x("%08hx", (unsigned short)0);
  test_x("%#08hx", (unsigned short)0);
  test_x("%lx", (unsigned long)0);
  test_x("%#lx", (unsigned long)0);
  test_x("%08lx", (unsigned long)0);
  test_x("%#08lx", (unsigned long)0);
  test_x("%#32lx", (unsigned long)0xFFFFFFFF);
  test_x("%#32lX", (unsigned long)0xFFFFFFFF);
  test_x("%50.40lx", (unsigned long)0xFFFFFFFF);
  test_x("%50.40lX", (unsigned long)0xFFFFFFFF);
}
END_TEST

START_TEST(s21_memchr_test) {
  test_memchr("Hello, world!", 'o', strlen("Hello, world!"));
  test_memchr("Hello, world!", 'x', strlen("Hello, world!"));
  test_memchr("", 'a', strlen(""));
  test_memchr("Hello, world!", 'o', 0);
  test_memchr("Hello, world! Hello, world!", 'o',
              strlen("Hello, world! Hello, world!"));
  test_memchr("Hello, world!", 'H', strlen("Hello, world!"));
  test_memchr("Hello, world!", '!', strlen("Hello, world!"));
  test_memchr("Hello\0world", '\0', strlen("Hello") + 1);
  test_memchr("Hello, world!", 'w', strlen("Hello, world!"));
  test_memchr("a", 'a', strlen("a"));
  test_memchr("aaaaa", 'a', strlen("aaaaa"));
  test_memchr("   ", ' ', strlen("   "));
  test_memchr("Hello, world!", 'W', strlen("Hello, world!"));
  test_memchr("Hello, \n\tworld!", '\n', strlen("Hello, \n\tworld!"));
  test_memchr("1234567890", '5', strlen("1234567890"));
}
END_TEST

START_TEST(s21_memcmp_test) {
  test_memcmp("Hello", "Hello", 5);
  test_memcmp("", "", 0);
  test_memcmp("HelloWorld", "HelloMars", 5);
  test_memcmp("Hello", "HelloWorld", 5);
  test_memcmp("HelloA", "HelloB", 6);
  test_memcmp("AHello", "BHello", 6);
  test_memcmp("Hello\0World", "Hello\0Mars", 11);
  test_memcmp("Hello World", "Hello World", 11);
  test_memcmp("Hello123", "Hello124", 8);
  test_memcmp("Hello@#", "Hello@#", 7);
  test_memcmp("Hello", "Hello123", 5);
}
END_TEST

START_TEST(s21_memcpy_test) {
  const char str[] = "Hello, world! 12345@";
  test_memcpy(str, 13);
  test_memcpy("", 1);
  test_memcpy(str, 0);
  test_memcpy(str, 5);
  test_memcpy(str, 5);
  test_memcpy(str, 5);
  test_memcpy("\0\0\0\0\0", 5);
}
END_TEST

START_TEST(s21_memset_test) {
  test_memset("Hello, world!", 'A', 5);
  test_memset("", 'A', 1);
  test_memset("Hello, world!", 'B', 5);
  test_memset("Hello, world!", 'A', 0);
  test_memset("Hello, world!", 0, 5);
  test_memset("Hello, world!", 'A', 15);
  test_memset("Hello, world!", '\t', 5);
  test_memset("Hello, world!", ',', 3);
  test_memset("Hello, world!", '$', 5);
}
END_TEST

START_TEST(s21_strchr_test) {
  test_strchr("Hello, World!", '!');
  const char *empty_str = "";
  test_strchr(empty_str, 'a');
  const char non_terminated_str[] = {'a', 'b', 'c'};
  test_strchr(non_terminated_str, '\0');
  const char multi_occurrence_str[] = "banana";
  test_strchr(multi_occurrence_str, 'a');
  const char control_char_str[] = "Hello, world!";
  test_strchr(control_char_str, '\t');
  const char separator_char_str[] = "Hello, world!";
  test_strchr(separator_char_str, ',');
  const char special_chars_str[] = "!@#$%^&*()";
  test_strchr(special_chars_str, '%');
  const char whitespace_str[] = "   ";
  test_strchr(whitespace_str, ' ');
  const char newline_str[] = "Hello,\nworld!";
  test_strchr(newline_str, '\n');
  const char carriage_return_str[] = "Hello,\rworld!";
  test_strchr(carriage_return_str, '\r');
  const char tab_str[] = "Hello,\tworld!";
  test_strchr(tab_str, '\t');
  const char crlf_str[] = "Hello,\r\nworld!";
  test_strchr(crlf_str, '\n');
  const char backslash_str[] = "C:\\Program Files\\";
  test_strchr(backslash_str, '\\');
  const char quote_str[] = "She said, \"Hello!\"";
  test_strchr(quote_str, '\"');
}
END_TEST

START_TEST(s21_strncmp_test) {
  test_strncmp("Hello, world!", "Hello, world!", 13);
  test_strncmp("Hello, world!", "Hello, everyone!", 13);
  test_strncmp("Hello", "Hello, world!", 13);
  test_strncmp("Hello", "Hello, world!", 0);
  test_strncmp("", "", 5);
  test_strncmp("Hello", "", 5);
  test_strncmp("", "Hello", 5);
  test_strncmp("hello", "Hello", 5);
  test_strncmp("Hello, world!", "Hello, earth!", 7);
  test_strncmp("Hello world", "Hello world!", 11);
  test_strncmp("Hello!", "Hello?", 5);
  test_strncmp("Hello", "Hello, world!", 5);
  test_strncmp("HelloWorld", "HelloThere", 5);
}
END_TEST

START_TEST(s21_strcspn_test) {
  test_strcspn("Hello, world!", "o,");
  test_strcspn("Hello, world!", "xyz");
  test_strcspn("Hello, world!", "");
  test_strcspn("", "xyz");
  test_strcspn("", "");
  test_strcspn("Hello, world!", "H");
  test_strcspn("Hello, world!", "r");
  test_strcspn("Hello, world!", "xyz");
  test_strcspn("Hello, world!", "Helo, wrd!");
  test_strcspn("Hello, world!", "!dlrow ,olleH");
  test_strcspn("H", "Hello");
  test_strcspn("Hello", "H");
  test_strcspn("a", "bcd");
  test_strcspn("a", "abc");
}
END_TEST

START_TEST(s21_strerror_test) {
  test_strerror(0);
  test_strerror(106);
  test_strerror(2147483647);
  test_strerror(-214748364);
}
END_TEST

START_TEST(s21_strlen_test) {
  const char *str =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec "
      "odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla "
      "quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent "
      "mauris. Fusce nec tellus sed augue semper porta. Mauris massa. "
      "Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad "
      "litora torquent per conubia nostra, per inceptos himenaeos. Curabitur "
      "sodales ligula in libero.";
  const char *str_null = s21_NULL;
  test_strlen("Hello, world!");
  test_strlen("");
  test_strlen("    ");
  test_strlen("123!@#");
  test_strlen("Hello\0world!");
  test_strlen(str);
  test_strlen("\t\t\t \t");

  s21_size_t expected = (s21_size_t)-1;
  s21_size_t result = s21_strlen(str_null);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(s21_strpbrk_test) {
  test_strpbrk("abcdefg", "123cd");
  test_strpbrk("abcdefg", "123");
  test_strpbrk("", "123");
  test_strpbrk("abcdefg", "");
  test_strpbrk("abcdefg", "a");
  test_strpbrk("abcdefg", "g");
  test_strpbrk("", "");
  test_strpbrk("a", "abc");
  test_strpbrk("a", "bcd");
  test_strpbrk("abcdefg", "gfedcba");
  test_strpbrk("abcdefg", "abcdefg");
  test_strpbrk("abc!@#", "!@#");
  test_strpbrk("!", "!@#");
  test_strpbrk("abc!def", "!");
  test_strpbrk("This is a very long string for testing purposes.", "t");
  test_strpbrk("t", "This is a very long string for testing purposes.");
}
END_TEST

START_TEST(s21_strrchr_test) {
  test_strrchr("abcdefg", 'c');
  test_strrchr("abcdefg", 'z');
  test_strrchr("", 'a');
  test_strrchr("Hello, world!", '\0');
  test_strrchr("abcdecf", 'c');
  test_strrchr("abcdefg", 'a');
  test_strrchr("abcdefg", 'g');
  test_strrchr("a", 'a');
  test_strrchr("a", 'b');
  test_strrchr("abc$defg", '$');
  test_strrchr("abc123def", '3');
  test_strrchr("abc def ghi", ' ');
  test_strrchr("aaabbbccc", 'a');
  test_strrchr("abc\0def", 'd');
  test_strrchr("a1b2c3!@#", '2');
  test_strrchr("xxxxxxxxxx", 'x');
}
END_TEST

START_TEST(s21_strstr_test) {
  test_strstr("hello world", "world");
  test_strstr("hello world", "hello");
  test_strstr("hello world", "foo");
  test_strstr("", "world");
  test_strstr("hello world", "");
  test_strstr("hello world", "w");
  test_strstr("hello world", "h");
  test_strstr("hello world", "d");
  test_strstr("aaaabaaa", "ba");
  test_strstr("     ", " ");
  test_strstr("hello @world!", "@world");
  test_strstr("hello123world", "123");
  test_strstr("he1llo@world!", "llo@");
  test_strstr("hello world", "hello world");
}
END_TEST

START_TEST(s21_strtok_test) {
  test_strtok((char[50]){"Hello, world! This is a test."},
              (char[50]){"Hello, world! This is a test."}, " ,.!");
  test_strtok((char[50]){",,,"}, (char[50]){",,,"}, ",");
  test_strtok((char[50]){"Hello"}, (char[50]){"Hello"}, ",");
  test_strtok((char[50]){""}, (char[50]){""}, ",");
  test_strtok((char[50]){"Hello,,,world"}, (char[50]){"Hello,,,world"}, ",");
  test_strtok((char[50]){"Hello;world,how:are-you?"},
              (char[50]){"Hello;world,how:are-you?"}, ";,:-?");
  test_strtok((char[50]){",,Hello world"}, (char[50]){",,Hello world"}, ",");
  test_strtok((char[50]){"Hello world,,"}, (char[50]){"Hello world,,"}, ",");
  test_strtok((char[50]){"Hello  world   test"},
              (char[50]){"Hello  world   test"}, " ");
  test_strtok((char[50]){"Hello##world##test"},
              (char[50]){"Hello##world##test"}, "##");
  test_strtok((char[50]){","}, (char[50]){","}, ",");
  test_strtok((char[50]){"Hello   world"}, (char[50]){"Hello   world"}, " ");
  test_strtok((char[50]){"Hello\tworld\ttest"},
              (char[50]){"Hello\tworld\ttest"}, "\t ");
  test_strtok((char[50]){"Hello\nworld\ntest"},
              (char[50]){"Hello\nworld\ntest"}, "\n");
  test_strtok((char[50]){"abc123!def456"}, (char[50]){"abc123!def456"}, "!");
  test_strtok((char[50]){"Hello@world#test$"}, (char[50]){"Hello@world#test$"},
              "@#$");
}
END_TEST

START_TEST(s21_to_upper_test) {
  test_to_upper((char[]){"Hello, World!"}, "HELLO, WORLD!");
  test_to_upper((char[]){"Hello, World! This is a test."},
                "HELLO, WORLD! THIS IS A TEST.");
  test_to_upper((char[]){"Hello, 123!"}, "HELLO, 123!");
  test_to_upper((char[]){"Hello, World! @#$%^&*()"}, "HELLO, WORLD! @#$%^&*()");
  test_to_upper((char[]){"HeLlO, WoRlD!"}, "HELLO, WORLD!");
  test_to_upper((char[]){"Hello, WOr1D! @#$%^&*()"}, "HELLO, WOR1D! @#$%^&*()");
  test_to_upper((char[]){"1234567890"}, "1234567890");
  test_to_upper((char[]){"!@#$%^&*()_+-=[]{}|;:,.<>?/~"},
                "!@#$%^&*()_+-=[]{}|;:,.<>?/~");
  test_to_upper((char[]){"Hello\tworld\ttest"}, "HELLO\tWORLD\tTEST");
  test_to_upper((char[]){"Hello\nworld\ntest"}, "HELLO\nWORLD\nTEST");
  test_to_upper((char[]){"HeLlO, WOr1D! @#$%^&*()"}, "HELLO, WOR1D! @#$%^&*()");
  test_to_upper((char[]){"!@#$%^&*()_+-=[]{}|;:,.<>?/~"},
                "!@#$%^&*()_+-=[]{}|;:,.<>?/~");
  test_to_upper((char[]){""}, "");
  test_to_upper(NULL, NULL);
}
END_TEST

START_TEST(s21_to_lower_test) {
  test_to_lower((char[]){"Hello, World!"}, "hello, world!");
  test_to_lower((char[]){"HelLo, WOrLD!"}, "hello, world!");
  test_to_lower((char[]){"12345"}, "12345");
  test_to_lower((char[]){"!@#$%^&*()"}, "!@#$%^&*()");
  test_to_lower((char[]){"HeLlO, WOr1D!"}, "hello, wor1d!");
  test_to_lower((char[]){"HelLO, WoRLd!"}, "hello, world!");
  test_to_lower((char[]){"Hello, WOr1D! @#$%^&*()"}, "hello, wor1d! @#$%^&*()");
  test_to_lower((char[]){"HeLlO, WOr1D! @#$%^&*()"}, "hello, wor1d! @#$%^&*()");
  test_to_lower((char[]){"Hello\tworld\ttest"}, "hello\tworld\ttest");
  test_to_lower((char[]){"Hello\nworld\ntest"}, "hello\nworld\ntest");
  test_to_lower((char[]){""}, "");
  test_to_lower(NULL, NULL);

  char str[10000];
  char expected[10000];
  for (int i = 0; i < 9999; ++i) {
    str[i] = 'A' + (i % 26);
    expected[i] = 'a' + (i % 26);
  }
  str[9999] = '\0';
  expected[9999] = '\0';

  test_to_lower(str, expected);
}
END_TEST

START_TEST(s21_insert_test) {
  test_insert("World!", "Hello, ", 0, "Hello, World!");
  test_insert("Hello!", " World,", 5, "Hello World,!");
  test_insert("Hello, ", "World!", 7, "Hello, World!");
  test_insert("", "Hello, World!", 0, "Hello, World!");
  test_insert("Hello, ", "World!", 7, "Hello, World!");
  test_insert("Hello, ", "World!", 8, NULL);
  test_insert(NULL, "World!", 7, NULL);
  test_insert("Hello, ", NULL, 7, NULL);
  test_insert("Hello!", "\n\t World,", 5, "Hello\n\t World,!");
  test_insert("Hi", " there, how are you doing today?", 2,
              "Hi there, how are you doing today?");
  test_insert("Hello, how are you?", " fine", 18, "Hello, how are you fine?");
  test_insert("     ", "Hello", 3, "   Hello  ");
  test_insert("Hello", "     ", 3, "Hel     lo");
  test_insert("Hello", "\n\t!", 2, "He\n\t!llo");
  test_insert("Hello", "", 2, "Hello");
}
END_TEST

START_TEST(s21_trim_test) {
  trim_test((char[]){"   Hello, World!"}, (char[]){" "}, "Hello, World!");
  trim_test((char[]){"Hello, World!   "}, (char[]){" "}, "Hello, World!");
  trim_test((char[]){"   Hello, World!   "}, (char[]){" "}, "Hello, World!");
  trim_test((char[]){"----Hello, World!===="}, (char[]){"-="}, "Hello, World!");
  trim_test((char[]){""}, (char[]){" "}, "");
  trim_test(NULL, (char[]){" "}, NULL);
  trim_test((char[]){"---Hello, World!   "}, (char[]){"- "}, "Hello, World!");
  trim_test((char[]){"---Hello---,--- World!---"}, (char[]){"-"},
            "Hello---,--- World!");
  trim_test((char[]){"  \t Hello, World!"}, (char[]){" \t"}, "Hello, World!");
  trim_test((char[]){"Hello, World!   \t  "}, (char[]){" \t"}, "Hello, World!");
  trim_test((char[]){"  \t Hello, World!   \t  "}, (char[]){" \t"},
            "Hello, World!");
  trim_test((char[]){"Hello, World!"}, (char[]){"Helo, Wrld!"}, "");
  trim_test((char[]){"   "}, (char[]){" "}, "");
  trim_test((char[]){"  \t\n Hello, World!"}, (char[]){" \t\n"},
            "Hello, World!");
  trim_test((char[]){"Hello, World!   \t  \n"}, (char[]){" \t\n"},
            "Hello, World!");
  trim_test((char[]){"  \t\n Hello, World!   \t  \n"}, (char[]){" \t\n"},
            "Hello, World!");
}
END_TEST

START_TEST(s21_strncat_test) {
  test_strncat("Hello, ", "world!", 6);
  test_strncat("Hello, ", "", 6);
  test_strncat("", "world!", 6);
  test_strncat("Hello, ", "world!", 0);
  test_strncat("Hello, ", "world!", 10);
  test_strncat("Hello, ", "world!", 3);
  test_strncat("Hello, ", "world!", 6);
  test_strncat("Hello, ", "world!", 7);
  test_strncat("Hello, ", "world!", 5);
  test_strncat("Hello, ", "", 4);
}
END_TEST

START_TEST(s21_strncpy_test) {
  test_strncpy("Hello, world!", 20);
  test_strncpy("Hello, world!", 5);
  test_strncpy("Hello, world!", 0);
  test_strncpy("", 10);
  test_strncpy("Hello, world!", 5);
  test_strncpy("Hello, world!", 13);
  test_strncpy("Hello\0world!", 13);
  test_strncpy("Hello, world!", 13);
  test_strncpy("Привет, мир!", 12);
  test_strncpy("This is a very long source string for testing purposes.", 10);
  test_strncpy("This is a very long source string for testing purposes.", 70);
  test_strncpy("", 0);
  test_strncpy("Hello, world!", 0);
}
END_TEST

Suite *string_suite() {
  Suite *suite = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_sprintf_test_c);
  tcase_add_test(tc_core, s21_sprintf_test_s);
  tcase_add_test(tc_core, s21_sprintf_test_d);
  tcase_add_test(tc_core, s21_sprintf_test_u);
  tcase_add_test(tc_core, s21_sprintf_test_f);
  tcase_add_test(tc_core, s21_sprintf_test_o);
  tcase_add_test(tc_core, s21_sprintf_test_p);
  tcase_add_test(tc_core, s21_sprintf_test_e);
  tcase_add_test(tc_core, s21_sprintf_test_g);
  tcase_add_test(tc_core, s21_sprintf_test_x);
  tcase_add_test(tc_core, s21_memchr_test);
  tcase_add_test(tc_core, s21_memcmp_test);
  tcase_add_test(tc_core, s21_memcpy_test);
  tcase_add_test(tc_core, s21_memset_test);
  tcase_add_test(tc_core, s21_strchr_test);
  tcase_add_test(tc_core, s21_strncmp_test);
  tcase_add_test(tc_core, s21_strcspn_test);
  tcase_add_test(tc_core, s21_strerror_test);
  tcase_add_test(tc_core, s21_strlen_test);
  tcase_add_test(tc_core, s21_strpbrk_test);
  tcase_add_test(tc_core, s21_strrchr_test);
  tcase_add_test(tc_core, s21_strstr_test);
  tcase_add_test(tc_core, s21_strtok_test);
  tcase_add_test(tc_core, s21_to_upper_test);
  tcase_add_test(tc_core, s21_to_lower_test);
  tcase_add_test(tc_core, s21_insert_test);
  tcase_add_test(tc_core, s21_trim_test);
  tcase_add_test(tc_core, s21_strncat_test);
  tcase_add_test(tc_core, s21_strncpy_test);

  suite_add_tcase(suite, tc_core);

  return suite;
}

void run_tests() {
  Suite *suite = string_suite();
  SRunner *sr = srunner_create(suite);

  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}
