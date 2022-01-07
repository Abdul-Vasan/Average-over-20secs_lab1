#include <LPC23xx.H>                    /* LPC23xx definitions                */
#include "LCD.h"
#include <stdio.h>
#define VREF 3.3
unsigned int i = 1;
float j=1.0;
double val = 0;
double voltage;
double convertedData;
unsigned char red[10] = "Reading...";
unsigned char red2[7] = "Reading";
unsigned char mcount[5];
char ans[7];
/* Timer0 IRQ: Executed periodically                                          */
__irq void T0_IRQHandler (void) {
	
		/* ADC */
	PCONP = PCONP|0x3000;
	PINSEL1       = (PINSEL1 & 0xFFFF3FFF)|0x4000;  // Select P0.23 as AD0 (Alt Func 1)
	 
	AD0INTEN      = 0x1;         //Using Channel 0 for Interrupt

	AD0CR         = 0x01200301; 
			set_cursor (0, 0);
	    lcd_print(red2);
	if(i<60){
	  	while(!(AD0STAT & 0x00000001));
			 convertedData =(AD0DR0 & 0xFFFF)>>6;  
			 voltage=(VREF/1023)*convertedData;
		  val = val+voltage;
			i++;
	}
	
	
	
	
	
	if (i==60) {
		val = val/60;
		sprintf(mcount,"%.0f",j);
	 set_cursor(8,0);
		lcd_print(mcount);
		set_cursor(0,1);
		sprintf(ans,"%.3f",val);
		lcd_print(ans);
		i = 0;
		val = 0;
	if(j<20.0) 
 j = j+1; 
		else if(j==20.0) 
 j=1.0; 
		}
	
	T0IR        = 1;                      /* Clear interrupt flag               */
  VICVectAddr = 0;                      /* Acknowledge Interrupt              */
}