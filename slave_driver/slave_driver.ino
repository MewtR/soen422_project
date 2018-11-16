#include <avr/io.h>
#include <util/delay.h>
  
int main(void)
{
    //Setup outputs
    DDRD = (1 << PD5) | (1 << PD6);                             //D5 D6
    DDRC = (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);   //A2 A3 A4 A5

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
      PORTC = (0 << PC5) | (1 << PC4) | (0 << PC3) | (1 << PC2);
    
      _delay_ms(500);
    
      // counter-clockwise rotation
      PORTC = (1 << PC5) | (0 << PC4) | (1 << PC3) | (0 << PC2);
    
      _delay_ms(500);
    }
}
