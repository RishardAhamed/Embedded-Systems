#include <avr/io.h>
#define FOSC 16000000
#define USARTBAUD_RATE 9600
#define USART_UBRR FOSC/16/USARTBAUD_RATE-1
void usart_init(long MY_UBRR){

//Set baud rate
	UBRR0H = (unsigned char)(MY_UBRR>>8);
	UBRR0L = (unsigned char)MY_UBRR;
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);//enable transmitter and receiver
	UCSR0C=(1<<USBS0);//1 stop bit
	UCSR0C=(1<<UCSZ00)|(1<<UCSZ01);//8 bit data


}
void usart_send(unsigned char data){
/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
		;
/* Put data into buffer, sends the data */
	UDR0 = data;
}


char EEPROMread(unsigned int address){
	while (EECR & (1<<EEPE)); //wait until previous writes are completed

	EEAR=address;  //input the address where the data should be read from

	EECR|=(1<<EERE); //read is enabled

	return EEDR; //return  the data that is read into the EEDR
}


int main (){

	usart_init(USART_UBRR);

	char message;

	unsigned int mem_addr=0;
	
	for(mem_addr=0; mem_addr<1024;mem_addr++){

		message=EEPROMread(mem_addr);
		
		usart_send(message);

		
	}

	return 0;


}

