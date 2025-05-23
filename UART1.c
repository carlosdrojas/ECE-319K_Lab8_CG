/* UART1.c
 * Your name
 * Date:
 * PA8 UART1 Tx to other microcontroller PA22 UART2 Rx
 */


#include <ti/devices/msp/msp.h>
#include "UART1.h"
#include "../inc/Clock.h"
#define PA8INDEX  18 // UART1_TX  SPI0_CS0  UART0_RTS TIMA0_C0  TIMA1_C0N


// power Domain PD0
// for 80MHz bus clock, UART clock is ULPCLK 40MHz
// initialize UART1 for 2000 baud rate
// blind, no synchronization on transmit
void UART1_Init(void){
    // do not reset or activate PortA, already done in LaunchPad_Init
    
     // write this
  UART1->GPRCM.RSTCTL = 0xB1000003;
  UART1->GPRCM.PWREN = 0x26000001;
  Clock_Delay(24); // time for uart to power 
  IOMUX->SECCFG.PINCM[PA8INDEX] = 0x00000082;
  UART1->CLKSEL = 0x08; // bus 
  UART1->CLKDIV = 0x00; // no 
  UART1->CTL0 &= ~0x01; // disable 
  UART1->CTL0 = 0x00020018;
  // assumes an 80 MHz bus 
  UART1->IBRD = 1249;// divider = 21+45/64 = 21.
  UART1->FBRD = 64; // baud = 2,500,000/21.703125 = 115,191
  UART1->LCRH = 0x00000030;
  UART1->CTL0 |= 0x01; // enable UART0
}


//------------UART1_OutChar------------
// Output 8-bit to serial port
// blind synchronization
// 10 bit frame, 2000 baud, 5ms per frame
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(char data){
// simply output data to transmitter without waiting or checking status
  UART1->TXDATA = data;
}
