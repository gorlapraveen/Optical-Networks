
 
#include <SoftwareSerial.h>
char inchar;

 
SoftwareSerial mySerial(9, 10);
// char data[21];
 //short pos=-1;
 //int number_of_bytes_received;
void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate  
  Serial.begin(9600);    // the GPRS baud rate
   delay(2000);
     mySerial.println("AT");
  delay(2000);
 
  mySerial.println("AT+CMGF=1");
  delay(2000);
  
  mySerial.println("AT+CMGS=\"8520940595\"");
  delay(2000);
 
  mySerial.println("HAI");
  delay(2000);
 
  mySerial.println((char)26);
  delay(2000);
 
  
 //mySerial.println("ATS0=002");
//delay(1000);  
//mySerial.println("ATH0");
//delay(1000);
  mySerial.print("AT+CLIP=1\r"); 
  delay(100); 
   mySerial.print("AT+CNMI=2,2,0,0,0"); 
  delay(100); 
  
}
 
void loop()
{
 
  

  if(mySerial.available() >0)
    {
    delay(10); 
    inchar=mySerial.read();
    if (inchar=='+')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='9')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='1')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='8')
    {           
    delay(10);
    inchar=mySerial.read();
    if (inchar=='0')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='0')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='8')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='6')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='4')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='5')
    {
    delay(10);
    inchar=mySerial.read();
    if (inchar=='2')
    {
          delay(10);
    inchar=mySerial.read();
    if (inchar=='7')
    {
          delay(10);
    inchar=mySerial.read();
    if (inchar=='3')
    {
    Serial.println("MOTOR ON");
    delay(100);
       
    
    delay(1000); 
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
  }  
  
 
receivemessage();    
      
    
}

void receivemessage()
{
  
  if(mySerial.available() >0)
   // {
   // delay(10); 
    //inchar=mySerial.read();
    //if (inchar=='Y')
    //{
    //delay(10);
    //inchar=mySerial.read();
    //if (inchar=='S')
   // {
     // delay(10);
      inchar=mySerial.read();
    if (inchar=='S')
    {
        Serial.print("motor on");
      }
 //   }
   // }
    //}
      
      
      if (mySerial.available() >0)
      
    {
    delay(10); 
    inchar=mySerial.read();
     if (inchar=='N')
    {
    delay(10);
    inchar=mySerial.read();
     if  (inchar=='O')
    {
      Serial.println("motor off");
    }
    }
    }
      
      
    
}


//void sendmessage()
//{
 // mySerial.println("AT");
 // delay(2000);
 // ShowSerialData();
 // mySerial.println("AT+CMGF=1");
  //delay(2000);
  //ShowSerialData();
 // mySerial.println("AT+CMGS=\"8008645273\"");
 // delay(2000);
 // ShowSerialData();
 // mySerial.println("HAI");
 // delay(2000);
 // ShowSerialData();
  //mySerial.println((char)26);
  //delay(2000);
  //ShowSerialData();
  
//}


