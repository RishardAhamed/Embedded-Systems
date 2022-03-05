/*XTAL clock=1/16us ,
1:256 prescalar, 
clock_time_period=256*(1/16)=16us,
increments needed=2ms/16us=125,
initial counter value=255+1-125=131*/

/*XTAL clock=1/16us ,
1:256 prescalar, 
clock_time_period=256*(1/16)=16us,
increments needed=20ms/16us=1250,
initial counter value=65535+1-1250=64286*/


#include <avr/io.h>
#include<avr/interrupt.h>

int counter0=0;
int counter1=0;
//delay function for 2ms using timer 0
void delay_time0(){
  TCNT0=131;//load the timer counter
  TCCR0A=0x00;
  TCCR0B=0x04;//set the timer0 under normal mode with prescale 1/256
  
  sei();//enable global interrupts

  TIMSK0=(1<<TOIE0);//enable timer 0 overflow control interrupt
}
//delay function for 20ms using timer 1
void delay_time1(){
  TCNT1=64286;//load the timer counter
  TCCR1A=0x00;
  TCCR1B=0x04;//set the timer1 under normal mode with prescale 1/256
  
  sei();//enable global interrupts

  TIMSK1=(1<<TOIE1);//enable timer 1 overflow control interrupt
}
  int main (void){
  DDRB=DDRB|(1<<5)|(1<<4);
  delay_time0();
  delay_time1();

    while(1){
    
    }
  }

//ISR for timer 0
ISR(TIMER0_OVF_vect){
    counter0++;
  TCNT0=131;
    if (counter0>=25){
      PORTB=PORTB^(1<<5);
      counter0=0;
    }
   
}
//ISR for timer 1
ISR(TIMER1_OVF_vect){
    counter1++;
  TCNT1=64286;
    if (counter1>=25){
      PORTB=PORTB^(1<<4);
      counter1=0;
    }
   
}