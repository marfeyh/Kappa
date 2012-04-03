/* Sonar Sensor
  
  Author: Feiyi SU  Qingju Luo
  Usage: This is for getting accurate data.  get 5 times per second and get average value
  Reference: This code refers from Arduino Example codes PIng

 */

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 7;
 float average_value=0.0;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{ 
  int j;
  float i=0.0;
  float sum=0;
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

float readSensor(){
  float duration,cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  return cm;
  
  }
  

float microsecondsToCentimeters(float microseconds)
{
  return microseconds / 29/ 2;
}
