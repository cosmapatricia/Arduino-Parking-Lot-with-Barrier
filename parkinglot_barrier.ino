
#include <Servo.h>             // Include the Servo library

int servoPin = 3;                  // Declare the Servo pin  
Servo Servo1;                      // Create a servo object

int DIODE1 = 2;                  // Declare photodiode pins
int DIODE2 = 1;

int RED_LED =  4;              // Declare Led pins
int GREEN_LED = 13;

void setup() { 
     pinMode(RED_LED, OUTPUT);                 // define leds
     pinMode(GREEN_LED,OUTPUT);
     digitalWrite(GREEN_LED, HIGH);            // initialize leds: green led on
     digitalWrite(RED_LED,LOW);                   // red led off
  
    Servo1.attach(servoPin);                   // attach the servo to the used pin number 
    Servo1.write(0);
    pinMode(DIODE1, INPUT);            // define photodiodes
    pinMode(DIODE2, INPUT);
    digitalWrite(DIODE1,HIGH);          // initialzie diodes
    digitalWrite(DIODE2,HIGH);

    pinMode(5,OUTPUT);                     // define 7-segment display
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
  
    digitalWrite(5,HIGH);                     // reset all segments - OFF
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
}   

const int number[10] = {0b00000011, 0b00111111, 0b01001010, 0b00101010, 0b00110110, 0b10100010, 0b10000010, 0b00111011, 0b00000010, 0b00100010};                                  // 0-9 configurations (0 – on, 1 - off)

int parkingSpaces = 2;            // the initial number of free parking spaces
int nrMaxParkSpaces = 6;

void display_freeParkingSpaces(int x){
     int pin,b;
     for(pin = 5, b = 0; pin <=12 ; pin++, b++){ 
          digitalWrite(pin, bitRead(number[x], b));
     }
}

int diode1_val1=0, diode1_val2=0;                // in
int diode2_val1=0, diode2_val2=0;                // out

void control_parking_lot(){
//read 2 consecutive values of the diode at the entrance
     diode1_val1 = digitalRead(DIODE1);   
     diode1_val2 = digitalRead(DIODE1);

// if parkingSpaces > 0 and darker when reading val2car identified
     if (diode1_val2 - diode1_val1 == 1 && parkingSpaces){
          Servo1.write(90);             // make servo go to 90 degrees 
          delay(4000);    // barrier held up for 5sec                     
          Servo1.write(0);               // make servo go back to 0 
          parkingSpaces--;              
          display_freeParkingSpaces(parkingSpaces);
          if(!parkingSpaces){        // if parkingSpaces = 0
               digitalWrite(GREEN_LED, LOW);  //led green turns off
               digitalWrite(RED_LED, HIGH);      //red led turns on
          }
          
     }

     diode2_val1 = digitalRead(DIODE2);            // same for the second diode
     diode2_val2 = digitalRead(DIODE2);
     if (diode2_val2 - diode2_val1 == 1){
          Servo1.write(90); 
          delay(4000);         
          Servo1.write(0);
          if(parkingSpaces < nrMaxParkSpaces)                 // maximum number of parking spaces
               parkingSpaces++;
          display_freeParkingSpaces(parkingSpaces);
          if(parkingSpaces){
               digitalWrite(GREEN_LED, HIGH);       // green led turns on
               digitalWrite(RED_LED, LOW);           // red led turns off
          }
          
     }
}
   
void loop(){
     display_freeParkingSpaces(parkingSpaces);
     control_parking_lot();
}


