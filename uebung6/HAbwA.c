#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include <sys/types.h> // struct sockaddr
#include <sys/socket.h>

#include <arpa/inet.h> // htons

#include <netdb.h>

#include <netinet/in.h> // IPPROTO_RAW, IPPROTO_IP, IPPROTO_TCP, INET_ADDRSTRLEN

#include <errno.h>

#include "load_file.h"
#include "tokenize.h"
#include "forever.h"
#include "buffer_size.h"

#define PORT "5000"
#define HOST "127.0.0.1"

int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: %s\n", "Exactly one file must be specified.");
    exit(EXIT_FAILURE);
  }

  int exit_value = EXIT_SUCCESS;

  const char* file_content = load_file(argv[1]);

  size_t line_count;
  char** lines = tokenize(file_content, "\n", &line_count);

  struct sockaddr_in server;
  struct sockaddr client;

  server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(PORT));

  int socket_server = socket(server.sin_family, SOCK_STREAM, 0);
  int client_socket;

  if (bind(socket_server, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("bind");
    exit_value = EXIT_FAILURE;
  }

  if (exit_value == EXIT_SUCCESS) {

    listen(socket_server, 3);

    forever {
      socklen_t client_len = sizeof(client);

      printf("%s\n", "Waiting for client to connect…");
      if((client_socket = accept(socket_server, &client, &client_len)) < 0) {
        perror("accept");
        close(client_socket);
        exit_value = EXIT_FAILURE;
        break;
      }

      // get ip of client

      char client_ip_address[INET_ADDRSTRLEN];
      inet_ntop(server.sin_family, (void*)(&((struct sockaddr_in *)&client)->sin_addr.s_addr), (char*)&client_ip_address, INET_ADDRSTRLEN);

      printf("Client with IP %s connected.\n", client_ip_address);

      // read message from client and return "Gefahrengrad"

      FILE* stream = fdopen(client_socket, "r+");

      forever {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stream);

        int buffer_strlen = strlen(buffer);

        if (buffer[buffer_strlen - 1] == '\n') {
          buffer[buffer_strlen - 1] = '\0';
        }

        if (strlen(buffer) == 0) {
          break;
        }

        for(int i = 0; buffer[i]; i++) {
          buffer[i] = toupper(buffer[i]);
        }

        printf("Client %s requested info for: '%s'\n", client_ip_address, buffer);

        char output_buffer[BUFFER_SIZE];
        memset(output_buffer, '\0', BUFFER_SIZE);

        for (size_t i = 0; i < line_count; i++) {
          size_t token_count;
          char** tokens = tokenize(lines[i], " ", &token_count);

          if (strcmp(tokens[0], buffer) == 0) {
            sprintf(output_buffer, "%s\n", tokens[1]);
          }

          free_tokens(tokens);
        }

        if (strlen(output_buffer) == 0) {
          sprintf(output_buffer, "-1\n");
        }

        printf("Sending response to client %s: %s", client_ip_address, output_buffer);

        if(write(client_socket, output_buffer, BUFFER_SIZE) == -1) {
          perror("write");
          close(client_socket);
          exit_value = EXIT_FAILURE;
          break;
        }
      }

      fclose(stream);
    }
  }

  close(socket_server);

  free_tokens(lines);
  return exit_value;
}
