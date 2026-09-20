#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>
// HASH FUNCTION
static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

int main(void) {
    char *key = false;
    printf("%ld", string_knr_hash(key));
}

