#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

int main(int argc, char *argv[]) {
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   string serverHostname;
   serverHostname = "youngchief.tk";
   char buffer[256];
   
//    if (argc < 3) {
//       printf("Usage %s hostname port\n", argv[0]);
//       exit(0);
//    }
	
   portno = 22; // Replace 1234 /w atoi(argv[2]) if you want to use program arguments for the port number
   
   /* Create a socket point */
   sockfd = socket(AF_INET6, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR Opening socket");
      exit(1);
   }
	
   // Resolve hostname to IP  
   server = gethostbyname(serverHostname.c_str()); 
   
   if (server == NULL) {
      printf("ERROR, No such host!\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET6;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR Connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
	
//    printf("Please enter the message: ");
   bzero(buffer,256);
//    fgets(buffer,255,stdin);

   
   /* Send message to the server */
   string msg = "PING";
   n = write(sockfd, msg.c_str(), strlen(msg.c_str()));
   if (n < 0) {
      perror("ERROR Writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,256);
   n = read(sockfd, buffer, 255);
   
   if (n < 0) {
      perror("ERROR Reading from socket");
      exit(1);
   }
	
   printf("%s\n",buffer);

   close(sockfd);

   return 0;
}