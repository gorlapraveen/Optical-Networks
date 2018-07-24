
#include <SoftwareSerial.h>
char inchar;
SoftwareSerial SIM900(9, 10);
 
void setup()
  {
  Serial.begin(9600);
  
 
  SIM900.begin(9600);
  delay(2000);  
  SIM900.print("AT+CLIP=1\r"); 
  delay(100); 
  SIM900.print("AT+CPBR=1"); 
  delay(100); 
  }
 

 

 
void loop()
  {
  if(SIM900.available() >0)
   {
   // delay(10); 
   // inchar=SIM900.read();
   // if (inchar=='1')
   // {
  //  delay(10);
    //inchar=SIM900.read();
   // if (inchar=='4')
  //  {
    delay(10);
    inchar=SIM900.read();
    if (inchar=='K')
   
    {
    Serial.println("MOTOR ON");
    delay(100);
       
    
   // delay(1000); 
    }
    }
   // }
    //}
    
    
  }
