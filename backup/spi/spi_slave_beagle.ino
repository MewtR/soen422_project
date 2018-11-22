#define F_CPU 16000000
#define BAUD 9600
#define MYUBBR F_CPU/16/BAUD-1
#include <util/setbaud.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//Use USART for communication between laptop and master
void USART_init(unsigned int ubrr){
UBRR0H = (unsigned char)(ubrr >> 8); // Shift needed to clear out first 8 bits
UBRR0L = (unsigned char) (ubrr);
UCSR0B = ((1 << RXEN0) | (1 << TXEN0)); // Enable receiver and transmitter
UCSR0C = ((1 << USBS0) | (3 << UCSZ00)); // Set frame to 8 bits of data, two stop bits
}
unsigned char USART_receive(void){
while ( !(UCSR0A & (1<<RXC0)) ) ;
return UDR0;
}
void USART_transmit(char data){
while( !(UCSR0A & ( 1 << UDRE0)) );
UDR0 = data;
}

void spi_slave_enable(void){

DDRB &= ~(( 1 << 2 )|( 1 << 3 )|( 1 << 5 )); // SCK, MOSI and SS as inputs
DDRB |= (1 << 4); // Set MISO as output. MOSI, SCK and SS are set to inputs (default)
SPCR &= ~(1 << MSTR); // Set as slave
SPCR |= (1 << SPE); // Set device as SPI slave by just enabling SPI.
SPCR |= ( 1 << SPR0 )|( 1 << SPR1 ); // divide clock by 128
}

uint8_t spi_transceiver (uint8_t spi_data)
{
SPDR = spi_data; // Load byte to be shifted out
while (! (SPSR & (1 << SPIF))); // Wait until interrupt flag is asserted. IF is asserted when transmission is complete
return (SPDR);
}

int main(void){

spi_slave_enable();
USART_init(MYUBBR);
DDRB |= (1 << PB0); //Output pin used to turn on LED

    while(1){

    spi_transceiver(0x42);
    USART_transmit(SPDR); //Echo contents of SPDR
    PORTB ^= (1 << PB0);

    }
}
