#include<reg51.h>
#define motor P1 
sbit rs = P1^0;
sbit rw = P1^1;
sbit e = P1^2;
sbit sensorO=P2^0;
sbit sensorE=P2^1;
sbit sensorM=P2^2;
char info[70];
char test[6]={"$GPGGA"};
char comma_position[15];
unsigned int check=0,i;
unsigned char a;
void receive_data();
void okcheck();
void sertxs(unsigned char x);
void sertx(unsigned char *tx);
void serinit();
void delay(unsigned int time);
unsigned char Receive();
unsigned char Rx;
void latitude();
void longitude();
unsigned char re_data();
unsigned char Tx;
void_gps();


void serinit()
{
TMOD=0x20;      
TH1=0xfa;      
SCON=0x50  ;   
TR1=1;          
}
 

void find_comma()
{
unsigned int i,count=0;
for(i=0;i<70;i++)
{ 
if(info[i]==',')
{
comma_position[count++]=i;
}
    }
}


void compare()
{  
IE=0x00;        
find_comma();     
check=0;
IE=0x90;    
}


void receive_data()         
{
info[check++]=SBUF;   
if(check<7)          
    {
if(info[check-1]!=test[check-1])
check=0;
    }
RI=0;
}


void delay(unsigned int time)
{
unsigned int i,j;
for(i=0;i<time;i++);
for(j=0;j<1234;j++);
}

  void sertxs(unsigned char x)
{
 SBUF=x;
 while(TI==0);
 TI=0;
}


void sertx(unsigned char *tx)
{

  for( ;*tx!='\0';*tx++)
  {
   SBUF=*tx;
   while(TI==0);
   TI=0;
   }
   }


  unsigned char Receive()
 {
  unsigned char Rx;
  while(RI==0);
  Rx=SBUF;
  RI=0;
  return Rx;
  }



 void okcheck()
{
unsigned char Rx;
do
{
Rx=Receive();
}
while(Rx!='K');
}




void main()
{
serinit();
IE=0X90;
 sertx("AT\r\n");
 okcheck();
 sertx("AT+CMGD=1\r\n");
 okcheck();
 sertx("AT+CNMI=1,2,0,0\r\n");
 okcheck();
 sertx("AT+CMGF=1\r\n");
 okcheck();
 sertx("AT+CMGS=\"7382021294\"\r\n");


do
 {
 Rx=Receive();
 }
																 
 while(Rx!='*');
// sertx("Hai......");
 sertxs(0x1A);

 while(1)
 {
 do
 {
 Rx=Receive();
 }

 while(Rx!='>');
 sertx("http://maps.google.com/maps/place/17.7107499,83.1637147\r\n");
 sertxs(0x1A);
 okcheck();

 do
 {
 Rx=Receive();
 } 
 while(Rx!='*');

Rx=Receive();
if(Rx=='1')
{
motor=0x09;
 }
while(1)
{

if(sensorO==1)
{
motor=0x08;
sertx("AT+CMGS=\"7382021294\"\r\n");
 do
 {
 Rx=Receive();
 }

 while(Rx!='>');
 sertx("http://maps.google.com/maps/place/17.7107499,83.1637147\r\n");
 sertxs(0x1A);
 okcheck();

}
if(sensorE==1)
{
motor=0x06;
sertx("AT+CMGS=\"7382021294\"\r\n");
 do
 {
 Rx=Receive();
 }

 while(Rx!='>');
 sertx("http://maps.google.com/maps/place/17.7107499,83.1637147\r\n");
 sertxs(0x1A);
 okcheck();

}

delay(20);
motor=0x09;
delay(20);
motor=0x08;
delay(20);
motor=0x01;
delay(20);

 }