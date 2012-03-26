/*
  Blink
  
  This example is based on Arduino blink example and it demonstrates 
  use of preprocessor directives for conditional compilation in SEMB 2011 project.
  
  The code below icnludes the actual blinking functionality when compiled
  for Arduino, while compilation for PC replaces it with print outs.
  
  ARDUINO and PC are defined automatically during compilation using project's makefile.  
  
 */

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif


void setup() {                

#ifdef ARDUINO // Arduino code
   // initialize the digital pin as an output.
   // Pin 13 has an LED connected on most Arduino boards:
   pinMode(13, OUTPUT);
  
#elif defined PC // PC code
   printf("%s\n", "Pin 13 mode = output");
   	
#endif
      
}

void loop() {

#ifdef ARDUINO // Arduino code
  digitalWrite(13, HIGH);   // set the LED on
  delay(500);               // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(100);               // wait for a second

#elif defined PC // PC code
   printf("%s\n", "Set pin 13\t ON\t for 500 ms");
   printf("%s\n", "Set pin 13\t OFF\t for 500 ms"); 
#endif
}

int main(void)
{

#ifdef ARDUINO // Arduino code
  init(); // init the Arduino hardware
#endif

  setup();

  for (;;)
    loop();

  return 0;
}
