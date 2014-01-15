#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {

  int serverSocket;
  int clientSocket;

  struct sockaddr_in serverAddr, clientAddr;

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(23300);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  int yes = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  
  listen(serverSocket, 5);

  printf("Waiting for connection\n");

  socklen_t sinSize = sizeof(struct sockaddr_in);
  clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &sinSize);

  char *msg = "Hello there!\n";
  send(clientSocket, msg, strlen(msg), 0);
  close(clientSocket);
  close(serverSocket);

  return 0;
}

