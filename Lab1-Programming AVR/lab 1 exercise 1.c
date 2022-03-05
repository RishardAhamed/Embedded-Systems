//Lab Exercise 1
//9/6/2021
//E/17/327
//E/17/005


//included Standard AVR header
#include<avr/io.h>
#include <util/delay.h> 
//defined delay time 1000 ms
#define BLINK_DELAY 1000

int main(void){
 // pin 2,3,4 and 5 of PORTB are configured as out put
  DDRB=DDRB |((1<<2)|(1<<3)|(1<<4)|(1<<5));
 //infinity loop 
  while(1){
   // PORTB = PORTB | ((1<<2)|(1<<3)|(1<<4)|(1<<5));
   //settin a time delay 
    _delay_ms(BLINK_DELAY);
    
     //toggling pin 2,3,4 and 5 of PORTB to blink leds
     PORTB = PORTB ^ ((1<<2)|(1<<3)|(1<<4)|(1<<5));
   
    //_delay_ms(BLINK_DELAY);
}
}