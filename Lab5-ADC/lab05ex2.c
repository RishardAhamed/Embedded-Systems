
#include <avr/io.h>

int main(){  
double x;

  //use adc1 in portc 
     DDRC  = DDRC & ~(1<<1);
    //define portB pin5s as output
     DDRB  = DDRB|(1>>5);

  //set voltage reference as external AREF 

  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);

   ADMUX |= 1<<ADLAR;//left justified
   
    //set adc1 input channel from mux
    ADMUX |= 1<<MUX0;
    ADMUX &= ~(1<<MUX1 | 1<<MUX2 | 1<<MUX3);

    //turn on adc module 
    ADCSRA |=(1<<ADEN);

    //start conversion
    ADCSRA |= 1<<ADSC;

    //select conversion speed
    //use 128 as div factor
    ADCSRA |=( 1<<ADPS0 | 1<< ADPS1 |1<<ADPS2 );  

    while(1){

        if(ADCSRA & (1<< ADIF)){ 

  if(ADCH>127) 
     PORTB |= 1<<5;
  else
    PORTB &= ~(1<<5);

  ADCSRA |= 1<<ADSC;
 
}






       }
return 0;

}
