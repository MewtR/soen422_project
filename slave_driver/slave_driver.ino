#include <avr/io.h>
#include <util/delay.h>
  
int main(void)
{
    //Setup outputs
    DDRD = (1 << PD5) | (1 << PD6);                             //D5 D6
    DDRB = (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4);   //D9 D10 D11 D12

     // configure Fast PWM
    TCCR0A = (1 << WGM00) | (1 << WGM01);
    // configure non-inverted PWM mode
    TCCR0A |= (1 << COM0A1) | (0 << COM0A0) | (1 << COM0B1) | (0 << COM0B0);    
    // configure timer and prescaler (no prescaler)
    TCCR0B = (1 << CS00);
    OCR0A = 255;
    OCR0B = 255;
    
    while(1)
    {
      // clockwise rotation      
      PORTB = (0 << PB4) | (1 << PB3) | (0 << PB2) | (1 << PB1);
    
      _delay_ms(500);
    
      // counter-clockwise rotation
      PORTB = (1 << PB4) | (0 << PB3) | (1 << PB2) | (0 << PB1);
    
      _delay_ms(500);
    }
}
