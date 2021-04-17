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

int main(int argc, char const *argv[])
{
    // ---------------IPv4--------------
    int sockfd_ipv4, newsockfd_ipv4, portno_ipv4;
    socklen_t clilen_ipv4;
    char buffer[256];
    struct sockaddr_in serv_addr_ipv4, cli_addr_ipv4;
    int n;

    sockfd_ipv4 = socket(AF_INET, SOCK_STREAM, 0);
    // setsockopt(sockfd_ipv4, 0, O_NONBLOCK, 0, 0);
    if (sockfd_ipv4 < 0)
    {
        perror("IPv4 | ERROR Opening socket.");
        exit(1);
    }
    else
    {
        cout << "IPv4 | Opened socket!\n";
    }

    bzero((char *)&serv_addr_ipv4, sizeof(serv_addr_ipv4));
    portno_ipv4 = 1234; // Port number goes here.

    // Configure server details.
    serv_addr_ipv4.sin_family = AF_INET;         // More details on types: man socket
    serv_addr_ipv4.sin_addr.s_addr = INADDR_ANY; // Allow any interface.
    serv_addr_ipv4.sin_port = htons(portno_ipv4);

    cout << "IPv4 | Port: " << portno_ipv4 << "\n"; // Output the port number, you could also ask for a custom port and use that.

    // Start binding the socket.
    if (
        bind(sockfd_ipv4, (struct sockaddr *)&serv_addr_ipv4, sizeof(serv_addr_ipv4)) < 0)
    {
        perror("IPv4 | ERROR binding.");
        exit(1);
    }
    else
    {
        cout << "IPv4 | Binded socket!\n";
    }

    // Nap until it gets an incomming connection.
    if (listen(sockfd_ipv4, 5) < 0)
    {
        perror("IPv4 | ERROR Listening to the socket");
    }
    else
    {
        // change 5 to how ever many connections you want in queue before refusing to connect
        cout << "IPv4 | Now listening to the socket!\n";
        clilen_ipv4
 = sizeof(cli_addr_ipv4); // 16 is default, change this to how ever many (or little) you want!
        cout << "IPv4 | Number of connections allowed in queue before refusing to connect: " << clilen_ipv4
 << "\n";
    }

    // Accept the connection from client
    newsockfd_ipv4 = accept(sockfd_ipv4, (struct sockaddr *)&cli_addr_ipv4, &clilen_ipv4);
    if (newsockfd_ipv4 < 0)
    {
        perror("IPv4 | ERROR Socket accept");
        exit(1);
    }
    else
    {
        cout << "IPv4 | Accepted connection!\n";
    }

    // Connected established, let's start communicating
    bzero(buffer, 256);
    n = read(newsockfd_ipv4, buffer, 255);
    if (n < 0)
    {
        perror("IPv4 | ERROR Reading from socket!\n");
        exit(1);
    }
    else
    {
        cout << "IPv4 | Connection estabilished!\n";
    }

    printf("IPv4 | Recieved message: \n%s\n", buffer);

    // Send something back to client!
    n = write(newsockfd_ipv4, "PONG", 18);
    if (n < 0)
    {
        perror("IPv4 | ERROR writing to socket failed.");
        exit(1);
    }
    else
    {
        cout << "IPv4 | Sent PONG message!\n";
    }

    // ------------------------IPv6----------------------
    int sockfd_ipv6, newsockfd_ipv6, portno_ipv6;
    socklen_t clilen_ipv6;
    // char buffer[256];
    struct sockaddr_in serv_addr_ipv6, cli_addr_ipv6;
    int n_ipv6;

    sockfd_ipv6 = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd_ipv6 < 0)
    {
        perror("IPv6 | ERROR Opening socket.");
        exit(1);
    }
    else
    {
        cout << "IPv6 | Opened socket!\n";
    }

    bzero((char *)&serv_addr_ipv6, sizeof(serv_addr_ipv6));
    portno_ipv6 = 1234; // Port number goes here.

    // Configure server details.
    serv_addr_ipv6.sin_family = AF_INET6;         // More details on types: man socket
    serv_addr_ipv6.sin_addr.s_addr = INADDR_ANY; // Allow any interface.
    serv_addr_ipv6.sin_port = htons(portno_ipv6);

    cout << "IPv6 | Port: " << portno_ipv6 << "\n"; // Output the port number, you could also ask for a custom port and use that.

    // Start binding the socket.
    if (
        bind(sockfd_ipv6, (struct sockaddr *)&serv_addr_ipv6, sizeof(serv_addr_ipv6)) < 0)
    {
        perror("IPv6 | ERROR binding.");
        exit(1);
    }
    else
    {
        cout << "IPv6 | Binded socket!\n";
    }

    // Nap until it gets an incomming connection.
    if (listen(sockfd_ipv4, 5) < 0)
    {
        perror("IPv6 | ERROR Listening to the socket");
    }
    else
    {
        // change 5 to how ever many connections you want in queue before refusing to connect
        cout << "IPv6 | Now listening to the socket!\n";
        clilen_ipv4 = sizeof(cli_addr_ipv6); // 16 is default, change this to how ever many (or little) you want!
        cout << "IPv6 | Number of connections allowed in queue before refusing to connect: " << clilen_ipv4
             << "\n";
    }

    // Accept the connection from client
    newsockfd_ipv6 = accept(sockfd_ipv6, (struct sockaddr *)&cli_addr_ipv4, &clilen_ipv4);
    if (newsockfd_ipv6 < 0)
    {
        perror("IPv6 | ERROR Socket accept");
        exit(1);
    }
    else
    {
        cout << "IPv6 | Accepted connection!\n";
    }

    // Connected established, let's start communicating
    bzero(buffer, 256);
    n_ipv6 = read(newsockfd_ipv6, buffer, 255);
    if (n < 0)
    {
        perror("IPv6 | ERROR Reading from socket!\n");
        exit(1);
    }
    else
    {
        cout << "IPv6 | Connection estabilished!\n";
    }

    printf("IPv6 | Recieved message: \n%s\n", buffer);

    // Send something back to client!
    n_ipv6 = write(newsockfd_ipv6, "PONG", 18);
    if (n_ipv6 < 0)
    {
        perror("IPv6 | ERROR writing to socket failed.");
        exit(1);
    }
    else
    {
        cout << "IPv6 | Sent PONG message!\n";
    }

    return 0;
};