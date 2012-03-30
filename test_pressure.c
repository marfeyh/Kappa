#include <stdio.h>
#include "pressure.c"

void main() {

  float test = getPressureIn();

  printf("Pressure is %.2f\n", test);

}
