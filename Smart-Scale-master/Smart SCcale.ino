/* Basic Digital Read
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13, when pressing a pushbutton attached to pin 7. It illustrates the
 * concept of Active-Low, which consists in connecting buttons using a
 * 1K to 10K pull-up resistor.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */


#include <LiquidCrystal.h>          //the liquid crystal libarry contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display
 
const int FLEX_PIN = A0; // Pin connected to voltage divider output
int ledPin = 5; // choose the pin for the LED
int ledPin2 = 4; // choose the pin for the LED
int inPin = 7;   // choose the input pin (for a pushbutton)
int inPin2 = 6;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status
int val2 = 0;     // variable for reading the pin status

float full=800;
float low=150;
float percent=256;



void setup() {

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display

    
  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input
  pinMode(ledPin2, OUTPUT);  // declare LED2 as output
  pinMode(inPin2, INPUT);    // declare pushbutton2 as input
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
}

void loop(){


  lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
  lcd.print(String(percent) + "% full\0");       //print hello, world! starting at that position

  
  // Read the ADC, and calculate voltage and resistance from it
  int current = analogRead(FLEX_PIN);
//  float current = flexADC * VCC / 1023.0;
  
  float  percent_new = map(current, low, full,0, 100.0);

  if (abs(percent_new-percent)>3){
    percent=percent_new;
  }
   
  if(percent<0){
    percent=0.0;
  }
  if(percent>100){
    percent=100.0;
  }



  

  Serial.println(String(full) + " full");
  Serial.println(String(current) + " current");
  Serial.println(String(percent) + "%full");
  Serial.println("          ");
  Serial.println("          ");

  delay(500);
  val = digitalRead(inPin);  // read input value
  val2 = digitalRead(inPin2);  // read input value



  
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(100);
    digitalWrite(ledPin, LOW);  // turn LED ON
    delay(100);
    digitalWrite(ledPin, HIGH);  // turn LED ON
        
    full=current;
    percent=percent_new;
    
    Serial.println("Full Item");
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("FULL Set");        
    
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF
    
  }


  if (val2 == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin2, HIGH);  // turn LED ON
    delay(100);
    digitalWrite(ledPin2, LOW);  // turn LED ON
    delay(100);
    digitalWrite(ledPin2, HIGH);  // turn LED ON
        
    low=current;
    percent=percent_new;
    
    Serial.println("LOW Set");
    lcd.setCursor(0,1);               //mvoe the cursor to the first space of the bottom row
    lcd.print("LOW Set"); 
  
    
  } else {
    digitalWrite(ledPin2, LOW);  // turn LED OFF
  }


  
}
 
