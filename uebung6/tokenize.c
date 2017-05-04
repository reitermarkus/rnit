#include "tokenize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (!(tokens = realloc(tokens, sizeof(char*) * (++tokens_len)))) {
      perror("realloc");
      exit(EXIT_FAILURE);
    }

    tokens[tokens_len - 1] = token;
  }

  if (!(tokens = realloc(tokens, sizeof(char*) * (tokens_len + 1)))) {
    perror("realloc");
    exit(EXIT_FAILURE);
  }

  tokens[tokens_len] = NULL;

  if (len) {
    *len = tokens_len;
  }

  free(string);
  return tokens;
}
