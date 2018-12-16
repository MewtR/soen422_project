#define F_CPU 16000000
#define BAUD 9600
#define DRIVE 0x01
#define STOP 0xFF
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_motors(void);
void init_sensor(void);
void init_communication(void);
uint8_t get_sensor_val(void);
void brake(int ms);
void drive_forwards(int ms);
void drive_left(int ms);
void drive_right(int ms);
void drive_backwards(int ms);
void drive();

uint8_t mode = DRIVE;

int main(void)
{
uint8_t rec;
    Serial.begin(9600);
//    DDRD |= (1 << PD4);
//    DDRD |= (1 << PD7);
    init_motors();
    init_sensor();
//    PORTD |= (1 << PD4);
    init_communication();
    sei(); //Enable interrupts after communication with BBB established
//    PORTD |= (1 << PD7);
    Serial.println("In main");
    DDRD |= (1 << PD3);
    DDRD |= (1 << PD2);
    while(1)
    {
//        drive_forwards(5000);
//        brake(1000);
//        drive_left(3000);
//        brake(1000);
//        drive_backwards(5000);
//        brake(2000);
//      if (mode == DRIVE)
//      {
//        drive_forwards(0);
//        PORTD |= (1 << PD2);
//        }else{
//        cli();
//        PORTD &= ~(1 << PD2);
//        brake(1000);
//        sei();
//        }
            
      //ADCSRA |= (1<<ADSC);
      if (mode == DRIVE)
      {

        drive_forwards(0);
        PORTD |= (1 << PD2);
      }
      else // (mode == STOP)
      {
        cli(); //Disable interupts to not go into driving mode due to sensor reading
        PORTD &= ~(1 << PD2);
        while(1){
        brake(1000);
        rec = spi_transceiver('S');
        Serial.print("BBB ");
        Serial.println(SPDR);
            if (rec == 'G'){
                brake(1000);
                drive_backwards(2000);
                brake(1000);
                drive_left(3000);
                brake(500);
                sei(); //Enable interupts
                while(1){
                    rec = spi_transceiver('B');
                    if (rec == 'A'){
                        break;
                    }else{
                        continue;
                    }
                }
                break;
            }else{
              continue;
            }
        }
      // drive_backwards(3000);
      // drive_left(1000);
      //}else {
      //  brake(0);
      //}
      }
    }
}

void init_motors(void)
{
    // Setup outputs
    // PWM pins D9 D10; D9 = left motors, D10 = right motors
    DDRB = (1 << PB1) | (1 << PB2);
    DDRD = (1 << PD6) | (1 << PD5) | (1 << PD3);
    // GPIO pins; A2 A3 = left motors, A4 A5 = right motors
    DDRC = (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);

    // Phase correct PWM
    //Make timer1 match at about 1hz
    TCCR1A |= (1 << COM1A0) | (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM13); 

    TIMSK1 = (1 << OCIE1A); //Enable interrupt on compare match A
    //TCCR1A = (1 << WGM13) | (1 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1A0) | (1 << COM1B0);
    TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1) | (1 << COM0A0) | (1 << COM0B0);
    // No prescaler
    //TCCR1B = (1 << CS10);
    TCCR0B =  (1 << CS00);

    //OCR1A = 150;
    //OCR1B = 150;
    OCR0A = 25;
    OCR0B = 25;
    OCR1A = 10000; //Increase to decrease frequency at which sensor is read
}

void init_sensor(void)
{
//UltraSonic Sensor
 ADCSRA|=(1<<ADEN)|(1<<ADPS2) ;//|(1<<ADIE); //enable with prescalar  at 16 (65kHz conversion clock speed)
 //The higher the prescalar the "slower" the alternatation of the freq., if its 0, then you don't see the change in the freq. (static red, eyes can't catch it).
 ADMUX |= 0 | (1<<REFS0); // Vcc ( 5v) conversion scale
 //sei();
}

void brake(int ms)
{
    PORTC = 0;
    _delay_ms(ms);
}

void drive_forwards(int ms)
{
    PORTC = (1 << PC4) | (1 << PC3);
    _delay_ms(ms);
}

void drive_left(int ms)
{
    PORTC = (1 << PC4); 
    _delay_ms(ms);
}

void drive_right(int ms)
{
    PORTC = (1 << PC3);
    _delay_ms(ms);
}

void drive_backwards(int ms)
{
    PORTC = (1 << PC5) | (1 << PC2);
    _delay_ms(ms);
}

ISR(TIMER1_COMPA_vect){
  cli();
  PORTD ^= (1 << PD3);
  ADCSRA |= (1<<ADSC); //Start Conversion
 while(!(ADCSRA & (1<<ADIF))){ }   //Wait for ADIF to go to 0, indicating conversion complete.
 ADCSRA|=(1<<ADIF);           //Reset ADIF to 1 for the next conversion.
 Serial.println(ADC);
  //if (ADC <= 120){
  //if (ADC <= 80){
  if (ADC <= 30){
    mode = STOP;
    //spi_transceiver('S'); //Might cause issues with driving
  }else{
    mode = DRIVE;
  }
  sei();
}


//SPI---------------------------
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
void init_communication(void){
//Wait until BBB sends H for I'm here
     uint8_t rec;
     spi_slave_enable();
     while(1){
        rec = spi_transceiver('W');
           // Serial.print("Received from BBB");
           // Serial.println(rec);
        if (rec == 'H'){ //BBB saying I'm here
           //Serial.println(rec);
            Serial.println("Communication initiated");
            break;
        }else{
//            Serial.println(rec);
            continue;
        }
     }
}
