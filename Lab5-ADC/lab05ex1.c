/*
 resolution = 10
step size = Vref/1024
*/
//frequency=16MHz/128=125kHz


#include <avr/io.h>

int main(){  

  int x;
//use adc1 in portc as input 
  DDRC = DDRC & ~(1<<1);
//define portD as output
  DDRD = 0xFF;

//turn on adc module
  ADCSRA |=(1<<ADEN);

  //select conversion speed
  //pre-scaler=128 , frequency=125kHz
  ADCSRA |=( 1<<ADPS0 | 1<< ADPS1 |1<<ADPS2 );

  //select voltage reference as -AVCC
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);

  
//select ADC input channels for ADC1 , 0001 from mux
  ADMUX |= 1<<MUX0;
  ADMUX &= ~(1<<MUX1 | 1<<MUX2 | 1<<MUX3);


  //start conversion
  ADCSRA |= 1<<ADSC;
  ADMUX &= ~(1<<ADLAR);//right justified

while(1){

    if((ADCSRA & (1<< ADIF))){//wait until conversion is complete
    
            x=(ADCH<<8)+(ADCL);
   //5v/8=0.625v
            if(x == 0)
                {PORTD = 0x00;//0 v
                }        
            else if(x<128) {//0v-0.625 V
                PORTD = 0x01;       
                }    
            else if(x<256) { //0.625-1.25 V     
                PORTD = 0x03;
                }    
            else if(x<384) {//1.25 -1.875 v
                PORTD = 0x07;
                }    
            else if(x<512) { //1.875 -2.5 v
                PORTD = 0x0F;
                }    
            else if(x<640) {  //2.5 -3.125 v
                PORTD = 0x1F;
                }    
            else if(x<768) {//3.125 -3.75 v
                PORTD = 0x3F;
                }    
            else if(x<896) {//3.75 -4.375 v
                PORTD = 0x7F;
                }    
            else{
                PORTD = 0xFF;//5v              
                }
           
      
            }
          }

return 0;
}




/*

Steps in programming the A/D converter using polling
To program the A/D converter of the AVR, the following steps can be taken:
(1) Make the pin for the selected ADC channel an input pin.

(2) Turn on the ADC module of the AVR, because it is disabled upon power-on reset to save power.

(3) Select the conversion speed. We use registers ADPS2:0 to select the conversion speed.

(4) Select voltage reference and ADC input channels. We use the REFS0 and REFS1 bits in the ADMUX register to select voltage reference and the MUX4:0 bits in ADMUX to select the ADC input channel.

(5) Activate the start conversion bit by writing a one to the ADSC bit of ADCSRA.

(6) Wait for the conversion to be completed by polling the ADIF bit in the ADCSRA register.

(7) After the ADIF bit has gone HIGH, read the ADCL and ADCH; otherwise, the result will not be valid.

(8) If you want to read the selected channel again, go back to step 5.

(9) If you want to select another Vref source or input channel, go back to step 4.


*/

void initADC(){
ADCSRA |= (1<<ADEN); //enable ADC module
/* Frequency of oscillator = 16 MHz
Clock frequency must be less than 200kHz
Therefore prescaler value range is x,
Then, 16000/200 = 80 < x
Suitable prescaler x = 128
ADPS2:0 = 111 for prescaler 1:128
*/
ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
//selecting conversion speed 125kHz by prescaler 1:128
ADMUX |= (1<<REFS0);
ADMUX &= ~(1<<REFS1);
//Select voltage reference as AVCC with external capacitor at AREF pin
ADMUX |= ((1<<MUX0)|(1<<MUX1));
ADMUX &= ~((1<<MUX3)|(1<<MUX2)); //Select ADC input channel as ADC3
ADMUX |= (1<<ADLAR); //left justify
ADCSRA |= (1<<ADSC);
}