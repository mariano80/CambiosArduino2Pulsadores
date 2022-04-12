#include <Servo.h>
#include <Arduino.h>

// constant variables used to set servo angles, in degrees
const int straight = 90; 
const int divergent = 120;

// constant variables holding the ids of the pins we are using
const int divergent_led = 7;
const int straight_led = 6;
const int buttonpin1 = 8;
const int buttonpin2 = 4;
const int servopin = 9;

// servo movement step delay, in milliseconds
const long step_delay = 100;
unsigned long b1_previousMillis = 0;
unsigned long b2_previousMillis = 0;
// create a servo object
Servo myservo;  
 
// global variables to store servo position
int pos = straight; // current

void setup() 
{ 
  // set the mode for the digital pins in use
  pinMode(buttonpin1, INPUT);
  pinMode(buttonpin2, INPUT);
  pinMode(straight_led, OUTPUT);
  pinMode(divergent_led, OUTPUT);
  Serial.begin(9600);
  // setup the servo
  myservo.attach(servopin);  // attach to the servo on pin 9
  myservo.write(pos); // set the initial servo position
  
  // set initial led states
   digitalWrite(straight_led, HIGH);
   digitalWrite(divergent_led, LOW);
}

void loop() 
{ 
 // Espero que algun boton sea presionado
 // y si lo es, pongo una variable en HIGH
  int button_state1 = digitalRead(buttonpin1);
  int button_state2 = digitalRead(buttonpin2);
  unsigned long currentMillis = millis(); 

  if(button_state1 == HIGH){
    
    // turn off the lit led
    Serial.println("El boton straigth fue activado");
    if(pos == straight){
              digitalWrite(straight_led, LOW);
          } else {
              digitalWrite(divergent_led, LOW);
          }
       // Move the servo to its new position
    Serial.println(pos);

    if (currentMillis - b1_previousMillis <= step_delay) {
      b1_previousMillis = currentMillis;
      if(pos ==  straight){   // if the new angle is higher
        
        // increment the servo position from oldpos to pos
        for(int i = straight + 1 ; i <= divergent; i++){  
          myservo.write(i); // write the next position to the servo
          }
 
    
      } 
    else {pos = divergent;}
    }
      // turn on the appropriate LED.
    if(pos == straight){
            digitalWrite(straight_led, HIGH);
        } else {
            digitalWrite(divergent_led, HIGH);
       }
  }
 
  if(button_state2 == HIGH){
    Serial.println("El boton divergent fue activado");
    // turn off the lit led
    if(pos == straight){
              digitalWrite(straight_led, LOW);
          } else {
              digitalWrite(divergent_led, LOW);
          }
       // Move the servo to its new position
    Serial.println(pos);
    
    if (currentMillis - b2_previousMillis <= step_delay) {
      b2_previousMillis = currentMillis;
      if(pos ==  divergent){   // if the new angle is higher
        pos = straight;
      // increment the servo position from oldpos to pos
        for(int b = divergent - 1 ; b >= straight; b--){  
          myservo.write(b); // write the next position to the servo
          delay(step_delay); // wait
       }
      }  
    else {pos = divergent;}
    }
    // turn on the appropriate LED.
    if(pos == straight){
            digitalWrite(straight_led, HIGH);
        } else {
            digitalWrite(divergent_led, HIGH);
       }
  }
     
}// end of loop