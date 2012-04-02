
// Just tested something with this

#include <stdio.h>
#include "pressure.c"

void main() {

  float test = getPressureIn();

  printf("Pressure is %.2f\n", test);

  float test2 = getPressureOut();

  printf("Pressure is %.2f\n", test2);

}
