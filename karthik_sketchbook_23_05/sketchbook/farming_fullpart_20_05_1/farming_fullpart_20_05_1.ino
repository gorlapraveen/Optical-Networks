//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(9, 10);

char inchar;
float F1;
//float F2;
float PS;
int f1=7;
//int f2=8;
int relay1=5;
int relay2=6;
int TimeInterval1;


int temp=0,i=0;
int led=13;
int a=0;

char str[15];

void setup()
{
  Serial.begin(9600);
  //mySerial.begin(9600);
  pinMode(f1,INPUT_PULLUP);
  //pinMode(f2,INPUT_PULLUP); 
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT); 
  Serial.print("pin state low\n");
 delay(3000); 
 Serial.println("AT+CMGF=1"); // set SMS mode to text
 delay(200);
 Serial.println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt 
 delay(200);
 
//  Serial.println("AT+CLIP=1");
  //delay(1000);
  //Serial.println("ATH");
  //Serial.println("ATA=010");
 PowerOn();
}

void loop()
{
  // set module to send SMS data to serial out upon receipt 
 WaterLevelRead();
 /*
  if(temp==1)
  {
    ReceiveSms();
    temp=0;
    i=0;
    delay(1000);
  }*/
 WaterOffMotorOff();
//InComingCall();

}

void serialEvent() 
 {
  while(Serial.available()) 
  {
    inchar=Serial.read(); 
       if (inchar=='Y')
        {
            delay(10);
            //digitalWrite(led1, HIGH);
            //digitalWrite(led2,LOW);
            inchar=Serial.read();
              if(inchar=='Y')
              {
                    delay(1000);
                    //Serial.println("Motor on");
                    MotorOnWaterStatus();
              } 
              
             
                   
                   
        }
      
       if (inchar=='N')
       {
            delay(10);
            inchar=Serial.read();
            //digitalWrite(led1, LOW);
            //digitalWrite(led2,HIGH);
         //           delay(10);
          if(inchar=='N')
            {
                   MotorOff();
                   Serial.println("Relay 1 low\n");
                   char status24[]="Motoroff";
                    SendMessage(status24);
            }
          
          
          else if(inchar=='O')
          {
      if(a==0)
      {
        MotorOnWaterStatus();
        a=1;
        return;
      }
      else
      {
        
        MotorOff();
        a=0;
        char status24[]="Motor off";
        SendMessage(status24);
        delay(200);
        return;
        
      }
   
    }
             
            
        }
      
        
  
    
  }
   
 }

void PowerOn()
{ 
 TimeInterval1=900000;
 WaterLevelStatus();
 OutGoingCall();
 
}

void WaterLevelRead()
{
 F1=digitalRead(f1);
// F2=digitalRead(f2);
 
}

void WaterLevelStatus()
{
  WaterLevelRead();
   {
    if((F1==1))
    { char status10[]="PowerAvailable_Water_is_There";
      SendMessage(status10);
      Serial.println("PowerAvailable_Water_is_There");
    } 
    
   else if((F1==0))
    { 
      char status12[]="PowerAvailable_and_Water_critical";
     SendMessage(status12) ;
     MotorOff();
     //delay(TimeInterval1);
     //WaterLevelStatus();
    }
   }
}

void MotorOnWaterStatus()
{
 WaterLevelRead();
                    {
                      if((F1==1))
                         { 
                          MotorOn();
                          a=1;
                          char status21[]="MotorOn_Water_is_There";
                          SendMessage(status21);
                         } 
                      
                      else if((F1==0))
                         {
                           MotorOff();
                           a=0;
                           char status23[]="MotorOff_due_to_Water_at_critical";
                           SendMessage(status23);
                         }
                    }  
  
}

/*void ReceiveSms()
{
   if(!(strncmp(str,"ON",2)))
    {
      MotorOnWaterStatus();
      
     
      delay(200);
    }  
   
   else if(!(strncmp(str,"OFF",3)))
    {
        MotorOff();
        char status24[]="Motor off";
        SendMessage(status24);
        delay(200);
    }
  
   
}*/

/*
void ReceiveSms()
{

 //If Y==on
 if(Serial.available() >0)
 {
 inchar=Serial.read(); 
       if (inchar=='Y')
        {
            delay(10);
            //digitalWrite(led1, HIGH);
            //digitalWrite(led2,LOW);
            inchar=Serial.read();
              if(inchar=='Y')
              {
                    delay(1000);
                    Serial.println("Motor on");
                    MotorOnWaterStatus();
              } 
              
             
                   
                   
        }
      
       if (inchar=='N')
       {
            delay(10);
            inchar=Serial.read();
            //digitalWrite(led1, LOW);
            //digitalWrite(led2,HIGH);
         //           delay(10);
          if(inchar=='N')
            {
                   MotorOff();
                   Serial.println("Relay 1 low\n");
                   char status24[]="Motoroff";
                    SendMessage(status24);
            }              
        }
      
        
          
    }  
}
*/

void OutGoingCall()
{
  Serial.println("ATD8008645273");
  delay(2000);
  Serial.println("ATH0");
  delay(100);

  
}

/*
void InComingCall()
{
 
  //Serial.println("ATH");
  while(Serial.available())
  {
    if(Serial.find("NO"))
    {
      if(a==0)
      {
        MotorOnWaterStatus();
        a=1;
      }
      else
      {
        
        MotorOff();
        a=0;
        char status24[]="Motor off";
        SendMessage(status24);
        delay(200);
        
      }
    }
      
  }
  
}*/

/*
void InComingCall()
{
  if(Serial.available() >0)
    {
    delay(10); 
    inchar=Serial.read();
    if (inchar=='+')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='9')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='1')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='9')
    {           
    delay(10);
    inchar=Serial.read();
    if (inchar=='5')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='4')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='2')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='5')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='3')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='8')
    {
    delay(10);
    inchar=Serial.read();
    if (inchar=='5')
    {
          delay(10);
    inchar=Serial.read();
    if (inchar=='3')
    {
          delay(10);
    inchar=Serial.read();
    if (inchar=='4')
    {
      MotorOnWaterStatus();
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
}
*/

void MotorOn()
{
digitalWrite(relay1,HIGH);
digitalWrite(relay2,LOW);
delay(5000);

digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);

}

void MotorOff()
{
 digitalWrite(relay1,LOW);
 digitalWrite(relay2,HIGH);
 delay(5000);
 digitalWrite(relay1,LOW);
 digitalWrite(relay2,LOW);
}


void SendMessage(char sms[])
{
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.println("AT+CMGS=\"9542538534\"");
  delay(500);
 Serial.println(sms);
  delay(500);
  Serial.write(26);
  delay(500);
  Serial.println("AT+CMD=1,4");
}

void WaterOffMotorOff()
{
  WaterLevelRead();
  if((F1==0))
  {
    if(a==1)
    {
    MotorOff();
    a=0;
    char status23[]="MotorOff_due_to_Water_at_critical";
    SendMessage(status23);
    }
  }
}
