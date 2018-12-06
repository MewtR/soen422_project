#include <avr/io.h>
#include <util/delay.h>

void init_motors(void);
void init_sensor(void);
void brake(void);
void drive_forwards(void);
void drive_left(void);
void drive_right(void);
void drive_backwards(void);

int main(void)
{
    //Serial.begin(9600);
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
    // Setup outputs
    // PWM pins D9 D10; D9 = left motors, D10 = right motors
    DDRB = (1 << PB1) | (1 << PB2);
    // GPIO pins; A2 A3 = left motors, A4 A5 = right motors
    DDRC = (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);

    // Phase correct PWM
    TCCR1A = (1 << WGM13) | (1 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1A0) | (1 << COM1B0);
    // No prescaler
    TCCR1B = (1 << CS00);

    OCR1A = 128;
    OCR1B = 128;
}

void init_sensor(void)
{
    // configure A0 as input
    DDRC = (0 << PC0);
    
    // configure prescaler (/2)
    ADCSRA = (1 << ADPS2);
    // enable ADC
    ADCSRA |= (1 << ADEN);
  
    // use AVcc as the voltage reference w/ external capacitor on AREF pin
    ADMUX |= (1 << REFS0);
}

//test code; rename and create signature
void test_motors(void)
{  
    drive_forwards();
    _delay_ms(5000);

    brake();
    _delay_ms(5000);

    drive_right();
    _delay_ms(5000);

    brake();
    _delay_ms(5000);
    
    drive_left();
    _delay_ms(5000);

    brake();
    _delay_ms(5000);

    drive_backwards();
    _delay_ms(5000);

    brake();
    _delay_ms(5000);
}


//test code; rename and create signature
void test_sensor(void)
{
    ADCSRA |= (1 << ADSC); //Start Conversion
    while (!(ADCSRA & (1 << ADIF))); //Wait for ADIF to go to 0, indicating conversion complete.
    ADCSRA |= (1 << ADIF);

    // clear ADIF manually
    ADCSRA |= (1 << ADIF);
    
    uint8_t value = ADC / 2;
    //Serial.println(value);
    _delay_ms(100);
}

void brake(void)
{
    PORTC = 0;
}

void drive_forwards(void)
{
    PORTC = (1 << PC4) | (1 << PC3);
}

void drive_left(void)
{
    PORTC = (1 << PC4); 
}

void drive_right(void)
{
    PORTC = (1 << PC3);
}

void drive_backwards(void)
{
    PORTC = (1 << PC5) | (1 << PC2);
}
