/**************   ECE2049 LAB 3   ******************/
/**************  BY JEFFREY HUANG ******************/
/************** AND MICHAEL MCCUE ******************/
/***************************************************/

#include <msp430.h>

#include "peripherals.h"

void main(void){
    WDTCTL = WDTPW | WDTHOLD;
    initLeds();

    configDisplay();
    configKeypad();


}
