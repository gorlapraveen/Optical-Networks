
 
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
 char inchar;
void setup()
{
 // mySerial.begin(9600);               // the GPRS baud rate  
  Serial.begin(9600);   // the GPRS baud rate
  mySerial.begin(9600);
  delay(2000);  
   mySerial.print("AT+CNMI=2,2,0,0,0"); 
  delay(100); 
 
}
 
void loop()
{
 
  receivemessage();
   delay(3000);
}


void receivemessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); 
  delay(3000);
 // ShowSerialData();
  if(mySerial.available() >0)
    {
    delay(10); 
    inchar=mySerial.read();
   
      if (inchar=='Y')
      {
        delay(10);
        inchar=mySerial.read();
        if (inchar==' ')
        {
           delay(10);
            inchar=mySerial.read();
       if (inchar=='/')     
     {
    
      Serial.println("MOTOR ON");
      delay(100);
       
   
    }
    }
    }
    }
    
    
   if (mySerial.available() >0)
    {
    delay(10); 
    inchar=mySerial.read();
    
      if (inchar=='N')
      {
        delay(10);
        inchar=mySerial.read();
    
        if (inchar==' ')
        {
          delay(10);
          inchar=mySerial.read();
          if (inchar=='/')
        {
      Serial.println("MOTOR OFF");
    }
    }
    }
    }
    
}



