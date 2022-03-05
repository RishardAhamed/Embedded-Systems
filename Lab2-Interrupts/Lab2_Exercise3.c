#include <avr/io.h>//standard AVR header
#include <util/delay.h>
#include <avr/interrupt.h>//include the interrupt header file


int count;//variable to count number of times that the push button is released
int main(){

  DDRB = DDRB | (1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 );//PIN 0,1,2,3,4,5 of PORTB are configured as outputs
  DDRD = DDRD & ~(1<<2);//PIN 2 of PORTD is configured as input
  
  //ISC01  bit in the EICRA (External Interrupt Control Register A) register set for falling edge detection of INT0 pin 
  EICRA |= (1<<ISC01);
  //ISC00  bit in the EICRA (External Interrupt Control Register A) register cleared for falling edge detection INT0 pin 
  EICRA &= ~(1<<ISC00);
  //enable global interrupts
  sei();
  //enable INT0 bit located in the EIMSK (External Interrupt Mask Register) register for external interrupt in PinD2
  EIMSK |= (1<<INT0);
   //infinity loop for stop ending the program(keeps the processer busy until a interrupt generated)
  while(1){
    
  }
 return 0;
}

//interrupt service routine for INTO
ISR(INT0_vect){

    count++;//if a interrupt is generated count the number of times button is released
  PORTB=PORTB & ~0XFF ;//set portB value to 0 to off the leds
  PORTB=PORTB | count ;//light the leds to display number of times the push button was released as a binary number


}





