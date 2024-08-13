#include "s21_string.h"

// S21_SPRINTF

int s21_sprintf(char *str, const char *format, ...) {
  int length = 0;
  char ch;

  va_list args;
  va_start(args, format);

  while ((ch = *format++)) {
    if (ch == '%') {
      format_option opts = {.width = 0,
                            .precision = -1,
                            .length = '\0',
                            .left_justify = 0,
                            .show_sign = 0,
                            .space_sign = 0,
                            .alternate_form = 0,
                            .zero_pad = 0,
                            .specifier = '\0'};

      parse_format_options(&format, &opts, &args);

      switch (opts.specifier) {
        case 'c':
          handle_specifier_c(&str, &opts, args, &length);
          break;
        case 's':
          handle_specifier_s(&str, &opts, args, &length);
          break;
        case 'd':
          handle_specifier_d(&str, &opts, args, &length);
          break;
        case 'u':
          handle_specifier_u(&str, &opts, args, &length);
          break;
        case 'f':
          handle_specifier_f(&str, &opts, args, &length);
          break;
        case 'o':
          handle_specifier_o(&str, &opts, args, &length);
          break;
        case 'p':
          handle_specifier_p(&str, &opts, args, &length);
          break;
        case 'e':
        case 'E':
          handle_specifier_e(&str, &opts, args, &length);
          break;
        case 'g':
        case 'G':
          handle_specifier_g(&str, &opts, args, &length);
          break;
        case 'x':
        case 'X':
          handle_specifier_x(&str, &opts, args, &length);
          break;
        case '%':
          *str++ = ch;
          length++;
          break;
        default:
          break;
      }
    } else {
      *str++ = ch;
      length++;
    }
  }
  *str = '\0';

  va_end(args);

  return length;
}

// S21_MEMCHR

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *ptr = (const char *)str;
  char val = (char)c;

  for (s21_size_t i = 0; i < n; ++i) {
    if (ptr[i] == val) {
      return (void *)(ptr + i);
    }
  }
  return s21_NULL;
}

// S21_MEMCMP

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *p1 = (const char *)str1;
  const char *p2 = (const char *)str2;

  for (s21_size_t i = 0; i < n; ++i) {
    if (p1[i] != p2[i]) {
      return (int)(p1[i] - p2[i]);
    }
  }
  return 0;
}

// S21_MEMCPY

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *d = (char *)dest;
  const char *s = (const char *)src;

  for (s21_size_t i = 0; i < n; ++i) {
    d[i] = s[i];
  }

  return dest;
}

// S21_MEMSET

void *s21_memset(void *str, int c, s21_size_t n) {
  char *p = (char *)str;
  char val = (char)c;

  for (s21_size_t i = 0; i < n; ++i) {
    p[i] = val;
  }

  return str;
}

// S21_STRNCAT

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (*ptr != '\0') {
    ptr++;
  }

  while (*src != '\0' && n > 0) {
    *ptr = *src;
    ptr++;
    src++;
    n--;
  }

  *ptr = '\0';

  return dest;
}

// S21_STRCHR

char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == (char)c) {
      return (char *)str;
    }
    str++;
  }

  if (c == '\0') {
    return (char *)str;
  }

  return s21_NULL;
}

// S21_STRNCMP

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  while (n > 0 && (*str1 != '\0' || *str2 != '\0')) {
    if (*str1 != *str2) {
      return (unsigned char)*str1 - (unsigned char)*str2;
    }
    str1++;
    str2++;
    n--;
  }

  return 0;
}

// S21_STRNCPY

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (n > 0 && *src != '\0') {
    *ptr++ = *src++;
    n--;
  }

  while (n > 0) {
    *ptr++ = '\0';
    n--;
  }

  return dest;
}

// S21_STRCSPN

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p1, *p2;

  for (p1 = str1; *p1 != '\0'; p1++) {
    for (p2 = str2; *p2 != '\0'; p2++) {
      if (*p1 == *p2) {
        return p1 - str1;
      }
    }
  }

  return p1 - str1;
}

// S21_STRERROR

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

static const char *error_list[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

static const char *error_list[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

char *s21_strerror(int errnum) {
  char *ptr = s21_NULL;
  static char part1[SIZE];
  static char part2[SIZE];

  part1[0] = '\0';

  if (errnum >= MAX_ERRLIST || errnum <= MIN_ERRLIST) {
    s21_strcat(part1, ERROR);
    s21_errnum_tostring(part2, errnum);
    s21_strcat(part1, part2);
    ptr = part1;
  } else {
    ptr = (char *)error_list[errnum];
  }
  return (char *)ptr;
}

void s21_errnum_tostring(char *str, int num) {
  int is_negative = 0;
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }
  int i = 0;
  while (num != 0) {
    str[i++] = (num % 10) + '0';
    num /= 10;
  }
  if (is_negative) {
    str[i++] = '-';
  }
  str[i] = '\0';
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}

char *s21_strcat(char *dest, const char *src) {
  int len = 0;
  while (*dest) {
    dest++;
    len++;
  }
  while (*src) {
    *dest = *src;
    dest++;
    src++;
    len++;
  }
  *dest = '\0';
  dest -= len;
  return dest;
}

// S21_STRLEN

s21_size_t s21_strlen(const char *str) {
  char *p = (char *)str;
  s21_size_t len = 0;
  if (p == s21_NULL) {
    return -1;
  }
  while (*p != '\0') {
    p++;
    len++;
  }
  return len;
}

// S21_STRPBRK

char *s21_strpbrk(const char *str1, const char *str2) {
  for (const char *p1 = str1; *p1 != '\0'; p1++) {
    for (const char *p2 = str2; *p2 != '\0'; p2++) {
      if (*p1 == *p2) {
        return (char *)p1;
      }
    }
  }
  return s21_NULL;
}

// S21_STRRCHR

char *s21_strrchr(const char *str, int c) {
  const char *last_occurrence = s21_NULL;

  for (; *str != '\0'; str++) {
    if (*str == (char)c) {
      last_occurrence = str;
    }
  }

  if (c == '\0') {
    return (char *)str;
  }

  return (char *)last_occurrence;
}

// S21_STRSTR

char *s21_strstr(const char *haystask, const char *needle) {
  s21_size_t l1, l2;

  l2 = s21_strlen(needle);
  if (!l2) return (char *)haystask;
  l1 = s21_strlen(haystask);
  while (l1 >= l2) {
    l1--;
    if (!s21_check_mem(haystask, needle, l2)) return (char *)haystask;
    haystask++;
  }
  return s21_NULL;
}

int s21_check_mem(const char *str1, const char *str2, int n) {
  int res = 0;
  for (int i = 0; i < n; i++, str1++, str2++) {
    if (*str1 != *str2) {
      res = 1;
      break;
    }
  }

  return res;
}

// S21_STRTOK

char *s21_strtok(char *str, const char *delim) {
  static char *remaining_str = s21_NULL;
  char *token_start;

  if (str != s21_NULL) {
    remaining_str = str;
  } else if (remaining_str == s21_NULL) {
    return s21_NULL;
  }

  while (*remaining_str != '\0' &&
         s21_strchr(delim, *remaining_str) != s21_NULL) {
    remaining_str++;
  }

  if (*remaining_str == '\0') {
    return s21_NULL;
  }

  token_start = remaining_str;
  while (*remaining_str != '\0' &&
         s21_strchr(delim, *remaining_str) == s21_NULL) {
    remaining_str++;
  }

  if (*remaining_str == '\0') {
    remaining_str = s21_NULL;
  } else {
    *remaining_str = '\0';
    remaining_str++;
  }

  return token_start;
}

// S21_TO_UPPER

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc((len + 1) * sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }

  for (size_t i = 0; i < len; i++) {
    result[i] = to_upper_char(str[i]);
  }
  result[len] = '\0';

  return result;
}

char to_upper_char(char ch) {
  if (ch >= 'a' && ch <= 'z') {
    return ch - ('a' - 'A');
  }
  return ch;
}

// S21_TO_LOWER

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc((len + 1) * sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }

  for (size_t i = 0; i < len; i++) {
    result[i] = to_lower_char(str[i]);
  }
  result[len] = '\0';

  return result;
}

char to_lower_char(char ch) {
  if (ch >= 'A' && ch <= 'Z') {
    return ch + ('a' - 'A');
  }
  return ch;
}

// S21_INSERT

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) {
    return s21_NULL;
  }

  size_t new_len = src_len + str_len;
  char *result = (char *)malloc((new_len + 1) * sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }

  s21_strncpy(result, src, start_index);
  s21_strcpy(result + start_index, str);
  s21_strcpy(result + start_index + str_len, src + start_index);

  result[new_len] = '\0';

  return result;
}

void s21_strcpy(char *dest, const char *src) {
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';
}

// S21_TRIM

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t start = 0;
  s21_size_t end = s21_strlen(src);

  int is_trim_char[256] = {0};
  for (s21_size_t i = 0; trim_chars[i] != '\0'; i++) {
    is_trim_char[(unsigned char)trim_chars[i]] = 1;
  }

  while (start < end && is_trim_char[(unsigned char)src[start]]) {
    start++;
  }
  while (end > start && is_trim_char[(unsigned char)(src[end - 1])]) {
    end--;
  }

  s21_size_t len = end - start;
  char *result = (char *)malloc((len + 1) * sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }

  for (s21_size_t i = 0; i < len; i++) {
    result[i] = src[start + i];
  }
  result[len] = '\0';

  return result;
}
