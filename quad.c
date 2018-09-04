#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "MotionSensor.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <wiringPi.h>

int clientSocket;
int velX=0,velY=0;
int motor1=1000, motor2=1000, motor3=1000, motor4=1000;
float SampleTime = 10; 
unsigned long lastTime=0;
float outmax=300, outmin=-300;
float Ix=0 , Iy=0 , Iz=0;
float lasteX=0,lasteY=0,lasteZ=0;
float outputX=0, outputY=0,outputZ=0; 
int canal[4];
float kp[2],kd[2], ki[2];

//////////////////  Função PID  ///////////////////////
void pid_init(){
   kp[0] = 2.2;
   ki[0] = 1.1 * (SampleTime/1000); //  KI * SampletimeinSEC
   kd[0] = 0.2 / (SampleTime/1000); //  KD / SampletimeinSEC
   kp[1] = 2.2;
   ki[1] = 0 * (SampleTime/1000); //  KI * SampletimeinSEC
   kd[1] = 0.2 / (SampleTime/1000); //  KD / SampletimeinSEC   
}

void pid_update(){
   unsigned long now = millis();
   int timeChange = (now - lastTime);
   if(timeChange>=SampleTime)
   {

      float eX = canal[3] - ypr[PITCH];
      float eY = canal[4] - ypr[ROLL];
      float eZ = canal[2] - ypr[YAW];
      
      Ix += (ki[0] * eX);
      Iy += (ki[0] * eY);
      Iz += (ki[1] * eZ);

 
      /*Compute PID Output*/
      outputX = kp[0]*eX + Ix - kd[0]*(eX-lasteX);
      outputY = kp[0]*eY + Iy - kd[0]*(eX-lasteX) ;
      outputZ = kp[1]*eZ + Iz - kd[1]*(eX-lasteX) ;
      
	  
      /*Remember some variables for next time*/
      lasteX=eX;
      lasteY=eY;
      lasteZ=eZ;
      lastTime = now;
   }
	
}


////////////////////  Função Motor  /////////////////////////////////////
void motor_init(){
	system("echo 3=1000us > /dev/servoblaster");//GPIO 27
	system("echo 4=1000us > /dev/servoblaster");//GPIO 22
	system("echo 5=1000us > /dev/servoblaster");//GPIO 23
	system("echo 6=1000us > /dev/servoblaster");//GPIO 24

}
void motor_update(){
   velX = canal[0] + outputZ;
   velY = canal[0] - outputZ;

   motor1 = velX - outputX; 
   motor3 = velX + outputX;
   
   motor2 = velY - outputY; 
   motor4 = velY + outputY; 
  
   if(canal[0]<1100){
                   motor1=1000;
                   motor2=1000;
                   motor3=1000;
                   motor4=1000;  
   }         
   if(motor1<1000) motor1=1000;   
   if(motor2<1000) motor2=1000;
   if(motor3<1000) motor3=1000;
   if(motor4<1000) motor4=1000;
   
   if(motor1>2000) motor1=2000;   
   if(motor2>2000) motor2=2000;
   if(motor3>2000) motor3=2000;
   if(motor4>2000) motor4=2000;
   char strx[4];
   char str1[50];
   char str2[50];
   char str3[50];
   char str4[50];
   char strm1[8]="echo 3=";
   char strm2[8]="echo 4=";
   char strm3[8]="echo 5=";
   char strm4[8]="echo 6=";
   char str[22]="us > /dev/servoblaster";
	
	str1[0]= '\0';
    	snprintf(strx, sizeof(strx), "%d", motor1);
    	strncat(str1, strm1, 7);
    	strncat(str1, strx, 4);
    	strncat(str1, str, 22);
	
	str2[0]= '\0';
    	snprintf(strx, sizeof(strx), "%d", motor2);
    	strncat(str2, strm2, 7);
    	strncat(str2, strx, 4);
    	strncat(str2, str, 22);
	
	str3[0]= '\0';
    	snprintf(strx, sizeof(strx), "%d", motor3);
    	strncat(str3, strm3, 7);
    	strncat(str3, strx, 4);
    	strncat(str3, str, 22);
	
	str4[0]= '\0';
    	snprintf(strx, sizeof(strx), "%d", motor4);
    	strncat(str4, strm4, 7);
    	strncat(str4, strx, 4);
    	strncat(str4, str, 22);
	
	system(str1);//GPIO 27
	system(str2);//GPIO 22
	system(str3);//GPIO 23
	system(str4);//GPIO 24
}



////////////////////  Função TCP  ////////////////////////

void tcp_open(){
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
	
}


void tcp(){
	int i=0,w=0,n=0,j=0;
	char buffer[21];
        char ch[4];
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
	/*printf("\n");
	printf("Ch1: %d",canal[0]);
	printf("\n");
	printf("Ch2: %d",canal[1]);
	printf("\n");
	printf("Ch3: %d",canal[2]);
	printf("\n");
	printf("Ch4: %d",canal[3]);
	printf("\n");
	*/
}

int main()
{ 	
	
  system("sudo ~/AracaCopter/ServoBlaster/user/servod --pcm"); // run servo program 
  tcp_open();// Iniciar conexão TCP
  ms_open(); // Iniciar conexão com o MPU6050
  pid_init(); // Iniciar parametros PID
  motor_init(); // Configurar esc
  

   while(1){
        tcp();
        ms_update();
        pid_update();
        motor_update();
    }
    return 0;
}







