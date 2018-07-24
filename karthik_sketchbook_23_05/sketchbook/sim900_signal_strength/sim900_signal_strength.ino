#include <SoftwareSerial.h>
char inchar;
SoftwareSerial mySerial(9, 10);
int led1=5;
int led2=6;
int led3=7;


void setup()
{
  Serial.begin(9600);
  delay(100);
  mySerial.begin(9600);
  pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
      mySerial.println("AT+CSQ");
  delay(1000);
  //ShowSerialData();
  
 
}
void loop()
{
   
  // mySerial.println("AT");
 // delay(1000);
  
//   mySerial.println("AT+CSQ");
  //delay(1000);
 
  if(mySerial.available() >0)
    {
    delay(10); 
    inchar=mySerial.read();
    if (inchar=='1')
    {
      delay(10);
      inchar=mySerial.read();
      if(inchar=='4')
    {
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
    }
    }
    
   
    
  
    }
  
}

//void ShowSerialData()
//{
// while(mySerial.available()!=0)
  //  Serial.write(mySerial.read()); 
//}
