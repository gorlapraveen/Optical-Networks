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
char pos;


float PS;
int f1=7;
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
  pinMode(f1,INPUT_PULLUP);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  Serial.print("pin state low\n");
 delay(300);
 if (gsm.begin(9600))
   Serial.println("\nstatus=READY");
 else Serial.println("\nstatus=IDLE");

 
 
 PowerOn();
 //addnumber();
 
}

void loop()
{
  
 WaterLevelRead();
 WaterOffMotorOff();
 InComingCall();
 ReceiveSms();

}


void PowerOn()
{

 WaterLevelStatus();
 //OutGoingCall();
 
}

void WaterLevelRead()
{
 F1=digitalRead(f1);

 
}

void WaterLevelStatus()
{
  WaterLevelRead();
   {
    if((F1==1))
    { char status10[]="PowerAvailable_Water_is_There";
      
      sms.SendSMS(1,status10);
      sms.SendSMS(number,status10);
      sms.SendSMS("8008645273",status10);
      delay(2000);
      gsm.SimpleWrite("AT+CMD=1,4");
    }
    
   else if((F1==0))
    {
      char status12[]="PowerAvailable_and_Water_critical";
      sms.SendSMS(1,status12);
     sms.SendSMS(number,status12) ;
      sms.SendSMS("8008645273",status12);
     MotorOff();
     delay(200);
     gsm.SimpleWrite("AT+CMD=1,4");
     
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
                           sms.SendSMS("8008645273",status21);
                          delay(200);
                          gsm.SimpleWrite("AT+CMD=1,4");
                         }
                      
                      else if((F1==0))
                         {
                           MotorOff();
                           a=0;
                           char status23[]="MotorOff_due_to_Water_at_critical";
                           sms.SendSMS(number,status23);
                            sms.SendSMS("8008645273",status23);
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
     sms.SendSMS("8008645273",status23);
    }
  }
}


void InComingCall()
{
   stat=call.CallStatusWithAuth(number,1,100);
  
  if(stat==CALL_INCOM_VOICE_AUTH){
   
    call.HangUp();
    delay(200);
    
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
         sms.SendSMS("8008645273",status24);
        delay(200);
        gsm.SimpleWrite("AT+CMD=1,4");
        return;
        
      }
    
  }
  delay(100);
}
//void addnumber()
//{
  
//}

void ReceiveSms()

{
  pos=sms.IsSMSPresent(SMS_UNREAD);
  Serial.println((int)pos);
  if (GETSMS_AUTH_SMS == sms.GetAuthorizedSMS((int)pos, number, smstext, 100, 1, 100)) 

  { Serial.println("your number is authorised");
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
         sms.SendSMS("8008645273",status24);
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
         sms.SendSMS("8008645273",status24);
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



