#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h> // struct sockaddr
#include <sys/socket.h>


#include <arpa/inet.h> // htons

#include <netdb.h>

// #include <netinet/ip.h>
#include <netinet/in.h> // IPPROTO_RAW, IPPROTO_IP, IPPROTO_TCP, INET_ADDRSTRLEN


#include <errno.h>

#include "load_file.h"
#include "tokenize.h"
#include "address_info.h"

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

  char buffer[BUFFER_SIZE];

  struct sockaddr_in server;
  struct sockaddr client;

  int socket_server = socket(AF_INET , SOCK_STREAM , 0);
  int client_socket;

  server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(PORT));

  if (bind(socket_server, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("bind");
    free_tokens(lines, line_count);
    return -1;
  }

  listen(socket_server, 3);

  while(1) {
    socklen_t client_len = sizeof(client);

    printf("%s\n", "waiting for client to connect.");
    if((client_socket = accept(socket_server, &client, &client_len)) < 0) {
      perror("accept");
      free_tokens(lines, line_count);
      return -1;
    }

    //get ip of client

    struct in_addr addr;

    char address[30];
    sprintf(address, "%d", ((struct sockaddr_in *)&client)->sin_addr.s_addr);

    inet_aton(address, &addr);

    strcpy(address, inet_ntoa(addr));

    //reverse ip because of little endian

    size_t len;
    char** ip = tokenize(address, ".", &len);

    memset(address, '\0', strlen(address));

    printf("%s", "client with ip ");

    for(int i = (int)len - 1; i >= 0; i--) {
      if(((len - 1) - i) > 2) {
        strcat(address, ip[i]);
      } else {
        char temp_str[5];
        strcpy(temp_str, ip[i]);
        strcat(temp_str, ".");
        strcat(address, temp_str);
      }
    }

    printf("%s%s\n", address, " connected.");

    //read message from client

    memset(buffer, '\0', BUFFER_SIZE);

    if(read(client_socket, buffer, BUFFER_SIZE - 1) == -1) {
      perror("read");
      free_tokens(ip, len);
      free_tokens(lines, line_count);
      return -1;
    }

    printf("%s%s%s", address, " wrote: ", buffer);
    free_tokens(ip, len);
    printf("%s\n", "client disconnected.\n");
  }
  
  free_tokens(lines, line_count);
  return 0;
}
