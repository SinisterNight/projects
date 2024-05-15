// compile: gcc -o minor4cli minor4cli.c
// usage  : ./minor4cli server_ip server_port
// PING CSE-0# to get server_ip connect server to port before connecting client

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
#include <limits.h>
#define SIZE 1024
#define PING_MESSAGE "PING"
#define PONG_MESSAGE "PONG"
#define MAX_TIMEOUT 10

int main(int argc, char *argv[]){//start main
    //checking command line arguments
    if(argc != 3){
        printf("%s <server_ip> <server_port>\n", argv[0]); //checking args
        exit(EXIT_FAILURE);//exit
    }

    //parsing server IP and port
    char* server_ip = argv[1]; //server_ip
    int server_port = atoi(argv[2]);//server port

    //checking port range
    if(server_port <= 0 || server_port > 65535){ //checking ports
        printf("You entered an invalid port number %d\n", server_port);
        exit(EXIT_FAILURE);//exit
    }

    //creating UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); //socket AF_INET SOCKDGRAM
    if (sockfd < 0){//checking sockfd
        perror("Socket");//socket 
        exit(EXIT_FAILURE);//exit
    }

    //configuring server address
    struct sockaddr_in servaddr;//struct
    memset(&servaddr, 0, sizeof(servaddr));//memset
    servaddr.sin_family = AF_INET; //servaddr = AFINET
    servaddr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &servaddr.sin_addr) <= 0){
        perror("inet_pton"); //error
        exit(EXIT_FAILURE);//exit
    }

//start timer
time_t start_time = time(NULL); //start time

//send/receive pings
int i = 0;// set i
int ping_count = 10;//set ping count
int successful_pings = 0;//successful ping set
int packets_lost = 0;//set packet lost
double total_packets = 0;//set total packets
double times[10];//set array times to store RTT times,

while(1) { //inf loop
     time_t RTT_time = time(NULL); //set RTT_time
    //check if 10 seconds have passed
    time_t current_time = time(NULL); //set current time
    
    if (current_time - start_time >= 101) { // run for 101 seconds
        printf("101 seconds have passed, all messages have been sent");
        break; //break
    }

    if (current_time - start_time >= 10) { // decrement ping_count every 10 seconds so only 10 pings get sent
        ping_count--;
        printf("%d pings left...\n", ping_count); //how many pings left
        start_time = time(NULL); //start time
        
        
        //send message
        char ping_msg[SIZE];
        sprintf(ping_msg, "%s %d", PING_MESSAGE, ping_count);  //message sent to svr
        sendto(sockfd, ping_msg, strlen(ping_msg), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr)); //send to
        times[i] = time(NULL); //set times to the current time,
    
    

    //receive response with timeout
    char buffer[SIZE];
    socklen_t servaddr_len = sizeof(servaddr);
    struct timeval timeout = {1, 0}; //1 second timeout
    fd_set set;
    FD_ZERO(&set);
    FD_SET(sockfd, &set);
    int num_ready = select(sockfd + 1, &set, NULL, NULL, &timeout); //int num ready
    if (num_ready == -1) { //checking num ready
        perror("SELECT");//error for select
        exit(EXIT_FAILURE);//exit
    } else if (num_ready == 0) {
        printf("Packet[Client] %s:%d Packet Dropped\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));//message if packet dropped
        packets_lost++;//increment packet loss
        times[i] = 0.00; // set times to zero,
        i++;//increment
        
        continue;//cont
    } else {
        int numBytes = recvfrom(sockfd, (char *)buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&servaddr, &servaddr_len); //init numBytes
        if(numBytes < 0){ // if less 0 
            perror("RECVFROM");//error
            exit(EXIT_FAILURE);//exit
        }
        buffer[numBytes] = '\0'; //reset buf
        printf("received[Server] %s:%d:%s\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port), buffer); //recieved message
        successful_pings++; //inc successful_pings
        double time_taken = (double)(time(NULL) - times[i]); //set time taken to when message recieved
        i++;//increment
        
    }

  
    

    sleep(1); //wait for 1 second
    }

    if (ping_count <= 0) { // exit if no more pings to send
        printf("All pings sent\n"); //all pings set message
        break;//break
    }//exit if

}//end while
printf("Packet Failure: %d\n",packets_lost); //shows packets failed
printf("Packet Success: %d\n",successful_pings);//shows packets successful
total_packets = packets_lost + successful_pings;//total packets sent, should be 10
printf("Total Packets lost percentage: %0.2f\n", packets_lost/total_packets);//showing percentage of packet loss 30% should be about the averge due to svr code but its rng so you can't promise anything
for (int j = 0; j < 10; j++) {
    printf("Ping Sent... RTT= %d took %.3f ms\n", j, times[j] == 0.00 ? 0.00 : (double)(time(NULL) - times[j]));//print RTT times
    
}
double min_time = times[0];// mintime
double max_time = times[0];//maxtime
double total_time = times[0];//total time

for (int l = 1; l < 10; l++) {
    if (times[l] != 0 && times[l] < min_time) {
        min_time = times[l]; //attempting to get min time
    }
    if (times[l] > max_time) {
        max_time = times[i]; //attempting to get max time
    }
    if (times[l] != 0) {
        total_time += times[l]; //attempting to get total time so that it can be converted to avg
    }
}

printf("Min time: %.9f ms\n", min_time == 0 ? 0.00 : min_time); //print min
printf("Max time: %.9f ms\n", max_time == 0 ? 0.00 : max_time); //print max
printf("Average time: %.9f ms\n", (successful_pings == 0 ? 0.00 : (total_time / successful_pings)));//print average


return 0;
}