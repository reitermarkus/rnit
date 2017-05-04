#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <sys/types.h> // struct sockaddr
#include <sys/socket.h>


#include <arpa/inet.h> // htons

#include <netdb.h>

// #include <netinet/ip.h>
#include <netinet/in.h> // IPPROTO_RAW, IPPROTO_IP, IPPROTO_TCP, INET_ADDRSTRLEN


#include <errno.h>

#include "load_file.h"
#include "tokenize.h"

const char* PORT = "5000";
const char* HOSTNAME = "localhost";

int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: %s\n", "Exactly one file must be specified.");
    exit(EXIT_FAILURE);
  }

  const char* file_content = load_file(argv[1]);

  size_t line_count;
  char** lines = tokenize(file_content, "\n", &line_count);

  printf("%ld lines\n", line_count);

  for (size_t i = 0; i < line_count; i++) {
    printf("line %ld:\n", i);

    size_t token_count;
    char** tokens = tokenize(lines[i], " ", &token_count);

    for (size_t j = 0; j < token_count; j++) {
      printf("  token %ld: %s\n", j, tokens[j]);
    }
  }

  int status;

  struct addrinfo hints;
  struct addrinfo* address_info;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = hints.ai_flags | AI_CANONNAME;

  if ((status = getaddrinfo(HOSTNAME, PORT, &hints, &address_info)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
  }

  int socket_server = socket(address_info->ai_family, address_info->ai_socktype, address_info->ai_protocol);

  printf("host: %s\n", address_info->ai_canonname);
  printf("port: %d\n", ntohs(((struct sockaddr_in*)(address_info->ai_addr))->sin_port));

  if ((status = bind(socket_server, address_info->ai_addr, address_info->ai_addrlen)) == -1) {
    perror("bind");
  }

  freeaddrinfo(address_info);

  return 0;
}
