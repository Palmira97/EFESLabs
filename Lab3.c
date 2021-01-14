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
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_pio_regs.h"
#define RXDATA_OFFSET 0
#define TXDATA_OFFSET 1
#define STATUS_OFFSET 2
#define CONTROL_OFFSET 3
#define DIVISOR_OFFSET 4

#define PROJECT4

#ifdef PROJECT1
int main()
{
  int *base = UART_0_BASE;
  int RXDATA, TXDATA, STATUS, CONTROL, DIVISOR;
  RXDATA = *(base + RXDATA_OFFSET);
  TXDATA = *(base + TXDATA_OFFSET);
  STATUS = *(base + STATUS_OFFSET);
  CONTROL = *(base + CONTROL_OFFSET);
  DIVISOR = *(base + DIVISOR_OFFSET);
  //RXDATA = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
  //TXDATA = IORD_ALTERA_AVALON_UART_TXDATA(UART_0_BASE);
  //STATUS = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
  //CONTROL = IORD_ALTERA_AVALON_UART_CONTROL(UART_0_BASE);
  //DIVISOR = IORD_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE);
  printf("Rxdata = %X\n", RXDATA);
  printf("Txdata = %X\n", TXDATA);
  printf("Status = %X\n", STATUS);
  printf("Control = %X\n", CONTROL);
  printf("Divisor = %X\n", DIVISOR);
  return 0;
}
#endif

#ifdef PROJECT2
int main(){
	int *base = UART_0_BASE;
	int new_divisor = 50000000/2400 - 1;
	int read_divisor;
	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor);
	*(base + DIVISOR_OFFSET) = new_divisor;
	//read_divisor = IORD_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE);
	read_divisor = *(base + DIVISOR_OFFSET);
	printf("Divisor after writing = %d\n", read_divisor);
	printf("Expected divisor = %d\n", new_divisor);
	return 0;
}
#endif

#ifdef PROJECT31
int main(){
	int *base = UART_0_BASE;
	int old_status, new_status;
	int new_divisor = 50000000/2400 - 1;
	*(base + DIVISOR_OFFSET) = new_divisor;
	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor);
	old_status = *(base + STATUS_OFFSET);
	//old_status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
	printf("Status Reg before reading: 0x%X\n", old_status);  //Status Reg = 0x60
	//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'A');
	*(base + TXDATA_OFFSET) = 'A';
	//new_status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
	new_status = *(base + STATUS_OFFSET);
	printf("Status Reg after reading: 0x%X", new_status); //Status Reg = 0x40
	return 0;
}
#endif

#ifdef PROJECT32
int main(){
	int *base = UART_0_BASE;
	int old_status, new_status;
	int new_divisor = 50000000/2400 - 1;

	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor);
	*(base + DIVISOR_OFFSET) = new_divisor;
	//old_status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
	old_status = *(base + STATUS_OFFSET);
	printf("Status Reg before reading: 0x%X\n", old_status); //Status Reg = 0x60
	//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'A');
	*(base + TXDATA_OFFSET) = 'A';
	//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'B');
	*(base + TXDATA_OFFSET) = 'B';
	//new_status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE); //Status Reg = 0x0
	new_status = *(base + STATUS_OFFSET);
	printf("Status Reg after reading: 0x%X\n", new_status);
	return 0;
}
#endif

#ifdef PROJECT33
int main(){
	int *base = UART_0_BASE;
	int old_status, new_status;
	int new_divisor = 50000000/2400 - 1;
	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor);
	*(base + DIVISOR_OFFSET) = new_divisor;
	//old_status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
	old_status = *(base + STATUS_OFFSET);
	printf("Status Reg before reading: 0x%x\n", old_status); //Status Reg = 0x60
	//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'A');
	*(base + TXDATA_OFFSET) = 'A';
	//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'B');
	*(base + TXDATA_OFFSET) = 'B';
	//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, 'A');
	*(base + TXDATA_OFFSET) = 'C';
	//new_status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE); //Status Reg = 0x0
	new_status = *(base + STATUS_OFFSET);
	printf("Status Reg after reading: 0x%x", new_status);
	return 0;
}
#endif

#ifdef PROJECT4
int main(){
	int *base = UART_0_BASE;
	char char_to_print, *string = "My name is Leonardo\r\n";
	int status_content, status_before, status_after;
	int new_divisor = 50000000/2400 - 1;
	//status_content = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE); //manual clearing of the status reg
	status_content = *(base + STATUS_OFFSET);
	//IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, status_content & 0x11F);
	*(base + STATUS_OFFSET) = status_content & 0x11F;
	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor); //set the divisor for the baud rate
	*(base + DIVISOR_OFFSET) = new_divisor;
	//IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, 0);
	*(base + CONTROL_OFFSET) = 0;
	for(int i=0; i<strlen(string); i++){
		do {
			//status_content = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
			status_content = *(base + STATUS_OFFSET);
			status_content &= 0x0040; 										//mask the RRDY bit
		} while(status_content == 0);
		//IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, string[i]);
		*(base + TXDATA_OFFSET) = string[i];
	}

}
#endif

#ifdef PROJECT51
int main(){
	int *base = UART_0_BASE;
	int status_content, status_before, status_after;
	int new_divisor = 50000000/2400 - 1;
	char char_to_print;
	//status_content = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE); //manual clearing of the status reg
	//status_content = *(base + STATUS_OFFSET);
	//IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, status_content & 0x11F);
	//*(base + STATUS_OFFSET) = status_content & 0x11F;
	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor);
	*(base + DIVISOR_OFFSET) = new_divisor;
	//IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, 0);
	*(base + CONTROL_OFFSET) = 0;
	while(1){
		//status_content = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
		status_content = *(base + STATUS_OFFSET);
		status_content &= 0x0080; 										//mask the RRDY bit
		if(status_content > 0) {  //RRDY = 1
			//status_before = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
			status_before = *(base + STATUS_OFFSET);
			printf("Status Reg before reading: 0x%X\n", status_before); //Status Reg=0x16C without previous clearing, 0xE0 with clearing
			//char_to_print = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
			char_to_print = *(base + RXDATA_OFFSET);
			printf("Found char = %c\n", (char) char_to_print);
			//status_after = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
			status_after = *(base + STATUS_OFFSET);
			printf("Status Reg before reading: 0x%X\n", status_after); //Status Reg=0x1EC without previous clearing, 0x60 with clearing
		}
	}
}
#endif

#ifdef PROJECT52
int main(){
	int *base = UART_0_BASE;
	int status_content, status_before, status_after;
	int new_divisor = 50000000/2400 - 1;
	char char_to_print;
	//status_content = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE); //manual clearing of the status reg
	//status_content = *(base + STATUS_OFFSET);
	//IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, status_content & 0x11F);
	//*(base + STATUS_OFFSET) = status_content & 0x11F;
	//IOWR_ALTERA_AVALON_UART_DIVISOR(UART_0_BASE, new_divisor);
	*(base + DIVISOR_OFFSET) = new_divisor;
	//IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, 0);
	*(base + CONTROL_OFFSET) = 0;
	while(1){
		//status_before = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
		status_before = *(base + STATUS_OFFSET);
		printf("Status Reg before reading: 0x%X\n", status_before); //if we write more than 1 char at a time: status reg=0x168
		//char_to_print = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		char_to_print = *(base + RXDATA_OFFSET);
		printf("Found char = %c\n", (char) char_to_print);
		//status_after = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
		status_after = *(base + STATUS_OFFSET);
		printf("Status Reg before reading: 0x%X\n", status_after); //if we write more than 1 char at a time: status reg=0x168
		*(base + STATUS_OFFSET) = 0; //clearing status register
		//usleep(1000000);
	}
}
#endif
