#include "pressure.h"

int main(void)
{

  init(); 

  return 0;
}

void setup() {
  Serial.begin(9600);

  
}

void loop() {
  float pressure;
  pressure = getPressure();
  Serial.println("%f \n",pressure);
}
