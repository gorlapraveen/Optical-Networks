
 
#include <SoftwareSerial.h>

 
SoftwareSerial SIM900(9, 10);
 char inchar;
 //short pos=-1;
 //int number_of_bytes_received;
void setup()
{
 // mySerial.begin(9600);               // the GPRS baud rate  
  Serial.begin(9600);   // the GPRS baud rate
  SIM900.begin(9600);
  delay(2000);  
  SIM900.print("AT+CLIP=1\r"); 
  delay(100); 
   SIM900.print("AT+CNMI=2,2,0,0,0"); 
  delay(100); 
 
}
 
void loop()
{
 
  receivemessage();
   delay(3000);
   //receivecall();
  //delay(1000);
   //phonebook();
   //while(Serial.available()&&pos<100) data[++pos]=Serial.read();
   
}
void sendmessage()
{
  SIM900.println("AT");
  delay(2000);
  ShowSerialData();
  SIM900.println("AT+CMGF=1");
  delay(2000);
  ShowSerialData();
  SIM900.println("AT+CMGS=\"8008645273\"");
  delay(2000);
  ShowSerialData();
  SIM900.println("HAI");
  delay(2000);
  ShowSerialData();
  SIM900.println((char)26);
  delay(2000);
  ShowSerialData();
  
}

void receivemessage()
{
  SIM900.println("AT+CNMI=2,2,0,0,0"); 
  delay(3000);
  ShowSerialData();
  if(SIM900.available() >0)
    {
    delay(10); 
    inchar=SIM900.read();
    if (inchar=='Y')
    {
    delay(10);
    inchar=SIM900.read();
    if (inchar=='E')
    {
    delay(10);
    inchar=SIM900.read();
    if (inchar=='S')
    {
   
    Serial.println("MOTOR ON");
    delay(100);
       
   
    }
    }
    }
    }
    
   if (SIM900.available() >0)
    {
    delay(10); 
    inchar=SIM900.read();
    if  (inchar=='N')
    {
    delay(10);
    inchar=SIM900.read();
    if  (inchar=='O')
    {
      Serial.println("MOTOR OFF");
    }
    }
    }
    

  
  //mySerial.println("AT+CMGL=\"ALL\""); 
  //delay(790);
 // if(Serial.available()>0)
  //{
    //number_of_bytes_received = Serial.readBytesUntil (13,data,20);
     //data[number_of_bytes_received] = 0;
  //}
  //bool result = strcmp(data,"Y");
  //if (result == 0)
  //{
   //Serial.println("motor on");
 //} 
 //else 
 //{
   //Serial.println("motor off");
 //}
}

void receivecall()
{
  //mySerial.begin(9600);
  delay(1000);
  ShowSerialData();

//mySerial.println("ATA\r\n");// ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
//delay(1000);
//ShowSerialData();

SIM900.println("ATS0=002");
delay(1000);
ShowSerialData();
//mySerial.println("AT+CPBR=1");
//delay(1000);
//ShowSerialData();
//mySerial.println("ATS3=13");
//delay(1000);
SIM900.println("ATH0");
delay(1000);
ShowSerialData();
SIM900.println("AT+CLIP=1\r\n");
delay(2000);
ShowSerialData();
if(Serial.available() >0)
   {
     inchar=Serial.read();
     if (inchar == '+')
     {
       delay(10);
        inchar=Serial.read();
     if (inchar == '9')
     {
       delay(10);
        inchar=Serial.read();
     if (inchar == '1')
     {
       delay(10);
        inchar=Serial.read();
     if (inchar == '8')
     {
       delay(10);
        inchar=Serial.read();
     if (inchar == '0')
     {
       delay(10);
        inchar=Serial.read();
     if (inchar == '0')
     {
       delay(10);
        inchar=Serial.read();
     if (inchar == '8')
     {
       Serial.print("motor on");
       delay(10);
       
     }
       
     }
       
     }
       
     }
       
     }
       
     }
       
     }
   }
//if (mySerial.println(" ") == "+CLIP: "+919542538534",145,"",,"",0
//)
//{
  //mySerial.println("hai");
//}
//mySerial.println("AT+CPBR=1");
//delay(1000);
//ShowSerialData();
//if (void ShowSerialData()==" ")
//{
 // digitalWrite(floatswitch,HIGH);
  //delay(1000);
//}
}
void phonebook()
{  
  //string(+CBUF)=+CPBF: 22,"5333315",129,"Mobile TV";
  SIM900.println("AT+CPBF");
   delay(1000);
   ShowSerialData();
   //if (+CPBF=='+CPBF: 22,"5333315",129,"Mobile TV"')
   //{
     //Serial.println("motor on");
   //}
   
}
 
  void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(SIM900.read());
}

