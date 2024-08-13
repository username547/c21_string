#include "s21_string.h"

void handle_specifier_c(char **str, format_option *opts, va_list args,
                        int *length) {
  char c = (char)va_arg(args, int);

  if (opts->left_justify) {
    *(*str)++ = c;
    (*length)++;
    for (int i = 1; i < opts->left_justify; i++) {
      *(*str)++ = ' ';
      (*length)++;
    }
  } else {
    for (int i = 1; i < opts->width; i++) {
      *(*str)++ = ' ';
      (*length)++;
    }
    *(*str)++ = c;
    (*length)++;
  }
}

void handle_specifier_s(char **str, format_option *opts, va_list args,
                        int *length) {
  char *s = va_arg(args, char *);

  if (s == NULL) {
    s = "(null)";
  }

  int len = s21_strlen(s);

  if (opts->precision >= 0 && opts->precision < len) {
    len = opts->precision;
  }

  char temp_str[SIZE];
  s21_memcpy(temp_str, s, len);
  temp_str[len] = '\0';

  int total_len = len;
  if (opts->width > len) {
    total_len = opts->width;
  }

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, len, opts);
  } else {
    char pad_char = ' ';
    add_padding(str, temp_str, len, total_len, pad_char);
  }

  *length += total_len;
}

void handle_specifier_d(char **str, format_option *opts, va_list args,
                        int *length) {
  long int n = extract_arg_d(opts, args);
  char sign = process_sign_d(&n, opts);
  char temp_str[SIZE];
  int temp_len = 0;
  int total_len = 0;

  int_to_str(n, temp_str, &temp_len);
  while (temp_len < opts->precision) temp_str[(temp_len)++] = '0';
  reverse_str(temp_str, temp_len);

  total_len = add_sign_dfeg(temp_str, &temp_len, sign, opts);

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = (opts->zero_pad && opts->precision < 0) ? '0' : ' ';
    if (opts->zero_pad && sign) {
      **str = sign;
      (*str)++;
      for (int i = temp_len; i < total_len; i++) {
        **str = pad_char;
        (*str)++;
      }
      s21_memcpy(*str, temp_str + 1, temp_len - 1);
      *str += temp_len - 1;
    } else {
      add_padding(str, temp_str, temp_len, total_len, pad_char);
    }
  }
  *length += total_len;
}

long int extract_arg_d(format_option *opts, va_list args) {
  long int n;
  if (opts->length == 'h') {
    n = (short int)va_arg(args, int);
  } else if (opts->length == 'l') {
    n = va_arg(args, long int);
  } else {
    n = va_arg(args, int);
  }
  return n;
}

char process_sign_d(long int *n, format_option *opts) {
  char sign = 0;
  if (*n < 0) {
    sign = '-';
    *n = -*n;
  } else if (opts->show_sign) {
    sign = '+';
  } else if (opts->space_sign) {
    sign = ' ';
  }
  return sign;
}

void handle_specifier_u(char **str, format_option *opts, va_list args,
                        int *length) {
  unsigned long long int u = extract_arg_uox(opts, args);
  char temp_str[SIZE];
  int temp_len = 0;

  uint_to_str(u, temp_str, &temp_len);

  while (temp_len < opts->precision) temp_str[temp_len++] = '0';

  reverse_str(temp_str, temp_len);

  int total_len = temp_len;
  if (opts->width > temp_len) {
    total_len = opts->width;
  }

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = (opts->zero_pad && opts->precision < 0) ? '0' : ' ';
    add_padding(str, temp_str, temp_len, total_len, pad_char);
  }
  *length += total_len;
}

void handle_specifier_f(char **str, format_option *opts, va_list args,
                        int *length) {
  long double value = extract_arg_feg(opts, args);
  char sign = process_sign_feg(&value, opts);
  char temp_str[SIZE];
  int temp_len = process_special_values_f(value, opts, &sign, temp_str);
  int total_len = add_sign_dfeg(temp_str, &temp_len, sign, opts);

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = opts->zero_pad ? '0' : ' ';
    if (opts->zero_pad && sign) {
      **str = sign;
      (*str)++;
      for (int i = temp_len; i < total_len; i++) {
        **str = pad_char;
        (*str)++;
      }
      s21_memcpy(*str, temp_str + 1, temp_len - 1);
      *str += temp_len - 1;
    } else {
      add_padding(str, temp_str, temp_len, total_len, pad_char);
    }
  }
  *length += total_len;
}

int process_special_values_f(long double value, format_option *opts, char *sign,
                             char *temp_str) {
  int temp_len = 0;

  if (isnan(value)) {
    opts->zero_pad = 0;
    s21_strcpy(temp_str, "nan");
    temp_len = 3;
  } else if (isinf(value)) {
    opts->zero_pad = 0;
    if (value < 0) {
      s21_strcpy(temp_str, "-inf");
      temp_len = 4;
    } else {
      s21_strcpy(temp_str, "inf");
      temp_len = 3;
    }
    *sign = '\0';
  } else {
    if (opts->precision == -1) opts->precision = 6;
    double_to_str(value, temp_str, &temp_len, opts);
  }
  return temp_len;
}

void handle_specifier_o(char **str, format_option *opts, va_list args,
                        int *length) {
  char temp_str[SIZE];
  int temp_len = 0;

  unsigned long long int n = extract_arg_uox(opts, args);

  uint_to_octal_str(n, temp_str, &temp_len);

  if (opts->alternate_form && n != 0) {
    for (int i = temp_len; i > 0; i--) {
      temp_str[i] = temp_str[i - 1];
    }
    temp_str[0] = '0';
    temp_len++;
  }

  while (temp_len < opts->precision) {
    for (int i = temp_len; i > 0; i--) {
      temp_str[i] = temp_str[i - 1];
    }
    temp_str[0] = '0';
    temp_len++;
  }

  int total_len = temp_len;
  if (opts->width > total_len) {
    total_len = opts->width;
  }

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = (opts->zero_pad && opts->precision < 0) ? '0' : ' ';
    add_padding(str, temp_str, temp_len, total_len, pad_char);
  }
  *length += total_len;
}

void handle_specifier_p(char **str, format_option *opts, va_list args,
                        int *length) {
  void *ptr = va_arg(args, void *);
  char temp_str[SIZE];
  int temp_len = 0;

  pointer_to_hex_str(ptr, temp_str, &temp_len, opts);

  int total_len = temp_len;
  if (opts->width > total_len) {
    total_len = opts->width;
  }

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = (opts->zero_pad) ? '0' : ' ';
    add_padding(str, temp_str, temp_len, total_len, pad_char);
  }
  *length += total_len;
}

void handle_specifier_e(char **str, format_option *opts, va_list args,
                        int *length) {
  long double value = extract_arg_feg(opts, args);
  char sign = process_sign_feg(&value, opts);
  char temp_str[SIZE];
  int temp_len = process_special_values_e(value, opts, temp_str);
  int total_len = add_sign_dfeg(temp_str, &temp_len, sign, opts);

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = opts->zero_pad ? '0' : ' ';
    if (opts->zero_pad && sign) {
      **str = sign;
      (*str)++;
      for (int i = temp_len; i < total_len; i++) {
        **str = pad_char;
        (*str)++;
      }
      s21_memcpy(*str, temp_str + 1, temp_len - 1);
      *str += temp_len - 1;
    } else {
      add_padding(str, temp_str, temp_len, total_len, pad_char);
    }
  }
  *length += total_len;
}

int process_special_values_e(long double value, format_option *opts,
                             char *temp_str) {
  int temp_len = 0;

  if (isnan(value)) {
    opts->zero_pad = 0;
    opts->specifier == 'e' ? s21_strcpy(temp_str, "nan")
                           : s21_strcpy(temp_str, "NAN");
    temp_len += 3;
  } else if (isinf(value)) {
    if (value < 0) {
      opts->specifier == 'e' ? s21_strcpy(temp_str, "-inf")
                             : s21_strcpy(temp_str, "-INF");
      temp_len += 4;
    } else {
      opts->specifier == 'e' ? s21_strcpy(temp_str, "inf")
                             : s21_strcpy(temp_str, "INF");
      temp_len += 3;
    }
  } else {
    if (opts->precision == -1) opts->precision = 6;
    double_to_exp_str(value, temp_str + temp_len, opts);
    temp_len += s21_strlen(temp_str + temp_len);
  }
  return temp_len;
}

void handle_specifier_g(char **str, format_option *opts, va_list args,
                        int *length) {
  long double value = extract_arg_feg(opts, args);
  char sign = process_sign_feg(&value, opts);
  char temp_str[SIZE];
  int temp_len = process_special_values_g(value, opts, temp_str);
  int total_len = add_sign_dfeg(temp_str, &temp_len, sign, opts);

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = opts->zero_pad ? '0' : ' ';
    if (opts->zero_pad && sign) {
      **str = sign;
      (*str)++;
      for (int i = temp_len; i < total_len; i++) {
        **str = pad_char;
        (*str)++;
      }
      s21_memcpy(*str, temp_str + 1, temp_len - 1);
      *str += temp_len - 1;
    } else {
      add_padding(str, temp_str, temp_len, total_len, pad_char);
    }
  }
  *length += total_len;
}

int process_special_values_g(long double value, format_option *opts,
                             char *temp_str) {
  int temp_len = 0;

  if (isnan(value)) {
    opts->specifier == 'g' ? s21_strcpy(temp_str, "nan")
                           : s21_strcpy(temp_str, "NAN");
    temp_len = 3;
  } else if (isinf(value)) {
    if (value < 0) {
      opts->specifier == 'g' ? s21_strcpy(temp_str, "-inf")
                             : s21_strcpy(temp_str, "-INF");
      temp_len = 4;
    } else {
      opts->specifier == 'g' ? s21_strcpy(temp_str, "inf")
                             : s21_strcpy(temp_str, "INF");
      temp_len = 3;
    }
  } else {
    if (opts->precision == -1) opts->precision = 6;
    double_to_str_g(value, temp_str, &temp_len, opts);
  }
  return temp_len;
}

void handle_specifier_x(char **str, format_option *opts, va_list args,
                        int *length) {
  char temp_str[SIZE];
  int temp_len = 0;
  unsigned long long int value = extract_arg_uox(opts, args);

  uint_to_hex_str(value, temp_str, &temp_len, opts);
  process_precision_x(temp_str, &temp_len, opts->precision);

  if (opts->alternate_form && value != 0) {
    process_alternate_form_x(temp_str, &temp_len, opts->specifier);
  }

  int total_len = temp_len;
  if (opts->width > total_len) {
    total_len = opts->width;
  }

  if (opts->left_justify) {
    total_len += add_left_justify(str, temp_str, temp_len, opts);
  } else {
    char pad_char = (opts->zero_pad && opts->precision < 0) ? '0' : ' ';
    if (opts->zero_pad && opts->precision < 0 && opts->alternate_form &&
        value != 0) {
      **str = '0';
      *(*str + 1) = opts->specifier;
      *str += 2;
      for (int i = temp_len; i < total_len; i++) {
        **str = pad_char;
        (*str)++;
      }
      s21_memcpy(*str, temp_str + 2, temp_len - 2);
      *str += temp_len - 2;
    } else {
      add_padding(str, temp_str, temp_len, total_len, pad_char);
    }
  }
  *length += total_len;
}

void process_precision_x(char *temp_str, int *temp_len, int precision) {
  if (precision > *temp_len) {
    int precision_diff = precision - *temp_len;
    for (int i = *temp_len - 1; i >= 0; i--) {
      temp_str[i + precision_diff] = temp_str[i];
    }
    for (int i = 0; i < precision_diff; i++) {
      temp_str[i] = '0';
    }
    *temp_len = precision;
  }
}

void process_alternate_form_x(char *temp_str, int *temp_len, char specifier) {
  for (int i = *temp_len - 1; i >= 0; i--) {
    temp_str[i + 2] = temp_str[i];
  }
  temp_str[0] = '0';
  temp_str[1] = specifier;
  *temp_len += 2;
}

unsigned long int extract_arg_uox(format_option *opts, va_list args) {
  unsigned long int value;
  if (opts->length == 'h') {
    value = (unsigned short int)va_arg(args, unsigned int);
  } else if (opts->length == 'l') {
    value = va_arg(args, unsigned long int);
  } else {
    value = va_arg(args, unsigned int);
  }
  return value;
}

long double extract_arg_feg(format_option *opts, va_list args) {
  long double value;
  if (opts->length == 'L') {
    value = va_arg(args, long double);
  } else {
    value = va_arg(args, double);
  }
  return value;
}

char process_sign_feg(long double *value, format_option *opts) {
  char sign = 0;
  if (*value < 0) {
    sign = '-';
    *value = -*value;
  } else if (opts->show_sign) {
    sign = '+';
  } else if (opts->space_sign) {
    sign = ' ';
  }
  return sign;
}

int add_sign_dfeg(char *temp_str, int *temp_len, char sign,
                  format_option *opts) {
  if (sign) {
    for (int i = *temp_len; i > 0; i--) {
      temp_str[i] = temp_str[i - 1];
    }
    temp_str[0] = sign;
    (*temp_len)++;
  }
  int total_len = *temp_len;
  if (opts->width > *temp_len) {
    total_len = opts->width;
  }
  return total_len;
}

int add_left_justify(char **str, const char *temp_str, int temp_len,
                     format_option *opts) {
  s21_memcpy(*str, temp_str, temp_len);
  *str += temp_len;
  for (int i = temp_len; i < opts->left_justify; i++) {
    *(*str)++ = ' ';
  }
  int diff = opts->left_justify - temp_len;
  return (diff < 0) ? 0 : diff;
}

void add_padding(char **str, char *temp_str, int temp_len, int total_len,
                 char pad_char) {
  for (int i = temp_len; i < total_len; i++) {
    **str = pad_char;
    (*str)++;
  }
  s21_memcpy(*str, temp_str, temp_len);
  *str += temp_len;
}
