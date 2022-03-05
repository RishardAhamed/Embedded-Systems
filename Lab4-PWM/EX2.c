
#include <avr/io.h>
#include <util/delay.h>
int main(){

  DDRD = DDRD | (1<<6);//set pd6 to output
  
 TCCR0A = TCCR0A | ( 1 << WGM01 ) |( 1 << WGM00 ); //fast pwm 
  TCCR0A = TCCR0A | 1<< COM0A1;//non inverting mode
  
  TCCR0B = 0x03; //pre-scaler is 64
  
  while(1)

  {
  	for(int i=0;i<255;i++){
  		 OCR0A = i;
  		 _delay_ms(10);

  	}
  	for(int i=255;i<255;i--){
  		 OCR0A = i;
  		  _delay_ms(10);
  	}
  }
  

}