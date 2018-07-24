#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include "call.h"

CallGSM call;
SMSGSM sms;

char number[20];
byte stat=0;
int value=0;
int pin=1;
char smstext[100];
char value_str[5];
char mon0[]="YY",mon1[]="Yy",mon2[]="yy",mon3[]="yY",mof0[]="NN",mof1[]="Nn",mof2[]="nn",mof3[]="nN";
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
 delay(30000);
 Serial.println("AT+CMGF=1"); // set SMS mode to text
 delay(200);
 Serial.println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt
 delay(200);
 
 PowerOn();
 
}

void loop()
{
  // set module to send SMS data to serial out upon receipt
 WaterLevelRead();
 WaterOffMotorOff();
 InComingCall();
 ReceiveSms();

}

/*void serialEvent()
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
                    sms.SendSMS(status24);
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
        sms.SendSMS(status24);
        delay(200);
        return;
        
      }
   
    }
             
            
        }
      
        
 
    
  }
   
 }
 */

void PowerOn()
{

 WaterLevelStatus();
 //OutGoingCall();
 
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
      sms.SendSMS(number,status10);
      delay(2000);
      gsm.SimpleWrite("AT+CMD=1,4");
    }
    
   else if((F1==0))
    {
      char status12[]="PowerAvailable_and_Water_critical";
     sms.SendSMS(number,status12) ;
     MotorOff();
     delay(200);
     gsm.SimpleWrite("AT+CMD=1,4");
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
                          sms.SendSMS(number,status21);
                          delay(2000);
                          gsm.SimpleWrite("AT+CMD=1,4");
                         }
                      
                      else if((F1==0))
                         {
                           MotorOff();
                           a=0;
                           char status23[]="MotorOff_due_to_Water_at_critical";
                           sms.SendSMS(number,status23);
                           gsm.SimpleWrite("AT+CMD=1,4");
                         }
                    }  
 
}


void OutGoingCall()
{
  Serial.println("ATD9542538534");
  delay(2000);
  Serial.println("ATH0");
  delay(100);

 
}

void MotorOn()
{
digitalWrite(relay1,HIGH);
digitalWrite(relay2,LOW);
delay(3000);

digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);

}

void MotorOff()
{
 digitalWrite(relay1,LOW);
 digitalWrite(relay2,HIGH);
 delay(3000);
 digitalWrite(relay1,LOW);
 digitalWrite(relay2,LOW);
}

/*
void sms.SendSMS(char msg[])
{
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.println("AT+CMGS=\"9542538534\"");
  delay(500);
 Serial.println(msg);
  delay(500);
  Serial.write(26);
  delay(500);
  Serial.println("AT+CMD=1,4");
}
*/
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
    sms.SendSMS(number,status23);
    }
  }
}


void InComingCall()
{
   stat=call.CallStatusWithAuth(number,1,3);
  //If the incoming call is from an authorized number
  //saved on SIM in the positions range from 1 to 3.
  if(stat==CALL_INCOM_VOICE_AUTH){
    //Hang up the call.
    call.HangUp();
    delay(2000);
    //Check the value of the input.
    //value=digitalRead(1);
    //Convert the int to a string.
    //itoa(value,value_str,10);
    //Send an SMS to the previous number with
    //the value read previously.
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
        sms.SendSMS(number,status24);
        delay(200);
        gsm.SimpleWrite("AT+CMD=1,4");
        return;
        
      }
    //sms.SendSMS(number,value_str);
  }
  delay(1000);
}

void ReceiveSms()
{
  if (GETSMS_AUTH_SMS == sms.GetAuthorizedSMS(1, number, smstext, 100, 1, 3)) 

  { 
    if((smstext == mon0)||(smstext == mon1)||(smstext == mon2)||(smstext == mon3))
    {
      MotorOnWaterStatus();
        a=1;
        return;
        
    }
    if((smstext == mof0)||(smstext == mof1)||(smstext == mof2)||(smstext == mof3))
    {
     MotorOff();
        a=0;
        char status24[]="Motor off";
        sms.SendSMS(number,status24);
        delay(200);
        gsm.SimpleWrite("AT+CMD=1,4");
        return; 
    }
    if((!strcmp(smstext,mon0))||(!strcmp(smstext,mon1))||(!strcmp(smstext,mon2))||(!strcmp(smstext,mon3)))
    {
      MotorOnWaterStatus();
        a=1;
        return;
      
    }
    if((!strcmp(smstext,mof0))||(!strcmp(smstext,mof1))||(!strcmp(smstext,mof2))||(!strcmp(smstext,mof3)))
    {
     MotorOff();
        a=0;
        char status24[]="Motor off";
        sms.SendSMS(number,status24);
        delay(200);
        gsm.SimpleWrite("AT+CMD=1,4");
        return;
        
    }
   
 else
 {
   gsm.SimpleWrite("AT+CMD=1,4");
 }

  }


}


