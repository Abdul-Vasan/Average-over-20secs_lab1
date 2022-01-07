#include <stdio.h>
#include <LPC23xx.H> 
#include "LCD.h"/* LPC23xx definitions                */


/* Import external IRQ handlers from IRQ.c file                               */
extern __irq void T0_IRQHandler  (void);


int main (void) {
  /* Enable and setup timer interrupt, start timer                            */
  T0MR0         = 999999;                      /* 0.5sec = 1x  10^6-1 at 2.0 MHz */
  T0MCR         = 3;                           /* Interrupt and Reset on MR0  */
	T0PR					= 11;													 /*Prescale 12 MHz to 2 MHZ*/
  T0TCR         = 1;                           /* Timer0 Enable               */
  VICVectAddr4  = (unsigned long)T0_IRQHandler;/* Set Interrupt Vector        */
  VICVectCntl4  = 15;                          /* use it for Timer0 Interrupt */
  VICIntEnable  = (1  << 4);                   /* Enable Timer0 Interrupt     */
	lcd_init();
	lcd_clear();
	while(1);
}
