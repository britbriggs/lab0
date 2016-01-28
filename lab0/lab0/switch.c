

#include <xc.h>
#include "switch.h"

#define Input 1
#define Released 0

void initSwitch1(){
    
    
    TRISDbits.TRISD6=Input;
 //   PORTDbits.RD6=Released;
    
    IFS1bits.CNDIF=0;
    CNPUDbits.CNPUD6=1;
    CNCONDbits.ON=1;        // Turn on Change Notifications
    CNENDbits.CNIED6=1;     //Enables CN for RD6
    
        
    
}
