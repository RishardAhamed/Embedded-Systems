#include <avr/io.h>
void delay_time0(){
  TCNT0=131;//load the timer counter
  TCCR0A=0x00;
  TCCR0B=0x04;//set the timer0 under normal mode with prescale 1/256
  
  while((TIFR0&0x01)==0);//wait timer till overflow (T0V0) is set
  TCCR0A=0x00;//clear timer settings
  TCCR0B=0x00; 
  TIFR0=0x01;//Clear timer overflow
}
  int main (void){
  DDRB=DDRB|(1<<5);
    while(1){
      PORTB=PORTB^(1<<5);//toggle the led
      delay_time0();
    }
  }
