/*

DUTY CYCLE=X/256 *100%
50=(X/256) * 100 %
X=127
OCR0A=127


F_Gen = F_Osci/(256*N)
976.56Hz=16MHz/256*N
N=64
therefore the prescaler is selected as 64

*/

#include <avr/io.h>

int main(){

  DDRD = DDRD | (1<<6);//set pd6 to output
  
  OCR0A = 127;//pwm duty cycle = 50%
  DDRB =  DDRB|(1<<5);
  PORTB = PORTB |(1<<5); //light 5v led
 
  TCCR0A = TCCR0A | ( 1 << WGM01 ) |( 1 << WGM00 ); //fast pwm 
  TCCR0B &= ~(1<<WGM02); //fast pwm

  TCCR0A = TCCR0A | 1<< COM0A1;//non inverting mode
  TCCR0A &= ~(1<<COM0A0); //non inverting

  TCCR0B = 0x03; //pre-scaler is 64
  
  while(1)
  {
  }
  

}


void initPWM(){
//OCR0A= 127 //50%
TCCR0A |= (1<<WGM00) | (1<<WGM01); //select fast PWM mode in timer 0
TCCR0B &= ~(1<<WGM02);
TCCR0A |= (1<<COM0A1) ;
TCCR0A &= ~(1<<COM0A0); //select COM0 is 10 non inverting mode
TCCR0B |= 0x03; //select clock to 1:64 prescaler CS02:0 = 011
/*changing prescaler --> changing frequency
while(1){
TCCR0B = 0x05; //select clock to 1:1024
prescaler CS02:0 = 101 , frequency = 61.035 Hz
_delay_ms(1000); //keep for 1s
TCCR0B = 0x04; //select clock to 1:256
prescaler CS02:0 = 100, frequency = 245.141 Hz
_delay_ms(1000); //keep for 1s
TCCR0B = 0x03; //select clock to 1:64
prescaler CS02:0 = 011, frequency = 976.56 Hz
_delay_ms(1000); //keep for 1s
TCCR0B = 0x02; //select clock to 1:8
prescaler CS02:0 = 010, frequency = 7812.5 Hz
_delay_ms(1000); //keep for 1s
} */
ADCSRA |= (1<<ADEN); //enable ADC module
}



/*
ATmega328 TIMER0 has 2 outputs, OC0A (Timer/Counter 0 Output Compare Match A Output) and OC0B (Timer/Counter 0 Output Compare Match B Output).

When the counter value in TCNT0 reaches OCR0 the PWM pin is set to low

Note that in ATmega 328P this waveform is called the non-inverted mode.

Steps

● Configure the corresponding PWM pin as an output pin.

● Find the counts required for the given duty cycle and write it to OCR0A.

● Configure the PWM settings.

➢ Select the timer mode. In lab 3 we used the normal mode. But today we should use Fast PWM mode. (See WGM01:0 bits in TCCR0A and WGM02 in TCCR0B)

➢ We are using a non inverting mode. So select that. (See COM0A1 and COM0A0 bits in TCCR0A. Use the correct table for Fast PWM since we are using that)

● Select the clock source. (See CS02:0 in TCC0B) You should use the correct prescaler to match the required period for the generated PWM. Note that when you select the clock source, the timer starts running and hence the PWM waveform should appear on the corresponding PWM pin.

● Now PWM is running. You can use the CPU for something else. If not, remember to put a while(1) loop to prevent the program from ending.

