#include <Servo.h>
#include <Arduino.h>

// constant variables used to set servo angles, in degrees
const int straight = 90; 
const int divergent = 120;

// constant variables holding the ids of the pins we are using

const int buttonpin1 = 8;
const int buttonpin2 = 9;
const int servopin1 = 4;
const int servopin2 = 5;

bool button_pressed1 = false ;
bool button_pressed2 = false ;
// servo movement step delay, in milliseconds
const long step_delay = 100;

unsigned long b1_previousMillis = 0;
unsigned long b2_previousMillis = 0;
// create a servo object

Servo myservo1;
Servo myservo2;  
 
// global variables to store servo position
int pos = straight; // current
int act_pos_servo1 = pos; // current
int act_pos_servo2 = pos; // current


void setup() 
{ 
  // set the mode for the digital pins in use
  pinMode(buttonpin1, INPUT);
  pinMode(buttonpin2, INPUT);

  Serial.begin(9600);
  // setup the servo to initial position
  
  myservo1.attach(servopin1);  // attach to the servo on pin 4
  myservo1.write(pos); // set the initial servo position
  myservo2.attach(servopin2);  // attach to the servo on pin 5
  myservo2.write(pos); // set the initial servo position
  
}

void loop() 
{ 
 // Espero que algun boton sea presionado
 // y si lo es, pongo una variable en HIGH
  int button_state1 = digitalRead(buttonpin1);
  int button_state2 = digitalRead(buttonpin2);
  unsigned long currentMillis = millis(); 

  if (button_state1 == LOW){
    Serial.println("El boton numero 1 fue activado");
    button_pressed1 = true;
  }
  else if (button_state2 == LOW) {
      Serial.println("El boton numero 2 fue activado");
    button_pressed2 = true;
  }
 
  
  if(button_pressed1 == true){
  

    // Imprimo en serial que si el boton 1 fue activado y la posicion actual
    
    Serial.println(act_pos_servo1);
    Serial.println(currentMillis);
    // Si el boton 1 se toco empiezo a mover el servo 1 
  
 //   if (currentMillis - b1_previousMillis >= step_delay) {
 //     b1_previousMillis = currentMillis;
 //     Serial.println("Enre al if del currentmilis");

      if(act_pos_servo1 ==  straight){   // if the new angle is higher
        
        // increment the servo position from oldpos to pos
        for(int i = straight + 1 ; i <= divergent; i++){  
          myservo1.write(i); // write the next position to the servo
          Serial.println("Movi el servo amiwo");
          }
        act_pos_servo1 = divergent;
      }
      
    else {
       for(int b = divergent - 1 ; b >= straight; b--){  
       myservo1.write(b); // write the next position to the servo
       Serial.println("Movi para atras el servo amiwo");
       }
       act_pos_servo1 = straight;
       }
    
  }
  else if(button_pressed2 == true){
  

    // Imprimo en serial que si el boton 1 fue activado y la posicion actual
    
    Serial.println(act_pos_servo2);
    Serial.println(currentMillis);
    // Si el boton 1 se toco empiezo a mover el servo 1 
  


      if(act_pos_servo2 ==  straight){   // if the new angle is higher
        
        // increment the servo position from oldpos to pos
        for(int i = straight + 1 ; i <= divergent; i++){  
          myservo2.write(i); // write the next position to the servo
          Serial.println("Movi el servo 2 amiwo");
          }
        act_pos_servo2 = divergent;
      }
      
    else {
       for(int b = divergent - 1 ; b >= straight; b--){  
       myservo2.write(b); // write the next position to the servo
       Serial.println("Movi para atras el servo 2 amiwo");
       }
       act_pos_servo2 = straight;
       }
    
  }
//}
button_pressed1 = false;  
button_pressed2 = false;
}// end of loop