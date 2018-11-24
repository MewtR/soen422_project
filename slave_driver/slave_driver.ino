#include <avr/io.h>
#include <util/delay.h>

void init_motors(void);
void init_sensor(void);

int main(void)
{
    init_motors();
    //init_sensor();
    
    while(1)
    {
      test_motors();
      //test_sensor();
    }
}

void init_motors(void)
{
    //Setup outputs
    DDRD = (1 << PD5) | (1 << PD6);                             //D5 D6
    DDRC = (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);   //A2 A3 A4 A5
    // configure non-inverted fast PWM
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1) | (1 << COM0A1);
    // configure timer and prescaler (no prescaler)
    TCCR0B = (1 << CS00);
    
    OCR0A = 255;
    OCR0B = 255;
}

void init_sensor(void)
{
  // configure A0 as input
  DDRC = (0 << PC0);
  
  // configure prescaler (/2)
  ADCSRA = (1 << ADPS2);// | (0 << ADPS1) | (0 << ADPS0);
  // enable ADC
  ADCSRA |= (1 << ADEN);

  // use AVcc as the voltage reference w/ external capacitor on AREF pin
  ADMUX |= (1 << REFS0);
}

//test code; rename and create signature
void test_motors(void)
{
      //TODO: going from forwards to backwards very iffy. Try braking with PWM first?
  
      // forwards 
      PORTC = (0 << PC5) | (1 << PC4) | (1 << PC3) | (0 << PC2);
      _delay_ms(2000);
    
      // backwards
      PORTC = (1 << PC5) | (0 << PC4) | (0 << PC3) | (1 << PC2);
      _delay_ms(2000);
}


//test code; rename and create signature
void test_sensor(void)
{

}
