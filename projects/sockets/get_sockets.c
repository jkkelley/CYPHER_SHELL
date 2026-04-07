/* sockets.c */
// Libs coming in
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IP "54.172.102.128" // httpbin.org
#define PORT 80 // http protocol

int main()
{
    int s;
    int bytes_read;
    struct sockaddr_in sock;
    char buf[1024];
    char *data;

    // What data we're sending
    data = "GET /range/1024 HTTP/1.0\r\nHost: httpbin.org\r\n\r\n";

    // Creating the socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Check for socket error before booting up!
    if (s < 0) 
    {
        printf("socket() error\n");
        return -1;
    }

    // Setting the socket up with some tools
    sock.sin_addr.s_addr = inet_addr(IP);
    sock.sin_port = htons(PORT);
    sock.sin_family = AF_INET;

    // Check for connect errors
    if (connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0)
    {
        printf("connect() error\n");
        close(s);

        return -1; // exit out
    }

    // Send the request over the established TCP stream
    write(s, data, strlen(data));

    // Go time baby
    // We're getting data now...
    // Keep reading as long as the server is pushing data (> 0)
    while ((bytes_read = read(s, buf, sizeof(buf) -1)) > 0)
    {
        // Null-terminate the chunk we just got
        buf[bytes_read] = '\0';
        // Print it immediately
        printf("%s", buf);
        // Clear the buffer for the next read
        memset(buf, 0, sizeof(buf));
    }

    if (bytes_read < 0)
    {
        // Print error out
        perror("read failed");
    }

    // Close socket connection
    close(s);

    // Exit out
    return 0;
}
