/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int clientSocket;
  char buffer[21];
  char ch[4];
  int canal[4];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(555);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("192.168.4.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  		
  while(1){
	      int i=0,w=0,n=0,j=0;
	  	  /*---- Read the message from the server into the buffer ----*/
		  recv(clientSocket, buffer, 21, 0);
		  	for(i=0;i<21;i++){
		  		if(buffer[i]=='a' && i==0){
		  			j=1;
		  			n=0;
					w=0;
				  }else{
				  	if(j==1){
						
						if(buffer[i]==','){	  			
							canal[n]=atoi(ch);
							if(n==3){
								j=0;
							}
						 	n=n+1;
							w=0;
							
						}else{
							ch[w]=buffer[i];
							w=w+1;	  		
					   }
					}
				  }

			}
		  	/*---- Print the received message ----*/
		  	
		  	printf("\n");
		  	printf("Ch1: %d",canal[0]);
		  	printf("\n");
		  	printf("Ch2: %d",canal[1]);
		  	printf("\n");
		  	printf("Ch3: %d",canal[2]);
		  	printf("\n");
		  	printf("Ch4: %d",canal[3]);
		  	printf("\n");
		  	
		
	}
  return 0;
}
