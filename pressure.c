/*
  Group: Kappa
  Authors: Rob Bruinsma, Anna Orazova
  Usage:
  Gets pressure info from pressure sensor, convert it to kPa.
 */

float getPressure() { // For the sensor in the skirt

  float pr_inside; // Pressure in kPa inside of the skirt
  pr_inside = ((float) analogRead(A0)/1023+0.04)/0.004; // Takes output of analog port 0 and converts it into kPa

  float pr_outside; // Pressure in kPa on the outside of the hovercraft
  pr_outside = ((float) analogRead(A1)/1023+0.04)/0.004; // Takes output of analog port 1 and converts it into kPa

  return pr_inside - pr_outside;
}
