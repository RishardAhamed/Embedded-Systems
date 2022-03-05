# include <avr/io.h>//standard AVR header
#include <util/delay.h>
#define BLINK_DELAY 500
int main(){

  DDRB = DDRB|((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));//PIN 0,1,2,3,4,5 of PORTB are configured as outputs
  DDRD &= ~(1<<7);               //PIN 7 of PORTD is configured as input
  int count;                     //A variable to count the number of times that push button is pressed
  
  while(1){ //infinity loop
    if(PIND&(1<<7)){            //check whether the button is pressed(Check whether the PIN& of PORTD is 1)
      count++;                  //if button is pressed increase the count
      PORTB=PORTB|count;        //assign that count value to portB to to display the number of times the push button is pressed, as a binary number
      _delay_ms(BLINK_DELAY);   //time delay
      PORTB=PORTB&~(count);     //turn off the Leds.
    
    }
  }
}