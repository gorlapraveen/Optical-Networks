#include <SoftwareSerial.h>
SoftwareSerial myserial(2,3);
char inData[100];
char inData1[20];
char inchar;
byte index=0;
byte index1=0;
int j=0;
int num;
String currentIMEI="";

void setup()
{
  Serial.begin(9600);
  myserial.begin(9600);
  myserial.println("AT+CGSN");
  delay(1000);
  for(j=0;j<30;j++)
  {
    
      while(myserial.available()>0)
        {
          
          inchar=myserial.read();
          
          
          
          inData[index]=inchar;
          
          
          if((index>=11)&&(index1<=14))
          {
            inData1[index1]=inData[index];
            currentIMEI+=inData1[index1];
            index1=index1+1;
          }
          index=index+1;
          
        }
  
  }
  
 delay(1000);
 
 
 //Serial.print("IMEI=");
 //Serial.print(inData1);
 Serial.println("string imei=");
 Serial.println(currentIMEI);
 
}
void loop()
{
    //Serial.println("hai=");
  //  Serial.println("IMEI=");
    //Serial.println(inData1);
    //Serial.println("string imei=");
    Serial.println(currentIMEI);
    
    
    //Serial.println("string imei");
   //Serial.println(currentIMEI);    
    
    //Serial.println(inData);
    //Serial.println(str);
    delay(2000);
  
}


