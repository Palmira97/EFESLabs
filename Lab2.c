/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define BAUDRATE 300
#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2
#define PARITY NOPARITY

/* TODO provare a far partire il timer solo una volta e contare il numero di ticks a partire da tale istante
 * */
int main()
{
  char charToPrint = 0;
  int ticksPerSec = alt_timestamp_freq();
  const int ticksPerBit = ticksPerSec/BAUDRATE;
  const int halfBitTime = ticksPerBit/2;
  int ticks2Wait = halfBitTime; //used for fast check computation
  int t1, t2, nticks, val;
  while(1){
	  do {
		 val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
	  } while(val);
	  //alt_timestamp_start();
/* 	  t1 = alt_timestamp();
	  do {
		  t2 = alt_timestamp();
  		  nticks = t2 - t1;
	  } while(nticks < halfBitTime); */
	  // while(alt_timestamp() < halfBitTime){};
	  alt_timestamp_start();
	  t1 = alt_timestamp();
	  do {
		  t2 = alt_timestamp();
		  nticks = t2 - t1;
	  } while (nticks < ticks2Wait);
	  val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
	  ticks2Wait += ticksPerBit;
	  if (!val){ //check if START BIT is effectively low
		  for (int i=0; i<NBIT; ++i){
			  //alt_timestamp_start();
			  /* t1 = alt_timestamp();
			  do {
				  t2 = alt_timestamp();
			  	  nticks = t2 - t1;
			   } while(nticks < ticksPerBit); */
			  do {
				  t2 = alt_timestamp();
				  nticks = t2 - t1;
			  } while(nticks < ticks2Wait);
			  // while(alt_timestamp() < ticksPerBit){};
			  val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
			  val &= 0x01;
			  charToPrint |= val << i;
			  ticks2Wait += ticksPerBit;
		  }
		  //alt_timestamp_start();
		  /* t1 = alt_timestamp();
		  do {
			  t2 = alt_timestamp();
		  	  nticks = t2 - t1;
		  } while(nticks < ticksPerBit); */
		  do {
			  t2 = alt_timestamp();
		  	  nticks = t2 - t1;
		  } while(nticks < ticks2Wait);
		  val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
		  if(val) //sample the STOP bit
			  printf("%c", charToPrint);
		  charToPrint = 0;
	  }
  }
  return 0;
}
