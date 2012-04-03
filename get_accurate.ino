/* Ping))) Sensor
  
   This sketch reads a PING))) ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
     
   The circuit:
	* +V connection of the PING))) attached to +5V
	* GND connection of the PING))) attached to ground
	* SIG connection of the PING))) attached to digital pin 7

   http://www.arduino.cc/en/Tutorial/Ping
   
   created 3 Nov 2008
   by David A. Mellis
   modified 30 Aug 2011
   by Tom Igoe
 
   This example code is in the public domain.

 */

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 7;
 long average_value=0;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{ 
  int j;
  long i=0.0;
  long sum=0;
  for(j = 0; j<5; j++){
      i = readSensor();
      sum +=i;
      
  }
  average_value = sum/5;
  
  Serial.print("accurate value");
  Serial.print(average_value);
  Serial.print("cm");
  Serial.println();
  delay(193);
}

long readSensor(){
  long duration,cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  //accurate_value = average(cm);
  //printf("Sonar accurate %d\n",accurate_value);
  
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  return cm;
  
  }
  

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}


