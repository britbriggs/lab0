/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>


#define preScalar256 3

#define Enable 1
#define defaultPriority 7
#define Down 0

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    TMR1=0;
    T1CONbits.TCKPS=preScalar256;
    PR1=39061;
    T1CONbits.ON=1;

    
    IFS0bits.T1IF=Down;
    IEC0bits.T1IE=Enable;
    IPC1bits.T1IP=defaultPriority;
    
    
}