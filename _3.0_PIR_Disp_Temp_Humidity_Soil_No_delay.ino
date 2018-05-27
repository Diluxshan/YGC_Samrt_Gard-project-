
//.......................................##########  UNIQUE PARTNERS  ##########........................................ 

// A6 - Soil Moistrure
// A7 - Water Level
// D7 - PIR 
// D2 - DHT
// D13- Water level LED
// D12- Soil Moistrure level LED
// D30- Relay pin 1 >>---------11 change to 30
// D31- Relay pin 2

//.........................................................................................................................

//Library for Display
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Library for DHT sensor
#include<dht.h>
dht DHT;
#define DHT11_PIN 2  //pin for DHT sensor

// Out for PIR sensor
int pir = 7;

// ....................................................DHT sensor..................................................
class A{ public:
  void f()
  {
   int chk = DHT.read11(DHT11_PIN);
   //if( DHT.humidity>0 && DHT.temperature>0  )
   {

   Serial.print("Temparature ");
   Serial.print(DHT.temperature, 1); 
         lcd.setCursor(0,0);   // Column+1 - Row+1
         lcd.print("T:");
         lcd.print(DHT.temperature, 1);
         lcd.print(" C");
  
   Serial.print("\t Humidity " );
   Serial.print(DHT.humidity, 2);
   Serial.print("%");
         lcd.setCursor(0,1);   // Column+1 - Row+1
         lcd.print("H:");
         lcd.print(DHT.humidity, 2);
         lcd.print("%");
  }
  }
  };

//..........................................Sooil Moistrue sensor......................................................
class B{ public:
  void f()
  {
   Serial.print("\t Moisture:");
   Serial.print(analogRead(6));
        lcd.setCursor(10,0);   // Column+1 - Row+1
        lcd.print("S:");
        lcd.print(analogRead(6));

    if(analogRead(6)>700)
  { digitalWrite(12,HIGH);  //white led
           
    digitalWrite(30,LOW);   //motor relay
  }
  else{ 
    digitalWrite(12,LOW);
    digitalWrite(30,HIGH);
  }
  }
  };

// ................................................Water level sensor..................................................
class C{ public:
  void f()
  {
   Serial.print("\t\t Water:");
   Serial.println(analogRead(7));
          lcd.setCursor(10 ,1);   // Column+1 - Row+1
          lcd.print("W:");
          lcd.print(analogRead(7));
          
   if(analogRead(7)<200)
  {   
    digitalWrite(13,HIGH); 
  
    digitalWrite(31,LOW); 
    delay(100);
    digitalWrite(31,HIGH); 
    delay(100);
  }
  
 else if(analogRead(7)>600)
 {
   digitalWrite(13,LOW); 
   digitalWrite(31,HIGH); 
  }
 }
  
  };
 

// ..................................Method for call class......................................................
A *a;
B *b;
C *c;  
//...............................................................................................................

void setup() {
    pinMode(pir , INPUT);
     
   lcd.init();                     
   lcd.init();
   
  
   a=new A(); 
   b=new B();
   c=new C();
   
   Serial.begin(19200);

   pinMode(11,OUTPUT); // Green LED - System full ok 

   pinMode(13,OUTPUT); // Motor light (red)  - Water level 
   pinMode(12,OUTPUT); // Motor light(white) - Soil moistrue motor

   pinMode(30,OUTPUT); // Motor Relay - Soil Moistrue level 
   pinMode(31,OUTPUT); // Motor Relay - Water level 
   
   
}

//............................................................................................................

void loop() {  
   boolean buttonState = digitalRead(pir);
       if (buttonState == 1)
       {   lcd.backlight();      
         //  Right(5000);
       }
       else{lcd.noBacklight();}  // No any action
        
  a->f();   
  b->f();  
  c->f();
   delay(300);

   if(analogRead(6)<700  || analogRead(7)>600)
   {  digitalWrite(11,HIGH);  }

    else{digitalWrite(11,LOW);}
}

//.............................................................................................................
// delay time for water level
void Right (int interval){
   static long prevMill = 0;
   if (((long)millis() - prevMill) >= interval){ 
    prevMill = millis(); 
    digitalWrite(12, !digitalRead(12));
  }
 }
