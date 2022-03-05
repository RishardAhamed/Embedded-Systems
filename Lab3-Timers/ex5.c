/*XTAL clock=1/16us ,
1:256 prescalar, 
clock_time_period=256*(1/16)=16us,
increments needed=2ms/16us=125,
initial counter value=255+1-125=131*/


#include <avr/io.h>
#include<avr/interrupt.h>

int counter=0;
//timer for 2ms delay 
void delay_time0(){
  TCNT0=131;//load the timer counter
  TCCR0A=0x00;
  TCCR0B=0x04;//set the timer0 under normal mode with prescale 1/256
  
  sei();//enable global interrupts

  TIMSK0=(1<<TOIE0);//enable timer 0 overflow control interrupt
}
  int main (void){
  DDRB=DDRB|(1<<5);
  delay_time0();
    while(1){

    
    }
  }


  ISR(TIMER0_OVF_vect){
    counter++;
    TCNT0=131;
    if (counter>=50){
      PORTB=PORTB^(1<<5);
      counter=0;
    }
   }


