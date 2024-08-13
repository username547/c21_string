#include "s21_string.h"

void parse_format_options(const char **format, format_option *opts,
                          va_list *args) {
  int check_dash = 0, check_dot = 0;
  char ch;
  while ((ch = *(*format)++)) {
    switch (ch) {
      case '+':
        opts->show_sign = 1;
        break;
      case '-':
        check_dash = 1;
        break;
      case ' ':
        opts->space_sign = 1;
        break;
      case '#':
        opts->alternate_form = 1;
        break;
      case '0':
        if (!check_dot)
          opts->zero_pad = 1;
        else if (check_dot)
          opts->precision = 0;
        break;
      case '.':
        check_dot = 1;
        break;
      case '*':
        if (opts->precision == -1 && check_dot)
          opts->precision = va_arg(*args, int);
        else if (!opts->left_justify && check_dash)
          opts->left_justify = va_arg(*args, int);
        else if (!opts->width && !check_dash)
          opts->width = va_arg(*args, int);
        break;
      case 'h':
      case 'l':
      case 'L':
        opts->length = ch;
        break;
      case 'c':
      case 's':
      case 'd':
      case 'u':
      case 'f':
      case 'o':
      case 'p':
      case 'e':
      case 'E':
      case 'g':
      case 'G':
      case 'x':
      case 'X':
      case '%':
        opts->specifier = ch;
        if ((opts->left_justify) ||
            (opts->precision >= 0 &&
             (opts->specifier != 'f' && opts->specifier != 'e' &&
              opts->specifier != 'E' && opts->specifier != 'g' &&
              opts->specifier != 'G' && opts->specifier != 'x' &&
              opts->specifier != 'X')))
          opts->zero_pad = 0;
        return;
      default:
        if (ch >= '0' && ch <= '9') {
          int value = 0;
          do {
            value = value * 10 + (ch - '0');
            ch = *(*format)++;
          } while (ch >= '0' && ch <= '9');
          --(*format);
          if (opts->precision == -1 && check_dot)
            opts->precision = value;
          else if (!opts->left_justify && check_dash)
            opts->left_justify = value;
          else if (!opts->width && !check_dash)
            opts->width = value;
        }
        break;
    }
  }
}
