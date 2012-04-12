// Written by: Rob Bruinsma
// Used to test the pressure sensor code.
//Doesn't work without sensors or changing sensor input to test values.

#include <stdio.h>
#include "pressure.c"

void main() {

  int test = get_pressure();

  printf("Difference in pressure is %d\n", test);

}
