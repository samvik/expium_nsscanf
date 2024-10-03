#include "nsscanf.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum
{
  STATE_IDLE,
  STATE_TOKEN,
  STATE_ESCAPE
} expium_nsscanf_state;

static bool is_digit(char c)
{
  return c >= '0' && c <= '9';
}

static bool is_white_space(char c)
{
  switch(c)
  {
    case ' ':
    case '\f':
    case '\n':
    case '\r':
    case '\t':
    case '\v':
      return true;
    default:
      return false;
  }
}

static bool read_unsigned(const char **str, unsigned *value)
{
  const char *s = *str;
  *value = 0;
  while(is_digit(*s))
  {
    *value *= 10;
    *value += (*s++ - '0');
  }
  *str = s;
  return true;
}

static bool read_signed(const char **str, int *value)
{
  const char *s = *str;

  int sign = 1;
  if(*s == '-')
  {
    sign = -1;
    ++s;
  }

  unsigned v;
  if(!read_unsigned(&s, &v))
  {
    return false;
  }

  *value = sign * v;
  *str = s;
  return true;
}

static bool read_string(const char **str, char *value)
{
  const char *s = *str;
  *value = 0;
  while(!is_white_space(*s))
  {
    *value++ = *s++;
  }
  *value = '\0';
  *str = s;
  return true;
}

int expium_nsscanf(const char *str, const char *format, ...)
{
  int count = 0;
  expium_nsscanf_state state = STATE_IDLE;

  va_list va;
  va_start(va, format);

  while(*format && *str)
  {
    switch(state)
    {
      case STATE_IDLE:
        switch(*format)
        {
          case '%':
            state = STATE_TOKEN;
            break;
          case '\\':
            state = STATE_ESCAPE;
            break;
          default:
            if(*format != *str)
            {
              goto DONE;
            }
            ++str;
            break;
        }
        break;
      case STATE_ESCAPE:
        if(*format != *str)
        {
          goto DONE;
        }
        ++str;
        state = STATE_IDLE;
        break;
      case STATE_TOKEN:
        switch(*format)
        {
#if EXPIUM_NSSCANF_ENABLE_INT
          case 'd':
          {
            int value;
            if(!read_signed(&str, &value))
            {
              goto DONE;
            }
            *(int *)va_arg(va, int *) = value;
            ++count;
            break;
          }
#endif
#if EXPIUM_NSSCANF_ENABLE_UNSIGNED
          case 'u':
          {
            unsigned value;
            if(!read_unsigned(&str, &value))
            {
              goto DONE;
            }
            *(unsigned *)va_arg(va, unsigned *) = value;
            ++count;
            break;
          }
#endif
#if EXPIUM_NSSCANF_ENABLE_STRING
          case 's':
          {
            char *value = (char *)va_arg(va, char *);
            if(!read_string(&str, value))
            {
              goto DONE;
            }
            ++count;
            break;
          }
#endif
        }
        state = STATE_IDLE;
        break;
    }

    ++format;
  }

DONE:
  va_end(va);
  return count;
}