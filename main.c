 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

int main(void)
{
    SYSTEM_Initialize();
    
    NCO1CONbits.EN = 0;  //disable NCO module
        
    NCO1INCU = 0x00;
    NCO1INCH = 0x00;
    NCO1INCL = 0x01;     //set increment to 0x000001, or 1
    
    while(1)
    {
        //wait initialize
        NCO1ACCL = 0x00; 
        NCO1ACCH = 0x00; 
        NCO1ACCU = 0x00;  //clear accumulator

        NCO1CONbits.EN = 1; //enable NCO module
        PIR2bits.CLC2IF = 0; //clear CLC2IF interrupt flag
        
        //wait for pulse
        while(!PIR2bits.CLC2IF); //wait until interrupt flag is set
            //save accumulator value
            int8_t result2 = NCO1ACCU; 
            int8_t result1 = NCO1ACCH;
            int8_t result0 = NCO1ACCL;

            //process accumulator values to make a 20-bit value
            int24_t measurement = ((int24_t)result2 << 16); 
            measurement = measurement + ((int16_t)result1 << 8);
            measurement = measurement + result0;

        NCO1CONbits.EN = 0; //disable NCO module
    }    
}