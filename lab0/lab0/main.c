/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

#define Enable 1
#define flagDown 0
#define defaultPriority 7

#define ON 1
#define OFF 0

//TODO: Define states of the state machine
typedef enum stateTypeEnum{ red, redInt, yellow, yellowInt, green, greenInt
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int state = 1;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initSwitch1();
    
    
    state = red;
    
    while(1){
        
        //TODO: Implement a state machine to create the desired functionality
       switch (state){
       
        case red:
            LATDbits.LATD0=ON;
            LATDbits.LATD1=OFF;
            LATDbits.LATD2=OFF;
            
            break;
        
        case yellow:
            LATDbits.LATD0=OFF;
            LATDbits.LATD1=ON;
            LATDbits.LATD2=OFF;
            break;
            
        case green:
            LATDbits.LATD0=OFF;
            LATDbits.LATD1=OFF;
            LATDbits.LATD2=ON;
         break;
    } 
        
        
    }
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
void __ISR (_TIMER_1_VECTOR, IPL7SRS) _T1Interupt() {
        
    IFS0bits.T1IF=flagDown;
    
    switch(state){
        case redInt:
            state=yellow;
            break;
            
        case yellowInt:
            state=green;
            break;
            
        case greenInt:
            state=red;
            break;
        
        default:
            state = red;
            break;
    }
}

    
 void __ISR(_CHANGE_NOTICE_VECTOR,IPL7SRS) _CNINterrupt(){
    // initTimer1();
     IFS1bits.CNDIF=0;
     
         switch(state){
             case red:
                 state=yellow;
                 break;
             case yellow:
                 state=green;
                 break;
             case green:
                 state=red;
                 break;
         }
 
}

