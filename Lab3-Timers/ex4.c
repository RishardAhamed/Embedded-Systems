/*XTAL clock=1/16us ,
1:256 prescalar, 
clock_time_period=256*(1/16)=16us,
increments needed=1s/16us=62500,
initial counter value=65536-62500=3036*/

#include <avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>
void delay_time1(){
  TCNT1=3036;//load the timer counter
  TCCR1A=0x00;
  TCCR1B=0x04;//set the timer1 under normal mode with prescale 1/256
  
  sei();//enable global interrupts

  TIMSK1=(1<<TOIE1);//enable timer 1 overflow control interrupt

 }


  int main (void){
  DDRB = DDRB|((1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1));//pin 1,2,3,4,5 are configured as outputs
   delay_time1();//called timer1 delay function to toggle the pinB5 led
    while(1){
      
    
// for loop for the forward lightning pattern
      for(int i=1;i<=4;i++){
        //i th pin value of port B is set to high to light the led
        PORTB= PORTB|(1<<i);
        _delay_ms(1000);
        ////i th pin value of port B is cleared  to off the led
        PORTB= PORTB&~(1<<i);
         //_delay_ms(BLINK_DELAY_MS);
      }
     // for loop for the backword lightning pattern          
      for(int j=3;j>1;j--){
          //j th pin value of port B is cleared to light the led
        PORTB= PORTB|(1<<j);
        _delay_ms(1000);
         PORTB= PORTB&~(1<<j);
        // _delay_ms(BLINK_DELAY_MS);
      }         
               


    }

   
           
    

  }
ISR(TIMER1_OVF_vect){
   PORTB=PORTB^(1<<5);

   TCNT1=3036;

 
}


  
               

