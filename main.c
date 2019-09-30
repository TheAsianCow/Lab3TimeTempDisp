/**************   ECE2049 LAB 3   ******************/
/**************  BY JEFFREY HUANG ******************/
/************** AND MICHAEL MCCUE ******************/
/***************************************************/

#include <msp430.h>
#include <math.h>
#include "peripherals.h"

#define CLK_SPEED 32768
#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)

void displayTime(long unsigned int inTime);
void displayTmpTime(unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec);
unsigned int getDayFromMonth(unsigned int month);
void displayTemp(float inAvgTempC);
void initADC(void);
__interrupt void Timer_A2_ISR(void);
__interrupt void ADC12_ISR(void);
void averageTemp(void);
void startTimerA2(void);
void stopTimerA2(void);

unsigned int leapYear = 0;//implementation of determining if leapYear is needed
/* mode = 0: display mode
 * mode = 1: editing month
 * mode = 2: editing day
 * mode = 3: editing hour
 * mode = 4: editing min
 * mode = 5: editing sec
 */
unsigned int mode;
unsigned long int pos, timerCount;
float avgTemp, tempStore[30];
//important to use a copy of the timer count cuz if the variable is modified directly then the time wouldn't be accurate anymore
void displayTime(long unsigned int inTime){
    unsigned char date[7];
    date[3] = ' ';
    date[6] = '\0';
    unsigned char time[9];
    time[2] = ':';
    time[5] = ':';
    time[8] = '\0';

    long unsigned int day  =  inTime/86400;
    long unsigned int hour = (inTime-day*86400)/3600;
    long unsigned int min  = (inTime-day*86400-hour*3600)/60;
    long unsigned int sec  =  inTime%60;
    day+=1;
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
    Graphics_flushBuffer(&g_sContext);
}

void displayTmpTime(unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec){
    unsigned char date[7];
        date[3] = ' ';
        date[6] = '\0';
        unsigned char time[9];
        time[2] = ':';
        time[5] = ':';
        time[8] = '\0';

        if(month==0){
            date[0] = 'J';
            date[1] = 'A';
            date[2] = 'N';
        }else if(month==1){
            date[0] = 'F';
            date[1] = 'E';
            date[2] = 'B';
        }else if(month==2){
            date[0] = 'M';
            date[1] = 'A';
            date[2] = 'R';
        }else if(month==3){
            date[0] = 'A';
            date[1] = 'P';
            date[2] = 'R';
        }else if(month==4){
            date[0] = 'M';
            date[1] = 'A';
            date[2] = 'Y';
        }else if(month==5){
            date[0] = 'J';
            date[1] = 'U';
            date[2] = 'N';
        }else if(month==6){
            date[0] = 'J';
            date[1] = 'U';
            date[2] = 'L';
        }else if(month==7){
            date[0] = 'A';
            date[1] = 'U';
            date[2] = 'G';
        }else if(month==8){
            date[0] = 'S';
            date[1] = 'E';
            date[2] = 'P';
        }else if(month==9){
            date[0] = 'O';
            date[1] = 'C';
            date[2] = 'T';
        }else if(month==10){
            date[0] = 'N';
            date[1] = 'O';
            date[2] = 'V';
        }else if(month==11||month==12){
            date[0] = 'D';
            date[1] = 'E';
            date[2] = 'C';
        }
        day++;
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
        Graphics_flushBuffer(&g_sContext);
}

unsigned int getDayFromMonth(unsigned int month){
    if(month==0)return 0;
    if(month==1)return 31;
    if(month==2)return 59+leapYear;
    if(month==3)return 90+leapYear;
    if(month==4)return 120+leapYear;
    if(month==5)return 151+leapYear;
    if(month==6)return 181+leapYear;
    if(month==7)return 212+leapYear;
    if(month==8)return 243+leapYear;
    if(month==9)return 273+leapYear;
    if(month==10)return 304+leapYear;
    if(month==11)return 334+leapYear;
//    if(month==11)return 365+leapYear;
    return 0;
}

void displayTemp(float inAvgTempC){
    unsigned char c[8];
    unsigned char f[8];
    c[3] = '.';
    c[5] = ' ';
    c[6] = 'C';
    c[7] = '\0';
    f[3] = '.';
    f[5] = ' ';
    f[6] = 'F';
    f[7] = '\0';
    float inAvgTempF = inAvgTempC*9.0/5.0+32.0;

    inAvgTempC*=10;
    inAvgTempF*=10;

    c[4] = (char)inAvgTempC%10+0x30;
    inAvgTempC/=10;
    c[2] = (char)inAvgTempC%10+0x30;
    inAvgTempC/=10;
    c[1] = (char)inAvgTempC%10+0x30;
    inAvgTempC/=10;
    c[0] = (char)inAvgTempC%10+0x30;
    inAvgTempC/=10;

    f[4] = (char)inAvgTempF%10+0x30;
    inAvgTempF/=10;
    f[2] = (char)inAvgTempF%10+0x30;
    inAvgTempF/=10;
    f[1] = (char)inAvgTempF%10+0x30;
    inAvgTempF/=10;
    f[0] = (char)inAvgTempF%10+0x30;
    inAvgTempF/=10;

    Graphics_drawStringCentered(&g_sContext, c, AUTO_STRING_LENGTH, 48, 30, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, f, AUTO_STRING_LENGTH, 48, 40, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

// Intitializes adc
// sets adc ref volt to read temp to nearest hundred
void initADC(void) {
    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0 = ADC12SHT0_9|ADC12REFON|ADC12ON|ADC12MSC;
    ADC12CTL1 = ADC12SHP|ADC12CONSEQ_1;
    ADC12MCTL0 = ADC12SREF_1|ADC12INCH_0;
    ADC12MCTL1 = ADC12SREF_1|ADC12INCH_10|ADC12EOS;
    ADC12IE = BIT1;

    P6SEL |= BIT0;
    P6DIR |= BIT0;
    __delay_cycles(100);
    ADC12CTL0 |= ADC12ENC;
}

void averageTemp(void) {
    if(timerCount < 30 && timerCount>0){
        avgTemp = tempStore[timerCount-1];
    }else{
        float added = 0;
        int i;
        for (i = 0; i < 30; i++) added += tempStore[i];
        avgTemp = added / 30;
    }
}

// initiates timer for one second
void startTimerA2(void) {
    TA2CTL  = (TASSEL__ACLK|ID__1|MC__UP);
    TA2CCR0  = CLK_SPEED-1; // Sets the timer for one second.
    TA2CCTL0 = CCIE; // IE
}

void stopTimerA2(void){
    TA2CTL = MC_0;
    TA2CCTL0 = ~CCIE;
}
// Timer Interrupt Function
#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void) {
    timerCount++;
    averageTemp();
    displayTime(timerCount);
    displayTemp(avgTemp);
    if(timerCount>=31535999)timerCount=0;
}

//ADC12 Interrupt Function
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void){
    volatile float degC_per_bit, tempC;
    volatile unsigned int bits30, bits85;

    bits30 = CALADC12_15V_30C;
    bits85 = CALADC12_15V_85C;
    degC_per_bit = ((float)(85.0 - 30.0))/((float)(bits85-bits30));

    pos = ADC12MEM0 & 0x0FFF;
    unsigned int in_temp = ADC12MEM1 & 0x0FFF;
    tempC = (float)((long)in_temp - CALADC12_15V_30C)*degC_per_bit+30.0;
    tempStore[timerCount%30] = tempC;
}

void main(void){
    WDTCTL = WDTPW | WDTHOLD;
    REFCTL0 &= ~REFMSTR;
    _BIS_SR(GIE);
    initLeds();
    startTimerA2();
    initADC();

    configDisplay();
    configBtn();
    configKeypad();

    timerCount = 0;
    avgTemp = 0;
    mode = 0;
    unsigned char currBtn;
    unsigned long int tmpMonth=0, tmpDay=0, tmpHour=0, tmpMin=0,tmpSec=0, currPos;
//    unsigned char num[] = {'0','\0'};

    for(;;){
        ADC12CTL0 |= ADC12SC;
        currBtn = getBtn();
        currPos = pos;
//        num[0] = pos*10/0x0FFF+48;
//        Graphics_drawStringCentered(&g_sContext,num, AUTO_STRING_LENGTH, 48,48,OPAQUE_TEXT);
//        Graphics_flushBuffer(&g_sContext);
        if(currBtn == 'r' && mode){
            mode = 0;
            timerCount = getDayFromMonth(tmpMonth)*86400+tmpDay*86400+tmpHour*3600+tmpMin*60+tmpSec;
            tmpMonth = 0;
            tmpDay = 0;
            tmpHour = 0;
            tmpMin = 0;
            tmpSec = 0;
            setLeds(0);
            startTimerA2();
        }
        if(currBtn == 'l'){
            if(mode==0){
                stopTimerA2();
                setLeds(BIT3);
            }
            mode++;
            if(mode>5)mode=1;
        }
        switch(mode){
        case 1:
            tmpMonth = pos*11/4095;
            displayTmpTime(tmpMonth, tmpDay, tmpHour, tmpMin, tmpSec);
            break;
        case 2:
            if(tmpMonth==0||tmpMonth==2||tmpMonth==4||tmpMonth==6||tmpMonth==7||tmpMonth==9||tmpMonth==11||tmpMonth==12)tmpDay = pos*30/4095;
            else if(tmpMonth==1) tmpDay = pos*27/4095;
            else tmpDay=pos*29/4095;
            displayTmpTime(tmpMonth, tmpDay, tmpHour, tmpMin, tmpSec);
            break;
        case 3:
            tmpHour = pos*23/4095;
            displayTmpTime(tmpMonth, tmpDay, tmpHour, tmpMin, tmpSec);
            break;
        case 4:
            tmpMin = pos*59/4095;
            displayTmpTime(tmpMonth, tmpDay, tmpHour, tmpMin, tmpSec);
            break;
        case 5:
            tmpSec = pos*59/4095;
            displayTmpTime(tmpMonth, tmpDay, tmpHour, tmpMin, tmpSec);
            break;
        }
    }
}
