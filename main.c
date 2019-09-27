/**************   ECE2049 LAB 3   ******************/
/**************  BY JEFFREY HUANG ******************/
/************** AND MICHAEL MCCUE ******************/
/***************************************************/

#include <msp430.h>

#include "peripherals.h"

#define CLK_SPEED 32768

void displayTime(long unsigned int inTime);
void displayTemp(float inAvgTempC);
void initADC(void);
int checkTemp(void);
void averageTemp(void);
void initTimer(void);

unsigned int leapYear = 0;//implementation of determining if leapYear is needed
unsigned int tempStore[30];
unsigned long int timerCount;
float avgTemp;
//important to use a copy of the timer count cuz if the variable is modified directly then the time wouldn't be accurate anymore
void displayTime(long unsigned int inTime){
    unsigned char date[6];
    date[3] = ' ';
    unsigned char time[8];
    time[2] = ':';
    time[5] = ':';

    unsigned int day  =  inTime/86400+1;
    unsigned int hour = (inTime-day*86400)/3600;
    unsigned int min  = (inTime-day*86400-hour*3600)/60;
    unsigned int sec  =  inTime%60;

    if(day<=31){
        date[0] = 'J';
        date[1] = 'A';
        date[2] = 'N';
    }else if(day>31&&day<=59+leapYear){
        date[0] = 'F';
        date[1] = 'E';
        date[2] = 'B';
        day-=31;
    }else if(day>59+leapYear&&day<=90+leapYear){
        date[0] = 'M';
        date[1] = 'A';
        date[2] = 'R';
        day-=59;
    }else if(day>90+leapYear&&day<=120+leapYear){
        date[0] = 'A';
        date[1] = 'P';
        date[2] = 'R';
        day-=90;
    }else if(day>120+leapYear&&day<=151+leapYear){
        date[0] = 'M';
        date[1] = 'A';
        date[2] = 'Y';
        day-=120;
    }else if(day>151+leapYear&&day<=181+leapYear){
        date[0] = 'J';
        date[1] = 'U';
        date[2] = 'N';
        day-=151;
    }else if(day>181+leapYear&&day<=212+leapYear){
        date[0] = 'J';
        date[1] = 'U';
        date[2] = 'L';
        day-=181;
    }else if(day>212+leapYear&&day<=243+leapYear){
        date[0] = 'A';
        date[1] = 'U';
        date[2] = 'G';
        day-=212;
    }else if(day>243+leapYear&&day<=273+leapYear){
        date[0] = 'S';
        date[1] = 'E';
        date[2] = 'P';
        day-=243;
    }else if(day>273+leapYear&&day<=304+leapYear){
        date[0] = 'O';
        date[1] = 'C';
        date[2] = 'T';
        day-=273;
    }else if(day>304+leapYear&&day<=334+leapYear){
        date[0] = 'N';
        date[1] = 'O';
        date[2] = 'V';
        day-=304;
    }else if(day>334+leapYear&&day<=365+leapYear){
        date[0] = 'D';
        date[1] = 'E';
        date[2] = 'C';
        day-=334;
    }
    date[5] = 0x30+day%10;
    day/=10;
    date[4] = 0x30+day%10;

    time[1] = 0x30+hour%10;
    hour/=10;
    time[0] = 0x30+hour%10;

    time[4] = 0x30+min%10;
    min/=10;
    time[3] = 0x30+min%10;

    time[7] = 0x30+sec%10;
    sec/=10;
    time[6] = 0x30+sec%10;

    Graphics_drawStringCentered(&g_sContext, date, AUTO_STRING_LENGTH, 48, 10, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, time, AUTO_STRING_LENGTH, 48, 20, OPAQUE_TEXT);
}

void displayTemp(float inAvgTempC){
    unsigned char c[7];
    unsigned char f[7];
    c[3] = '.';
    c[5] = ' ';
    c[6] = 'C';
    f[3] = '.';
    f[5] = ' ';
    f[6] = 'F';
    float inAvgTempF = inAvgTempC*9/5+32;

    inAvgTempC*=10;
    inAvgTempF*=10;

    c[4] = (char)inAvgTempC%10;
    inAvgTempC/=10;
    c[2] = (char)inAvgTempC%10;
    inAvgTempC/=10;
    c[1] = (char)inAvgTempC%10;
    inAvgTempC/=10;
    c[0] = (char)inAvgTempC%10;
    inAvgTempC/=10;

    f[4] = (char)inAvgTempF%10;
    inAvgTempF/=10;
    f[2] = (char)inAvgTempF%10;
    inAvgTempF/=10;
    f[1] = (char)inAvgTempF%10;
    inAvgTempF/=10;
    f[0] = (char)inAvgTempF%10;
    inAvgTempF/=10;

    Graphics_drawStringCentered(&g_sContext, c, AUTO_STRING_LENGTH, 48, 30, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, f, AUTO_STRING_LENGTH, 48, 40, OPAQUE_TEXT);
}

// Intitializes adc
// sets adc ref volt to read temp to nearest hundred
void initAdc(void) {
    REFCTLO &= ~REFMSTR;

    P6SEL &= BIT0; //
    P6DIR &= BIT0; //

    ADC12CTL0 = ADC12SHT0_0 | ADC12REFON | ADC12ON;
    ADC12CTL1 = ADC12SHP;

    ADCMCTL0 = ADC12SREF_1 + ADC12INCH_10; // temp sensor
    ADCMCTL1 = ADC12SREF_1 + ADC12INCH_0; // scroll wheel
}

// Check Temp
// Check Temp returns current temperature of the board
int checkTemp(void) {
    return 0;
}

void averageTemp(void) {
    int added = 0;
    int i;
    for (i = 0; i < 30; i++) {
        added += tempStore[i];
    }
    avgTemp = added / 30;
}

// scrollWheel
int scrollWheel(int items) {
    return 0; // returns a number based oon the position of the wheel and the number of items
}

// initiates timer for one second
void initTimer(void) {
    TA2CTL  = (TASSEL__ACLK|ID__1|MC__UP);
    TA2CCR0  = CLK_SPEED-1; // Sets the timer for one second.
    TA2CCTL0 = CCIE; // IE
}

// Interrupt Function
#pragma vector=TIMER2_A0_VECTOR
interrupt void Timer_A2 (void) {
    timerCount++;
    if(timerCount%2==0){
        displayTime(timerCount);
        displayTemp(avgTemp);
    }
}

void main(void){
    WDTCTL = WDTPW | WDTHOLD;
    _BIS_SR(GIE);
    initLeds();
    initTimer();

    configDisplay();
    configKeypad();

    timerCount = 0;
    avgTemp = 0;

    for(;;);
}
