// Client side implementation of UDP client-server model 
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <thread>
#include <chrono>
   
#define PORT     5000 
#define MAXLINE 1024 
   
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE];
 const char *hello = "fr 3823\nts 44597.741924\n6dcal 1\n6df2 1 1 [0 -1.000 8 3][0.000 0.000 0.000][0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000][0 0.00 0.00 0.00]\n6d 1 [0 1.000][84.203 37.681 172.102 99.1970 6.7130 9.6575][0.979069 0.086946 0.184021 -0.166608 -0.176923 0.970021 0.116897 -0.980377 -0.158734]\n3d 0\n6dmt2 1 1 [0 -1.000 1 0.000][1.500 2.500 3.500][0.888888 1.888888 2.888888 3.888888 4.888888 5.888888 6.888888 7.888888 8.888888][0][0.000e+00 0.000e+00 0.000e+00 0.000e+00 0.000e+00 0.000e+00]\n6dmtr 0 0\ngl 0 \nglcal 0 \0";  
    struct sockaddr_in     servaddr; 
    //char ip[]= "192.168.188.41";
    char ip[]="192.168.0.137";
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
   
    memset(&servaddr, 0, sizeof(servaddr)); 
       
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr(ip); 
       
    int n;
    socklen_t len; 
    while(1){
   

    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    std::cout<<"Hello message sent."<<std::endl;
    usleep(10000);
    }
   
    close(sockfd); 
    return 0; 
}
