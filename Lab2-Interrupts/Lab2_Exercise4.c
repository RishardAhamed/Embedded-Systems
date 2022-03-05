#include <avr/io.h>//standard AVR header
#include <util/delay.h>
#include <avr/interrupt.h>//include the interrupt header file



int count=0;//count variable is set to 0
int main(){

  DDRB = DDRB | (1<<5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0 );//PIN 0,1,2,3,4,5 of PORTB are configured as outputs
  DDRD = DDRD & ~(1<<2);//PIN 2 of PORTD is configured as input
  DDRD = DDRD & ~(1<<3);//PIN 3 of PORTD is configured as input
  
  //ISC01  bit in the EICRA (External Interrupt Control Register A) register set for rising edge detection of INT0 pin 
  EICRA |= (1<<ISC01);
 //ISC00  bit in the EICRA (External Interrupt Control Register A) register set for rising edge detection of INT0 pin 
  EICRA |= (1<<ISC00);
   //ISC11  bit in the EICRA (External Interrupt Control Register A) register set for rising edge detection of INT1 pin 
  EICRA |= (1<<ISC11);
   //ISC10  bit in the EICRA (External Interrupt Control Register A) register set for rising edge detection of INT1 pin 
  EICRA |= (1<<ISC10);
 //enable global interrupts 
  sei();
  //enable INT0 bit located in the EIMSK (External Interrupt Mask Register) register for external interrupt in PinD2
  EIMSK |= (1<<INT0);
  //enable INT1 bit located in the EIMSK (External Interrupt Mask Register) register for external interrupt in PinD2
  EIMSK |= (1<<INT1);
  //infinity loop for stop ending the program(keeps the processer busy until a interrupt generated) 
  while(1){
    
  }
 return 0;
}


int z=0;
//ISR routine for pinD2(push button A to input 0)
ISR(INT0_vect){
   z = z << 1; //z value is left shifted by 1
   
   PORTB = PORTB & ~ 0xFF;
   PORTB = PORTB | z;
   
   
}
//ISR routine for pinD3(push button B to input 1)
ISR(INT1_vect){
   z = (z << 1) + 1; //z value is left shifted by 1 and then added 1
 
  PORTB = PORTB & ~ 0xFF;
   PORTB = PORTB | z;
   
   
}                           