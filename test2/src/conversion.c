#include<stdio.h>
#include"pressure.h"
#include"conversion.h"

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




