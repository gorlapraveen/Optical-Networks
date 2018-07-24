//ERFINDER CODE
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
int ledpin = 13;
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(ledpin,OUTPUT);
  delay(1000);
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
     //'s':
      //SendMessage();
      //break;
     //'r':
      RecieveMessage();
      //break;
      ReceiveCall();
  }

 if (mySerial.available()>0)
  Serial.write(mySerial.read());
      

}

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917306988232\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("hi this is gsm");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
 }
 
 void ReceiveCall()
 {
   mySerial.begin(9600);
//delay(2000);
ShowSerialData();

//mySerial.println("ATA\r\n");// ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
//delay(1000);
//ShowSerialData();

mySerial.println("ATS0=002");
delay(800);
//mySerial.println("ATS3=13");
//delay(1000);
mySerial.println("ATH0");
delay(1000);
mySerial.println("AT+CLIP=1\r\n");
delay(1000);
ShowSerialData();
mySerial.println("AT+CPBF");
delay(1000);
ShowSerialData();
if (mySerial.println("AT+CPBF")==mySerial.println("AT+CPBF"))
{
  digitalWrite(ledpin,HIGH);
}



}
void ShowSerialData()
{
if (mySerial.available())
Serial.write(mySerial.read());

}


 
 
