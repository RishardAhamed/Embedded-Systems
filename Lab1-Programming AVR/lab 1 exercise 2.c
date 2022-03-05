//Lab Exercise 2
//9/6/2021
//E/17/327
//E/17/005


//included Standard AVR header
#include<avr/io.h>
#include <util/delay.h> 
//defined delay time 1000 ms
#define BLINK_DELAY_MS 1000

int main (void){
  // pin 2,3,4 and 5 of PORTB are configured as out put
  DDRB = DDRB|((1<<5)|(1<<4)|(1<<3)|(1<<2));
    //infinity loop             
    while(1){
     // for loop for the forward lightning pattern
      for(int i=2;i<=5;i++){
        //i th pin value of port B is set to high to light the led
        PORTB= PORTB|(1<<i);
        _delay_ms(BLINK_DELAY_MS);
        ////i th pin value of port B is cleared  to light the led
        PORTB= PORTB&~(1<<i);
         //_delay_ms(BLINK_DELAY_MS);
      }
     // for loop for the backword lightning pattern          
      for(int j=4;j>2;j--){
          //j th pin value of port B is cleared to light the led
        PORTB= PORTB|(1<<j);
        _delay_ms(BLINK_DELAY_MS);
         PORTB= PORTB&~(1<<j);
        // _delay_ms(BLINK_DELAY_MS);
      }         
               
               
               }
               
}