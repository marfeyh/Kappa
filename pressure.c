/*
  Group: Kappa
  Authors: Rob Bruinsma, Anna Orazova
  Usage:
  Gets pressure info from pressure sensor, convert it to kPa.
 */

float getPressure() {

  float pr_kPa; // Pressure in kPa
  pr_kPa = ((float) analogRead(A0)/1023+0.04)/0.004; // Takes analog output and converts it into kPa
  return pr_kPa;

}
