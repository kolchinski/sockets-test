#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {

  int clientSocket;
  struct sockaddr_in clientAddr;

  memset(&clientAddr, 0, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = htons(23300);
  clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  int yes = 1;
  setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  if(connect(clientSocket, (struct sockaddr *)&clientAddr, sizeof(clientAddr))<0)
  {
    printf("\n Error : Connect Failed \n");
    return 1;
  }

  int nbytes = 0;
  char buffer[1024];
  nbytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
  if (nbytes == 0)
  {
          perror("Server closed the connection");
          close(clientSocket);
          exit(-1);
  }
  else if (nbytes == -1)
  {
          perror("Socket recv() failed");
          close(clientSocket);
          exit(-1);
  }
  else
  {
          /* The message doesn't have a '\0' at the end. Add one so we
             can print it */
          buffer[nbytes] = '\0';
          printf("Received this message:\n<<%s>>\n", buffer);
  }

  char * msg = "Going the other direction!!!\n";
  send(clientSocket, msg, strlen(msg), 0);

  close(clientSocket);

  return 0;
}

