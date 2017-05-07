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
#include "address_info.h"

int main (int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: %s\n", "Exactly one file must be specified.");
    exit(EXIT_FAILURE);
  }

  const char* file_content = load_file(argv[1]);

  size_t line_count;
  char** lines = tokenize(file_content, "\n", &line_count);

  char buffer[BUFFER_SIZE];

  struct sockaddr_in server;
  struct sockaddr client;

  server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(PORT));

  int socket_server = socket(server.sin_family, SOCK_STREAM, 0);
  int client_socket;

  if (bind(socket_server, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("bind");
    close(socket_server);
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

    char client_ip_address[INET_ADDRSTRLEN];
    inet_ntop(server.sin_family, (void*)(&((struct sockaddr_in *)&client)->sin_addr.s_addr), (char*)&client_ip_address, INET_ADDRSTRLEN);

    printf("Client with IP %s connected.\n", client_ip_address);

    //read message from client and return "Gefahrengrad"

    memset(buffer, '\0', BUFFER_SIZE);

    if(read(client_socket, buffer, BUFFER_SIZE - 1) == -1) {
      perror("read");
      free_tokens(lines, line_count);
      return -1;
    }

    if(buffer[0] != '\n') {
      printf("%s%s%s\n", client_ip_address, " requested info for: ", buffer);

      size_t request_len;
      char** requests = tokenize(buffer, " ", &request_len);

      memset(buffer, '\0', BUFFER_SIZE);

      for (size_t i = 0; i < line_count; i++) {
        size_t token_count;
        char** tokens = tokenize(lines[i], " ", &token_count);

        for (size_t j = 0; j < request_len; j++) {
          for(int i = 0; requests[j][i]; i++) requests[j][i] = toupper(requests[j][i]);
          if(strcmp(strtok(requests[j], "\n"), tokens[0]) == 0) {
            char temp_output[BUFFER_SIZE];
            sprintf(temp_output, "%s%s%s%s\n", "Gefahrengrad for ", requests[j], " is ", tokens[1]);
            printf("%s", temp_output);
            strcat(buffer, temp_output);
          }
        }

        free_tokens(tokens, token_count);
      }

      if(buffer[0] == '\0') {
        printf("%s\n", "wrong input from client.");
        write(client_socket, "wrong input.", BUFFER_SIZE);
      } else {
        write(client_socket, buffer, BUFFER_SIZE);
      }

      free_tokens(requests, request_len);
      printf("%s\n", "client disconnected.\n");
    } else {
      printf("%s\n", "wrong input from client.");
      write(client_socket, "wrong input.", BUFFER_SIZE);
    }
  }

  free_tokens(lines, line_count);
  return 0;
}
