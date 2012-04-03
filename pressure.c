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


/* Conversion functions. Written by:
	Yuwei Chen  */

float conversion_ktp(void){
    return getPressure()*0.145;
    }
float conversion_ktb(void){
    return getPressure()*0.0102;
    }
float conversion_ptk(float psi){
    return psi*6.895;
    }
float conversion_ptb(float psi){
    return psi*0.06895;
    }
float conversion_btk(float bar){
    return bar*101.3;
    }
float conversion_btp(float bar){
    return bar*14.503;
    }
