// compile: gcc -o minor4svr minor4svr.c
// usage  : ./minor4svr port
//run this before cli

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define SIZE 1024
#define PING_MESSAGE "PING"
#define PONG_MESSAGE "PONG"
#define MAX_TIMEOUT 10
//definitions and imports

//main
int main(int argc, char *argv[]){
	//checking command line arguments
	if(argc != 2){
		printf("%s <port> \n", argv[0]); // print
		exit(EXIT_FAILURE);//exit
	}
	//port parsing
	int port = atoi(argv[1]); // port
	//checking port range
	if(port <= 0 || port > 65535){
		printf("You entered an invalid port number %s\n", argv[1]);
		exit(EXIT_FAILURE); //exit
	}
	//CREATING UDP SOCKET
	int sockfd = socket(AF_INET, SOCK_DGRAM,0); //socket connectionless UDP
	if (sockfd < 0){ //checking sockfd < 0
		 perror("Socket");//perror socket
		 exit(EXIT_FAILURE);//exit
	}
    // Bind socket to local address and port
    struct sockaddr_in servaddr, cliaddr; //struck servaddr cliaddr
    memset(&servaddr, 0, sizeof(servaddr)); //memory set
    servaddr.sin_family = AF_INET;  // address family AF_INET IPV4
    servaddr.sin_addr.s_addr = INADDR_ANY; //IP ADDR accepting any connections
    servaddr.sin_port = htons(port); //port num host byte order to network byte order
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { //checking bind
        perror("bind");//bind perror statement
        exit(EXIT_FAILURE);//exit
    }
	// seed RNG
	srand(time(NULL));
	// loop to send/recv pings
	char buffer[SIZE];
	while(1) {
		//Recv message
		socklen_t clientAddressLength = sizeof(cliaddr); //setting clientAddressLength to size cliaddr
		int numBytes = recvfrom(sockfd,(char*)buffer,SIZE, MSG_WAITALL,(struct sockaddr*)&cliaddr,&clientAddressLength); //numBytes recvfrom
		if(numBytes < 0){ //checking numBytes
			perror("RECVFROM");//perror message
			exit(EXIT_FAILURE);//exit
		}
		
		//checking packet loss
		// Check if packet is lost (30% chance of loss)
        if (rand() < RAND_MAX * 0.3) {
            printf("Packet from %s : %d Packet Dropped\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port)); //print ip addr and port
            continue;
        }
		//print message and response
		buffer[numBytes] = '\0'; //reset
		printf("received from %s : %d : %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), buffer); //print
		sendto(sockfd, PONG_MESSAGE, strlen(PONG_MESSAGE), MSG_CONFIRM, (const struct sockaddr *)&cliaddr,  clientAddressLength); //send pong message
	}
	return 0;
}