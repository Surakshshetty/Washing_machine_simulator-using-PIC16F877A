/*
 * File:   digital_keypad.c
 * Author: Suraksh
 *
 * Created on 17 October, 2021, 5:59 AM
 */


#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES; //TRISB = TRISB | 0x3F
    
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    static unsigned char pre_key;
    static unsigned char longpress;
    
    if (mode == LEVEL_DETECTION)
    {
        return KEYPAD_PORT & INPUT_LINES; //PORTB & 0x3F
    }
    else
    {
        if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            longpress = 0;
            pre_key = KEYPAD_PORT & INPUT_LINES;  
           // return KEYPAD_PORT & INPUT_LINES;
        }
        else if (!once && (pre_key == (KEYPAD_PORT & INPUT_LINES)) && longpress < 50)
        {
           // once = 1;
            longpress++;
        }
        else if (longpress == 50)
        {
            longpress++;
            return 0x80 | pre_key;
        }
        else if((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED && !once)
        {
            once = 1;
            if(longpress < 50)
            {
                return pre_key; 
            }
        }
    }
    
    return ALL_RELEASED;
}