#include <SoftwareSerial.h>
SoftwareSerial BTserial(0,1); // RX | TX
// Connect the HC-05 TX to Arduino pin 0 RX. 
// Connect the HC-05 RX to Arduino pin 1 TX through a voltage divider.
// 
 
char c;
int p=1;    //variable for gate auto mode
int sensor1 = 2;
int sensor2 = 3;


int Time1;
int Time2;
int Time;
int flag = 0;

int distance = 27;

int Speed;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Over Speed Controlling System is ready");
  Serial.println("Press 0 to put the Barrier OFF");
  Serial.println("Press 1 to put the Barrier ON");
  Serial.println("Press 2 to put the System in Auto Mode");

  BTserial.begin(38400);

  pinMode(12, OUTPUT); //Relay
  digitalWrite(12, LOW);  //Initially off
   pinMode(11, OUTPUT); //Relay
  digitalWrite(11, LOW);  //Initially off

  attachInterrupt(0,fun1,RISING);
  attachInterrupt(1,fun2,FALLING);

  pinMode(4, OUTPUT); //LED
  digitalWrite(4, HIGH);    //LED off

  pinMode(6, OUTPUT); //
  digitalWrite(6, HIGH);
 

}

void fun1()
{
  Time1 = millis(); 
  if (flag == 0) {flag = 1;}
  else {flag = 0;}
}

void fun2()
{
  Time2 = millis();
  if (flag == 0) {flag = 1;}
  else {flag = 0;}
}



void loop() {
  // put your main code here, to run repeatedly:

 Label1:  digitalWrite(4, HIGH);
          digitalWrite(6, HIGH);


                   // Keep reading from Arduino Serial Monitor and send to HC-05
                  if (Serial.available())
                  {
                       c =  Serial.read();
                       BTserial.write(c);  
              
                       if(c=='1')
                       {
                          
                          digitalWrite(12, HIGH);
                          digitalWrite(11, LOW);// Gates on
                          p=1;
                          Serial.println("Barrier ON");
                          delay(3000);
                          digitalWrite(12, LOW);
                          digitalWrite(11, LOW);
                       }

                        else if(c=='0')
                        {
                           
                           digitalWrite(12, LOW);
                           digitalWrite(11, HIGH);//Gates off
                            p=1;
                           Serial.println("Barrier OFF");
                           delay(3000);
                           digitalWrite(12, LOW);
                           digitalWrite(11, LOW);
                        }

                        else if(c=='2')
                        {
                           p=2;
                           digitalWrite(12, LOW);
                           digitalWrite(11, LOW);
                           Serial.println("System on AUTO MODE");
                         }
                  }

                  

  if (flag == 0)
          {
                   if(Time1 > Time2)
                   {
                      Time = Time1-Time2;  
                      Speed =(distance*1000)/Time;
                     
                     }
                   else if(Time2 > Time1) 
                   {
                      Time = Time2 - Time1;  
                      Speed = (distance*1000)/Time;
                    
                    }
                   else
                   {
                      Speed = 0;
                    
                    }
          }
  
          if (Speed > 40) 
          { 
         
                     digitalWrite(4, LOW);
                     digitalWrite(6, LOW);
                     

                     if(p==2)
                     {
                          digitalWrite(12, HIGH);
                          digitalWrite(11, LOW); 
                          delay(5000);
                          digitalWrite(12, LOW);
                          digitalWrite(11, LOW);
                      }
                     
                     

                        delay(2000);
                             
                      Time1 = 0;
                      Time2 = 0;
                      Speed=0;

                      goto Label1;
           }
           

         

}
