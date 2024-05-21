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
#include <iostream>
   
#define PORT     5000 
#define MAXLINE 1024 
   
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    const char *hello="0";

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
       
    int n=1;
    socklen_t len; 
    int c=0;
    while(1){
    std::string zahl=std::to_string(c);
    hello=zahl.c_str();
  	
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    std::cout<<"Hello message sent."<< hello <<std::endl;
    //usleep(1000000);
    c++;
}
   
    close(sockfd); 
    return 0; 
}
