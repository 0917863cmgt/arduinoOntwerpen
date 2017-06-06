/*-----( Import needed library )-----*/
#include <SoftwareSerial.h>  
///*-----( Declare Constants and Pin Numbers )-----*/
#define HC_05_TXD_ARDUINO_RXD 0
#define HC_05_RXD_ARDUINO_TXD 1
//#define HC_05_SETUPKEY        4
//#define HC_05_PWR1            5  // Connect in parallel to HC-05 VCC
//#define HC_05_PWR2            6  // Connect in parallel to HC-05 VCC
//
/*-----( Declare objects )-----*/
SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX

/*-----( Import LiquidCrystal library )-----*/
#include <LiquidCrystal.h>

/*-----( Declare objects )-----*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// initialize the library with the numbers of the interface pins

/*-----( Declare Variables )-----*/
const int buttonPin1 = 6;     // the number of the pushbutton pin
const int buttonPin2 = 7;     // the number of the pushbutton pin
const int buttonPin3 = 8;     // the number of the pushbutton pin
const int buttonPin4 = 9;     // the number of the pushbutton pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
int buttonState4 = 0;         // variable for reading the pushbutton status

String data;
int modulo;
int inBetween;
int endString;
int half;
String LCDBoven; 
String LCDOnder;
int Value; 
int Value2;    

#define ledRood 13
#define ledGroen 10


void setup() {

//    /*-----( Bluetooth Setup )-----*/
//
//  pinMode(HC_05_SETUPKEY, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
//  pinMode(HC_05_PWR1, OUTPUT);      // Connect in parallel to HC-05 VCC
//  pinMode(HC_05_PWR2, OUTPUT);      // Connect in parallel to HC-05 VCC
//  
//  digitalWrite(HC_05_SETUPKEY, HIGH);  // Set command mode when powering up
//  
  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
//  Serial.println("YourDuino.com HC-05 Bluetooth Module AT Command Utility V1.02");
//  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud' at bottom right");
//  Serial.println("Vcc Power Up DELAY");
//  delay(2000);
//  Serial.println("Applying VCC Power. LED should blink SLOWLY: 2 Seconds ON/OFF");
//  digitalWrite(HC_05_PWR1, HIGH); // Power VCC
//  digitalWrite(HC_05_PWR2, HIGH);  
//  delay(2000);
//  Serial.println("Enter AT commands in top window.");
//  BTSerial.begin(38400);  // HC-05 default speed in AT command mode

  /*-----( LCD Setup )-----*/

   lcd.clear();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Welcome, u are");
  lcd.setCursor(0,1);
  lcd.print("using the Flight Buddy");
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT); 
  pinMode(buttonPin3, INPUT); 
  pinMode(buttonPin4, INPUT);
  pinMode(ledRood, OUTPUT);
  pinMode(ledGroen, OUTPUT);
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft(); 
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  text1();  
}

void loop() {

  if(Serial.available() > 0)  // Send data only when you receive data:
  {
    data = Serial.readString();
    
    Serial.println(data);        //Print Value inside data in Serial monitor
 
    
    endString = data.length();

    LCDBoven = data;

    dataCheck();
    
      
  }

  
 

 // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  //  Serial.println(buttonState1);
  // Button 1
  if (buttonState1 == HIGH) {
    // turn LED on:
     Serial.println("textone"); 
    
  } else {
    // turn LED off:
    
  }

  // read the state of the pushbutton value:
  buttonState2 = digitalRead(buttonPin2);
  
  // Button 2
  if (buttonState2 == HIGH) {
    // turn LED on:
     Serial.println("texttwo"); 
  } else {
    // turn LED off:
    
  }

  // read the state of the pushbutton value:
  buttonState3 = digitalRead(buttonPin3);
  
  // Button 3
  if (buttonState3 == HIGH) {
    // turn LED on:
     Serial.println("textthree"); 
  } else {
    // turn LED off:
    
  }

  // read the state of the pushbutton value:
  buttonState4 = digitalRead(buttonPin4);
  
  // Button 4
  if (buttonState4 == HIGH) {
    // turn LED on:
     Serial.println("textfour"); 
  } else {
    // turn LED off:
    
  }

  weigh();

}

void scrollLeft(){
  delay(600);
  lcd.scrollDisplayLeft();
//  lcd.autoscroll();
  
  
}

void weigh(){
  delay(1000);
  Value = analogRead(0);
//  Value2 = analogRead(1);
   Serial.println(Value);
//   Serial.println(Value2);

  
  
}



void lock(){
  if(data == "1"){
            digitalWrite(ledRood, HIGH);
            digitalWrite(ledGroen, LOW);
            
      }  else if (data == "0"){
            digitalWrite(ledRood, LOW);
            digitalWrite(ledGroen, HIGH);
            
      }

      else if (data == "-1"){
            digitalWrite(ledRood, LOW);
            digitalWrite(ledGroen, LOW);
            
      }
}

void dataCheck(){
  if (endString < 3) {
    Serial.println("<3");
      lock();
    }
              
    else if(endString < 16){
                LCDBoven = data;
                LCDOnder = "";
                text2();
                Serial.println(LCDBoven);
                Serial.println("<16");
               

                
    }
     else if(endString < 32){               
                modulo = endString % 16;
                inBetween = endString - modulo;
                LCDBoven = data.substring(0,inBetween);
                LCDOnder = data.substring(inBetween,endString);
                Serial.println(endString);
                Serial.println(">16");
                Serial.println(LCDBoven);
                Serial.println(LCDOnder);
                text2();
                
            }
     else if(endString > 32){
                half = endString / 2;
                LCDBoven = data.substring(0,half);
                LCDOnder = data.substring(half,endString);
                Serial.println(endString);
                Serial.println(">32");
                Serial.println(LCDBoven);
                Serial.println(LCDOnder);
                text2();
                
                
//                switch (data2) {
//                  case  2:
//                  text1();
//                  break;
//                  case  3:
//                  text2();
//                  break;
//                  case  4:
//                  text3();
//                  break;
//                  case  5:
//                  text4();
//                  break;
//                }
              }
}

void text1() {

  //lcd clear characters
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  lcd.print(data);
  lcd.setCursor(0,1);
}

void text2() {
  
  //lcd clear characters
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  lcd.print(LCDBoven);
  lcd.setCursor(0,1);
  lcd.print(LCDOnder);
  
}

void text3() {  
  
  //lcd clear characters
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  lcd.print("");
//  lcd.setCursor(0,1);
//  lcd.print("Flight Buddy te openen");
}

void text4() {
  
  //lcd clear characters
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  lcd.print("Uw Flight Buddy");
  lcd.setCursor(0,1);
  lcd.print("weegt: 10 Kilo");
}



