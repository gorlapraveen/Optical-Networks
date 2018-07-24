
 
#include <SoftwareSerial.h>

 
SoftwareSerial mySerial(9, 10);
// char data[21];
 //short pos=-1;
 //int number_of_bytes_received;
void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate  
  Serial.begin(9600);    // the GPRS baud rate
 
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
  mySerial.println("AT");
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CMGF=1");
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CMGS=\"8008645273\"");
  delay(2000);
  ShowSerialData();
  mySerial.println("HAI");
  delay(2000);
  ShowSerialData();
  mySerial.println((char)26);
  delay(2000);
  ShowSerialData();
  
}

void receivemessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); 
  delay(3000);
  ShowSerialData();
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
  mySerial.begin(9600);
  delay(1000);
  ShowSerialData();

//mySerial.println("ATA\r\n");// ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
//delay(1000);
//ShowSerialData();

mySerial.println("ATS0=002");
delay(1000);
ShowSerialData();
//mySerial.println("AT+CPBR=1");
//delay(1000);
//ShowSerialData();
//mySerial.println("ATS3=13");
//delay(1000);
mySerial.println("ATH0");
delay(1000);
ShowSerialData();
mySerial.println("AT+CLIP=1\r\n");
delay(2000);
ShowSerialData();
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
  mySerial.println("AT+CPBF");
   delay(1000);
   ShowSerialData();
   //if (+CPBF=='+CPBF: 22,"5333315",129,"Mobile TV"')
   //{
     //Serial.println("motor on");
   //}
   
}
 
  void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}

