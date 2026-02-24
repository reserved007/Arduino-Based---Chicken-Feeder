#include <virtuabotixRTC.h> //Library used
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Servo.h>
Servo myservo; 

virtuabotixRTC myRTC(3, 4, 5); //If you change the wiring change the pins here also
LiquidCrystal_I2C lcd(0x27,16,2);  /*I2C scanned address defined + I2C screen size*/

const int SetSW = A0;
const int NextSw = A1;
const int UpSw = A2;
const int DownSw = A3;

const int relay1 = 6;
const int relay2 = 7;
int pos = 0;


int buttonState1;             // the current reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin
int buttonState2;             // the current reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin

//int ledState = HIGH;         // the current state of the output pin
int buttonState3;             // the current reading from the input pin
int lastButtonState3 = LOW;   // the previous reading from the input pin
int buttonState4;             // the current reading from the input pin
int lastButtonState4= LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay1 = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay2 = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime3 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay3 = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime4 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay4 = 50;   

bool start = false;
int addr1 = 0;
int addr2 = 2;
int addr3 = 4;
int addr4 = 6;
int addr5 = 8;
int addr6 = 10;
int addr7 = 12;
int addr8 = 14;
int addr9 = 16;
int addr10 = 18;

bool schedule_start = false;
bool week_set = false;
bool day_set = false;
bool hour_set = false;
bool min_set = false;
bool sec_set = false;

bool schedule_start2 = false;
bool week_set2 = false;
bool day_set2 = false;
bool hour_set2 = false;
bool min_set2 = false;
bool sec_set2 = false;
bool feed1_done = false;
bool feed2_done = false;

int i,j;
int n1,n2,n3,n4,n5; // hr:min:sec
int m1,m2,m3,m4,m5; // hr:min:sec
int o1,o2;// duration
extern volatile unsigned long timer0_millis;

bool debug = false;

void setup() {
    Serial.begin(9600);
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("LCD OK");
    lcd.clear();    
    delay(2000);
  // Set the current date, and time in the following format:
 // seconds, minutes, hours, day of the week, day of the month, month, year
   // myRTC.setDS1302Time(00, 48, 19, 3, 9, 04, 2024); //Here you write your actual time/date as shown above 

    pinMode(SetSW, INPUT_PULLUP);    
    pinMode(NextSw, INPUT_PULLUP);    
    pinMode(UpSw, INPUT_PULLUP);    
    pinMode(DownSw, INPUT_PULLUP);   
    pinMode(relay1, OUTPUT);
        pinMode(relay2, OUTPUT);
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    myservo.attach(9); 


   n1 = EEPROM.read(addr1);
   n2 = EEPROM.read(addr2);
   n3 = EEPROM.read(addr3);
   n4 = EEPROM.read(addr4);

  Serial.print(n1);
  Serial.print(",");
  Serial.print(n2);
  Serial.print(",");
  Serial.print(n3);
  Serial.print(",");
  Serial.println(n4);


   m1 = EEPROM.read(addr5);
   m2 = EEPROM.read(addr6);
   m3 = EEPROM.read(addr7);
   m4 = EEPROM.read(addr8);
   o1 = EEPROM.read(addr9);
   o2 = EEPROM.read(addr10);
  Serial.print(m1);
  Serial.print(",");
  Serial.print(m2);
  Serial.print(",");
  Serial.print(m3);
  Serial.print(",");
  Serial.println(m4);

   lcd.setCursor(0, 0);
   lcd.print("Please Set Time");
   lcd.setCursor(0, 1);
   lcd.print("Start");
   lcd.print(" Set");
   lcd.print(" (+)");
   lcd.print("(-)");
    myservo.write(0);
    delay(1000);


}
void loop() {
  // myservo.write(90);


    if(start){
    myRTC.updateTime();
    lcd.setCursor(0, 0);

        lcd.print("NowTime:");
        //lcd.setCursor(5, 0);
        lcd.print(myRTC.hours);
        //lcd.setCursor(7, 0);
        lcd.print(":");         
        //lcd.setCursor(8, 0);  
        lcd.print(myRTC.minutes);    
        //lcd.setCursor(10, 0);      
        lcd.print(":");    
        //lcd.setCursor(11, 0);     
        lcd.print(myRTC.seconds);
    }
    if(debug){
       Serial.print("Current Date / Time: ");
       Serial.print(myRTC.month);
       Serial.print("/");
       Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
       Serial.print("/");
       Serial.print(myRTC.year);
       Serial.print(" ");
       Serial.print(myRTC.hours);
       Serial.print(":");
       Serial.print(myRTC.minutes);
       Serial.print(":");
       Serial.print(myRTC.seconds);
       Serial.print("Day of Week:");
       Serial.println(myRTC.dayofweek);
       //delay(1000);
    }

        
      if(start ){      
        lcd.setCursor(0, 1);           
        lcd.print("F.Time :");
        //lcd.setCursor(9, 1);
        if(myRTC.hours <=12){
          lcd.print(n1);
          //lcd.setCursor(11, 1);
          lcd.print(":");
          //lcd.setCursor(12, 1);
          lcd.print(n2);
          //lcd.setCursor(14, 1);
          lcd.print(":");
          //lcd.setCursor(15, 1);
          lcd.print(n3);
           lcd.print("  ");
        }else if(myRTC.hours >12){
          lcd.print(m1);
          //lcd.setCursor(11, 1);
          lcd.print(":");
          //lcd.setCursor(12, 1);
          lcd.print(m2);
          //lcd.setCursor(14, 1);
          lcd.print(":");
          //lcd.setCursor(15, 1);
          lcd.print(m3);
           lcd.print("  ");
          
        }
      }
    
      if(hour_set & min_set & sec_set){
        schedule_start = true;
         hour_set=false;
         min_set=false;
         sec_set=false;
        lcd.clear();
        delay(2000);
        lcd.print("feeding starts");
        delay(2000);
      }else if(hour_set2 & min_set2 & sec_set2){
        schedule_start2 = true;
        hour_set2=false;
        min_set2=false;
        sec_set2=false;
        lcd.clear();
        delay(2000);
        lcd.print("feeding2 starts");
        delay(2000);
        Serial.println("feeding starts2");  
      }

      
      if(start & schedule_start &!feed1_done){ // feeding starts [morning]
         timer0_millis=0;
         myservo.write(90);
         delay(o1*1000);
         myservo.write(0);
         delay(1000);
         digitalWrite(relay1,LOW);
         delay(o2*1000);
         //delay(1000);
         digitalWrite(relay1,HIGH);
         //schedule_start =false;
         feed1_done =true;
         Serial.println("feeding starts21");
      }else if(start & schedule_start2 & !feed2_done){ // feeding starts [morning]
         timer0_millis=0;
         myservo.write(90);
         delay(o1*1000);
         myservo.write(0);
         delay(1000);
         digitalWrite(relay1,LOW);
         delay(o2*1000);
         //delay(1000);
         digitalWrite(relay1,HIGH);
         //schedule_start2 =false;
         feed2_done =true;

         Serial.println("feeding starts22");
      }

     
  if(myRTC.hours == 23 & myRTC.minutes == 59){
         schedule_start2 =false;
         schedule_start =false;
              feed1_done =false;     
     feed2_done =false;
//              hour_set=false;
//         min_set=false;
//         sec_set=false;
  }else if(schedule_start & schedule_start2){
         schedule_start2 =false;
         schedule_start =false;
              feed1_done =false;     
     feed2_done =false;
//             hour_set2=false;
//        min_set2=false;
//        sec_set2=false;
  }


/* n1 = hour, n2 = min, n3 = sec , n4 = day*/
if(start & !schedule_start){
  if(myRTC.dayofweek == n4 & !day_set){ // noused
    day_set = true;
    Serial.println("Day Set");
  }
  if(myRTC.hours == n1 & !hour_set){
    hour_set = true;
    Serial.println("Hour Set");
  }
  if(myRTC.minutes == n2 & !min_set){
    min_set = true;
    Serial.println("Min Set");
  }
  if(myRTC.seconds == n3 & !sec_set){
    sec_set = true;
    Serial.println("Sec Set");
  }
}

if(start & !schedule_start2){
  if(myRTC.dayofweek == m4 & !day_set2){ // no used
    day_set2 = true;
    Serial.println("Day Set2");
  }
  if(myRTC.hours == m1 & !hour_set2){
    hour_set2 = true;
    Serial.println("Hour Set2");
  }
  if(myRTC.minutes == m2 & !min_set2){
    min_set2 = true;
    Serial.println("Min Set2");
  }
  if(myRTC.seconds == m3 & !sec_set2){
    sec_set2 = true;
    Serial.println("Sec Set2");
  }
}




  int reading1 = digitalRead(SetSW);
  int reading2 = digitalRead(NextSw);
  int reading3 = digitalRead(UpSw);
  int reading4 = digitalRead(DownSw); 

  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();

  }

/*SAVED Button*/

  if ((millis() - lastDebounceTime1) > debounceDelay1) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

        if (buttonState1 == HIGH) {
            if(n1==0 & n2 ==0 & n3==0){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Abnormal Data");
            lcd.setCursor(0, 1);
            lcd.print("Please set again");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Please Set Time");
            lcd.setCursor(0, 1);
            lcd.print("Start");
            lcd.print(" Set");
            lcd.print(" (+)");
            lcd.print("(-)");
            start = false;
            schedule_start=false;
            hour_set=false;
            min_set=false;
            sec_set=false;
            schedule_start2=false;
            hour_set2=false;
            min_set2=false;
            sec_set2=false;

            i=0; 
             timer0_millis=0;
            }else{
            start = true;
            //set = false; 
            i=0; 
            schedule_start=false;
            hour_set=false;
            min_set=false;
            sec_set=false;
            schedule_start2=false;
            hour_set2=false;
            min_set2=false;
            sec_set2=false;
     feed1_done =false;     
     feed2_done =false;
            Serial.println("SAVED!   ");
            lcd.setCursor(0, 0);
            EEPROM.write(addr1, n1);
            EEPROM.write(addr2, n2);
            EEPROM.write(addr3, n3);
            EEPROM.write(addr4, n4);
            EEPROM.write(addr5, m1);
            EEPROM.write(addr6, m2);
            EEPROM.write(addr7, m3);
            EEPROM.write(addr8, m4);
            EEPROM.write(addr9, o1);
            EEPROM.write(addr10,o2);
            lcd.clear();
            lcd.print("DATA SET!!    ");

            timer0_millis=0;
            delay(2000);

        }
        }
    }
  }

/*NEXT Button*/
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();

  }

    if ((millis() - lastDebounceTime2) > debounceDelay2) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == HIGH) {
        i++;
         if(8< i){
          i=0;
         }
        Serial.print("i:");
        Serial.println(i);
        start = false;
        //set = true; 
        
        digitalWrite(relay1,HIGH);
        digitalWrite(relay2,HIGH);

        if(i ==1 ){
    
            lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("Set Hour(AM):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(n1);
            lcd.print("    ");

        }else if(i ==2){
            lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("Set Min(AM):");
    //        lcd.setCursor(0,1);
    //       lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(n2);
            lcd.print("    ");

        }else if(i ==3){
            lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("Set Sec(AM):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(n3);
            lcd.print("     ");

        }else if(i ==4){
            lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("Set Hour(PM):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(m1);
            lcd.print("    ");
        }else if(i ==5){
           lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("Set Min(PM):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(m2);
            lcd.print("     ");
        }else if(i ==6){
           lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("Set Sec(PM):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(m3);
            lcd.print("     ");

        }else if(i ==7){
           lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("F.Time(Sec):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(o1);
            lcd.print("     ");

        }else if(i ==8){
           lcd.clear();
            delay(500);
            lcd.setCursor(0,0);
            lcd.print("W.Time(Sec):");
    //        lcd.setCursor(0,1);
    //        lcd.print("  ");
    //        lcd.setCursor(0,1);
            lcd.print(o2);
            lcd.print("     ");

        }
        
        

      }
    }
  }

  /*(+) Button*/
  if (reading3 != lastButtonState3) {
    // reset the debouncing timer
    lastDebounceTime3 = millis();

  }

  if ((millis() - lastDebounceTime3) > debounceDelay3) {
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

      if (buttonState3 == HIGH) {
      if(i ==1 ){    
          if(n1>11)n1=0; //Hours
          else n1++;
          lcd.setCursor(0,1);
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(n1);
          lcd.print("     ");
        }else if(i ==2){
          if(n2>59)n2=0; //minutes
          else n2++;
          lcd.setCursor(0,1); 
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(n2);  
          lcd.print("     ");
        }else if(i ==3){
          if(n3>59)n3=0; //Seconds
          else n3++;;
          lcd.setCursor(0,1); 
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(n3);    
          lcd.print("     ");
        }else if(i ==4){
          if(m1>23)m1=13; //Hours
          else m1++;
          lcd.setCursor(0,1);
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(m1);
          lcd.print("     ");
        }else if(i ==5){
          if(m2>59)m2=0; //minutes
          else m2++;
          lcd.setCursor(0,1); 
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(m2);  
          lcd.print("     ");
        }else if(i ==6){
          if(m3>59)m3=0; //Seconds
          else m3++;;
          lcd.setCursor(0,1); 
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(m3);    
          lcd.print("     ");
        }else if(i ==7){
          if(o1>10)o1=0; //Seconds
          else o1++;;
          lcd.setCursor(0,1); 
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(o1);    
          lcd.print("     ");
        }else if(i ==8){
          if(o2>10)o2=0; //Seconds
          else o2++;
          lcd.setCursor(0,1); 
          lcd.print("     ");
          lcd.setCursor(0,1);
          lcd.print(o2);    
          lcd.print("     ");
        }
  
      }
    }
  }

  /*(-) Button*/

  if (reading4 != lastButtonState4) {
    // reset the debouncing timer
    lastDebounceTime4 = millis();

  }

  if ((millis() - lastDebounceTime4) > debounceDelay4) {
    if (reading4 != buttonState4) {
      buttonState4 = reading4;

        if (buttonState4 == HIGH) {
      
              if(i ==1 ){ 
                n1--;
                if(n1<0) n1=24;
                lcd.setCursor(0,1);
                lcd.print(n1);
                lcd.print("     ");
              }else if(i ==2){     
                n2--;
                if(n2<0) n2=59;          
                lcd.setCursor(0,1); 
                lcd.print(n2); 
                lcd.print("     "); 
              }else if(i ==3){
                n3--;
                if(n3<0) n3=59;     
                lcd.setCursor(0,1); 
                lcd.print(n3);   
                lcd.print("     "); 
              }else if(i ==4 ){ 
                m1--;
                if(m1<0) m1=24;
                lcd.setCursor(0,1);
                lcd.print(m1);
                lcd.print("     ");
              }else if(i ==5){     
                m2--;
                if(m2<0) m2=59;          
                lcd.setCursor(0,1); 
                lcd.print(m2);  
                lcd.print("     ");
              }else if(i ==6){
                m3--;
                if(m3<0) m3=59;     
                lcd.setCursor(0,1); 
                lcd.print(m3);
                lcd.print("     ");    
              }else if(i ==7){
                o1--;
                if(o1<0) o1=10;     
                lcd.setCursor(0,1); 
                lcd.print(o1);
                lcd.print("     ");    
              }else if(i ==8){
                o2--;
                if(o2<0) o2=10;     
                lcd.setCursor(0,1); 
                lcd.print(o2);
                lcd.print("     ");    
              }

        }           

      }
    }


  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
  lastButtonState4 = reading4;
      
  //delay(250);

}
