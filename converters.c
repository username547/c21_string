#include "s21_string.h"

void int_to_str(long long int n, char *str, int *len) {
  do {
    str[(*len)++] = (n % 10) + '0';
    n /= 10;
  } while (n != 0);
}

void uint_to_str(unsigned long long int n, char *str, int *len) {
  do {
    str[(*len)++] = (n % 10) + '0';
    n /= 10;
  } while (n != 0);
}

void double_to_str(long double n, char *str, int *len, format_option *opts) {
  long long int integer_part = (long long int)n;
  int integer_len = 0;
  int_to_str(integer_part, str, &integer_len);
  reverse_str(str, integer_len);

  *len += integer_len;

  if (opts->precision > 0 || opts->alternate_form) {
    str[(*len)++] = '.';
  }

  if (opts->precision > 0) {
    long double fraction_part = n - integer_part;

    for (int i = 0; i < opts->precision; i++) {
      fraction_part *= 10;
      int digit = (int)fraction_part;
      str[(*len)++] = digit + '0';
      fraction_part -= digit;
    }

    if ((int)(fraction_part * 10) >= 5) {
      for (int i = *len - 1; i >= 0; i--) {
        if (str[i] == '.') continue;
        if (str[i] < '9') {
          str[i]++;
          break;
        } else {
          str[i] = '0';
          if (i == 0) {
            for (int j = *len; j > 0; j--) {
              str[j] = str[j - 1];
            }
            str[0] = '1';
            (*len)++;
          }
        }
      }
    }
  }
}

void pointer_to_hex_str(void *ptr, char *str, int *len, format_option *opts) {
  if (ptr == s21_NULL) {
    s21_strcpy(str, "(nil)");
    *len = 5;
  } else {
    uintptr_t value = (uintptr_t)ptr;
    int buf_len = 0;
    int temp_len = 0;
    char temp[SIZE];

    str[buf_len++] = '0';
    str[buf_len++] = 'x';

    if (value == 0) {
      str[buf_len++] = '0';
    } else {
      while (value != 0) {
        int digit = value % 16;
        temp[temp_len++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
        value /= 16;
      }
      while (temp_len < opts->precision) {
        temp[temp_len++] = '0';
      }
      for (int i = temp_len - 1; i >= 0; i--) {
        str[buf_len++] = temp[i];
      }
    }
    *len = buf_len;
    str[buf_len] = '\0';
  }
}

void uint_to_octal_str(unsigned long long int n, char *str, int *len) {
  *len = 0;

  if (n == 0) {
    str[*len] = '0';
    (*len)++;
    str[*len] = '\0';
    return;
  }

  while (n > 0) {
    str[*len] = (n % 8) + '0';
    n /= 8;
    (*len)++;
  }

  str[*len] = '\0';
  for (int i = 0; i < *len / 2; i++) {
    char temp = str[i];
    str[i] = str[*len - i - 1];
    str[*len - i - 1] = temp;
  }
}

void double_to_exp_str(long double value, char *str, format_option *opts) {
  int exponent = 0;
  int sign = (value < 0) ? -1 : 1;
  value = (sign < 0) ? -value : value;

  if (value != 0.0) {
    while (value >= 10.0) {
      value /= 10.0;
      exponent++;
    }
    while (value < 1.0) {
      value *= 10.0;
      exponent--;
    }
  }

  int mantissa_len = 0;
  double_to_str(value, str, &mantissa_len, opts);

  char exp[10];
  int exp_len = 0;
  exp[exp_len++] = opts->specifier;
  exp[exp_len++] = (exponent < 0) ? '-' : '+';
  exponent = (exponent < 0) ? -exponent : exponent;

  int hundreds = exponent / 100;
  int tens = (exponent / 10) % 10;
  int ones = exponent % 10;

  if (hundreds > 9) {
    exp[exp_len++] = (hundreds / 10) + '0';
    exp[exp_len++] = (hundreds % 10) + '0';
  } else if (hundreds > 0) {
    exp[exp_len++] = hundreds + '0';
  }
  exp[exp_len++] = tens + '0';
  exp[exp_len++] = ones + '0';
  exp[exp_len] = '\0';

  // printf("TEST [%s] hundreds: [%d], tens: [%d], ones: [%d]\n", exp, hundreds,
  // tens, ones);

  s21_strcpy(str + mantissa_len, exp);
}

void double_to_str_g(long double n, char *str, int *len, format_option *opts) {
  *len = 0;

  if (n == 0.0) {
    handle_zero_value(str, len, opts);
    return;
  }

  int exp_rep = 0;
  int exponent = 0;
  long double abs_n = fabsl(n);

  if (abs_n < 1e-4 || abs_n >= pow(10, opts->precision)) {
    exp_rep = 1;
    // exponent = (int)log10(abs_n);
    exponent = (int)floor(log10(abs_n));
    n /= pow(10, exponent);
  } else {
    opts->precision -= (int)(ceil(log10(abs_n)));
  }

  if (!exp_rep) {
    format_normal(n, str, len, opts);
  } else {
    format_exponential(n, str, len, opts, exponent);
  }
}

void handle_zero_value(char *str, int *len, format_option *opts) {
  if (!opts->alternate_form && opts->precision > 0) {
    s21_strcpy(str, "0");
    *len = 1;
  } else {
    s21_strcpy(str, "0.");
    *len = 2;
    for (int i = 0; i < opts->precision - 1; i++) {
      str[(*len)++] = '0';
    }
    str[*len] = '\0';
  }
}

void format_normal(long double n, char *str, int *len, format_option *opts) {
  long long int int_part = (long long int)n;
  long double frac_part = fabsl(n - int_part);

  int int_len = 0;
  int_to_str(int_part, str, &int_len);
  reverse_str(str, int_len);
  *len = int_len;

  if (opts->precision > 0) {
    str[(*len)++] = '.';
    for (int i = 0; i < opts->precision; i++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      str[(*len)++] = digit + '0';
      frac_part -= digit;
    }

    if (frac_part >= 0.5) {
      str[*len - 1]++;
      round_fraction(str, len);
    }

    if (!opts->alternate_form) {
      while (*len > 0 && str[*len - 1] == '0') {
        (*len)--;
      }
      if (*len > 0 && str[*len - 1] == '.') {
        (*len)--;
      }
    }
  } else {
    if (opts->alternate_form) {
      str[(*len)++] = '.';
    }
  }

  str[*len] = '\0';
}

void format_exponential(long double n, char *str, int *len, format_option *opts,
                        int exponent) {
  if (n < 0) {
    str[(*len)++] = '-';
    n = -n;
  }

  int int_part = (int)n;
  long double frac_part = n - int_part;

  int int_len = 0;
  int_to_str(int_part, str + *len, &int_len);
  reverse_str(str + *len, int_len);
  *len += int_len;

  if (opts->precision > 1 || opts->alternate_form) {
    str[(*len)++] = '.';
    for (int i = 0; i < opts->precision - 1; i++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      str[(*len)++] = digit + '0';
      frac_part -= digit;
    }

    if (frac_part >= 0.5) {
      str[*len - 1]++;
      round_fraction(str, len);
    }
  }

  str[(*len)++] = opts->specifier == 'g' ? 'e' : 'E';
  if (exponent >= 0) {
    str[(*len)++] = '+';
  } else {
    str[(*len)++] = '-';
    exponent = -exponent;
  }

  if (exponent < 10) {
    str[(*len)++] = '0';
  }

  int exp_len = 0;
  int_to_str(exponent, str + *len, &exp_len);
  reverse_str(str + *len, exp_len);
  *len += exp_len;
  str[*len] = '\0';
}

void uint_to_hex_str(unsigned long long int num, char *str, int *len,
                     format_option *opts) {
  const char *digits =
      opts->specifier == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
  char temp[SIZE];
  int i = 0;

  if (num == 0) {
    temp[i++] = '0';
  } else {
    while (num > 0) {
      temp[i++] = digits[num % 16];
      num /= 16;
    }
  }

  for (int j = 0; j < i; j++) {
    str[j] = temp[i - j - 1];
  }
  *len = i;
}

void round_fraction(char *str, int *len) {
  for (int i = *len - 1; i > 0; i--) {
    if (str[i] > '9') {
      str[i] = '0';
      str[i - 1]++;
    } else {
      break;
    }
  }
}

void reverse_str(char *str, int len) {
  for (int i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = temp;
  }
}
