#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define BAUDRATE 9600
#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2
#define PARITY NOPARITY

int main()
{
  char charToPrint;
  int ticksPerSec = alt_timestamp_freq(); //clk frequency
  const int ticksPerBit = ticksPerSec/BAUDRATE;
  const int halfTicksPerBit = ticksPerBit/2;
  int ticks2Wait; //used to avoid resetting timer after each bit
  int t1, t2, nticks, val;
  while(1){
	  do {
		 val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
		 val &= 0x01; // mask not meaningful bits
	  } while(val);
	  alt_timestamp_start(); // start the timer
	  t1 = alt_timestamp();
	  charToPrint = 0;
	  ticks2Wait = halfTicksPerBit;
	  do {
		  t2 = alt_timestamp();
		  nticks = t2 - t1;
	  } while (nticks < ticks2Wait);
	  val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
	  ticks2Wait += ticksPerBit;
	  if (!val){ //check if START BIT is effectively low (no glitch)
		  for (int i=0; i<NBIT; ++i){
			  do {
				  t2 = alt_timestamp();
				  nticks = t2 - t1;
			  } while(nticks < ticks2Wait);
			  val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
			  val &= 0x01;
			  charToPrint |= val << i;
			  ticks2Wait += ticksPerBit;
		  }
		  do {
			  t2 = alt_timestamp();
		  	  nticks = t2 - t1;
		  } while(nticks < ticks2Wait);
		  val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
		  if(val) //sample the STOP bit
			  printf("%c", charToPrint);
	  }
  }
  return 0;
}
