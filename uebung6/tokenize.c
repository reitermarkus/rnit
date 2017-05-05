#include "tokenize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void* checked_realloc(void *ptr, size_t size) {
  ptr = realloc(ptr, size);

  if (ptr == NULL) {
    perror("realloc");
    exit(EXIT_FAILURE);
  }

  return ptr;
}

char** tokenize(const char* str, const char* sep, size_t* len) {
  if (!str || !sep || !strlen(str) || !strlen(sep)) {
    return NULL;
  }

  char *string = malloc(strlen(str) + 1);
  strcpy(string, str);

  size_t tokens_len = 0;
  char* token = NULL;
  char** tokens = NULL;

  for (
    token = strtok_r(string, sep, &string);
    token;
    token = strtok_r(NULL, sep, &string)
  ) {
    tokens = checked_realloc(tokens, sizeof(char*) * ++tokens_len);
    tokens[tokens_len - 1] = token;
  }

  tokens = checked_realloc(tokens, sizeof(char*) * (tokens_len + 1));
  tokens[tokens_len] = NULL;

  if (len) {
    *len = tokens_len;
  }

  free(string);
  return tokens;
}
