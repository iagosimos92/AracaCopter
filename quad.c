#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "MotionSensor.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


int main()
{ 
  int clientSocket;
  int velX=0,velY=0;
  int motor1=1000, motor2=1000, motor3=1000, motor4=1000;
  float kp=2.2, kd=0.2, ki=1.1;
  float kpz=2.2, kdz=0.2, kiz=1.1;
  float SampleTime = 10; 
  unsigned long lastTime=0;
  float outmax=300, outmin=-300;
  float Ix=0 , Iy=0 , Iz = 0;
  float lasteX=0=,lasteY=0,lasteZ=0;
	
	
  system("sudo ~/AracaCopter/ServoBlaster/user/servod --pcm"); // run servo program 
  tcp_open();// Iniciar conexão TCP
  ms_open(); // Iniciar conexão com o MPU6050
  motor_init(); // Configurar esc
  pid_init(); // Iniciar parametros PID

   while(1){
        tcp();
        ms_update();
        pid_update();
        motor_update();
    }
    return 0;
}






//////////////////  Função PID  ///////////////////////
void pid_init(){
   ki = Ki * (SampleTime/1000); //  KI * SampletimeinSEC
   kd = Kd / (SampleTime/1000); //  KD / SampletimeinSEC
   kiz = Kiz * (SampleTime/1000); //  KI * SampletimeinSEC
   kdz = Kdz / (SampleTime/1000); //  KD / SampletimeinSEC
}

void pid_update(){
   unsigned long now = millis();
   int timeChange = (now - lastTime);
   if(timeChange>=SampleTime)
   {

      float eX = canal[3] - ypr[PITCH];
      float eY = canal[4] - ypr[ROLL];
      float eZ = canal[2] - ypr[YAW];
      
      Ix += (ki * eX);
      Iy += (ki * eY);
      Iz += (kiz * eZ);

 
      /*Compute PID Output*/
      float outputX = kp*eX + Ix - kd*(eX-lasteX);
      float outputY = kp*eY + Iy - kd*(eX-lasteX) ;
      float outputZ = kpz*eZ + Iz - kdz*(eX-lasteX) ;
      
	  
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
	
/*	system("echo 3=%dus > /dev/servoblaster",motor1);//GPIO 27
	system("echo 4=%dus > /dev/servoblaster",motor2);//GPIO 22
	system("echo 5=%dus > /dev/servoblaster",motor3);//GPIO 23
	system("echo 6=%dus > /dev/servoblaster",motor4);//GPIO 24*/	
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
        int canal[4];
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

