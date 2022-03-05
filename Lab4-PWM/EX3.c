/*

DUTY CYCLE=X/256 *100%
50=(X/256) * 100 %
X=127
OCR0A=127


F_Gen = F_Osci/(256*N)

f_Gen=16MHz/(256*8)
f_Gen=7812.5 Hz

f_Gen=16MHz/(256*64)
f_Gen=976.56 Hz

f_Gen=16MHz/(256*256)
f_Gen=244.14 Hz

f_Gen=16MHz/(256*1024)
f_Gen=61.03 Hz 



*/

#include <avr/io.h>
#include <util/delay.h>
#define DELAY 2000
int main(){

  DDRD = DDRD | (1<<6);//set pd6 to output
  
  //TCNT0=0x00;

  TCCR0A = TCCR0A | ( 1 << WGM01 ) |( 1 << WGM00 ); //fast pwm 
  TCCR0A = TCCR0A | 1<< COM0A1;//non inverting mode
  
  OCR0A = 127;//127- Duty cycle of 50%
  while(1)

  {

  	TCCR0B = 0x05;// 61.03 Hz
    _delay_ms(DELAY);
    TCCR0B = 0x04; //244.14 Hz
   _delay_ms(DELAY);
    TCCR0B = 0x03; //976.56 Hz
   _delay_ms(DELAY);
    TCCR0B = 0x02; 
   _delay_ms(DELAY);//7812.5 Hz
  
  }
  return 0;

}