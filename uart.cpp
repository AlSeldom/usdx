/*
 * Example: USART_AVR
 * Target: ATmega32/ATmega32A
 * Frequency: 16 MHz Fuse: LFUSE=0xFF HFUSE=0x99
 * NOTE: Make sure to burn right fuse bits after loading USART_AVR.hex file to MCU. 
 * Remember Tx of FT232RL Adapter is connected to RXD and Rx connected to TXD of ATmega32A. 
 * https://binaryupdates.com/usart-in-avr-atmega32a-microcontroller/
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char String[]="Wel-Come to BINARYUPDATES.COM !!! \n\r\n";    

int main(void){
  USART_init();                     // Call the USART initialization code
  
  while(1){                     // Infinite loop
    USART_putstring(String); // Pass the string to the USART_putstring function and sends it over the serial
    _delay_ms(1000);         // Delay for 5 seconds so it will re-send the string every 5 seconds
  }
  
  return 0;
}

/* Initialize USART */
void USART_init(void){
  UBRRH = (uint8_t)(BAUD_PRESCALLER>>8);
  UBRRL = (uint8_t)(BAUD_PRESCALLER);
  UCSRB = (1<<RXEN)|(1<<TXEN);
  UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
}

/* Function to receive byte/char */
unsigned char USART_receive(void){
  while(!(UCSRA & (1<<RXC)));
  return UDR;
}

/* Function to send byte/char */
void USART_send( unsigned char data){
  while(!(UCSRA & (1<<UDRE)));
  UDR = data;
}

/* Send string */
void USART_putstring(char* StringPtr){
  while(*StringPtr != 0x00){
    USART_send(*StringPtr);
  StringPtr++;}
  
}
