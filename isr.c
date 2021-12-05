/*
 * File:   isr.c
 * Author: Suraksh
 *
 * Created on 17 October, 2021, 6:32 AM
 */


#include <xc.h>
#include "main.h"
extern unsigned char sec, min;
void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR2IF == 1)
    {
        if (++count == 1250)
        {
            count = 0;
            if(sec > 0)
            {
                sec--;
            }
            else if(sec == 0 && min > 0)
            {
                min--;
                sec = 59;
        }
        }        
        TMR2IF = 0;
    }
}
