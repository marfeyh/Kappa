/*
  Group: Kappa
  Authors: Rob Bruinsma, Anna Orazova
  Usage:
  Gets pressure info from pressure sensor, convert it to kPa.
 */

float getPressureIn() { // For the sensor in the skirt

  float pr_kPa; // Pressure in kPa inside of the skirt
  pr_kPa = ((float) analogRead(A0)/1023+0.04)/0.004; // Takes output of analog port 0 and converts it into kPa

  return pr_kPa;
}

float getPressureOut() { // For the sensor on the outside

float pr_kPa2; // Pressure in kPa on the outside of the hovercraft
  pr_kPa2 = ((float) analogRead(A1)/1023+0.04)/0.004; // Takes output of analog port 1 and converts it into kPa

  return pr_kPa2;
}
