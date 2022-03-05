
#include <avr/io.h>
#define FOSC 16000000
#define USARTBAUD_RATE 9600
#define USART_UBRR FOSC/16/USARTBAUD_RATE-1
void usart_init(long MY_UBRR){

//Set baud rate 
	UBRR0H = (unsigned char)(MY_UBRR>>8);
	UBRR0L = (unsigned char)MY_UBRR;
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);//enable transmitter and receiver
	//set ( asynchronous | No parity | 1 stop bit | 8 data bit )
	UCSR0C = ( 0<<UMSEL00 | 0<<UPM00 |0<<USBS0| 3<<UCSZ00 );

}
void usart_send(unsigned char data){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));
/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char usart_receive(){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)));
/* Get and return received data from buffer */
	return UDR0;
}


int main (){
	int key=3;
	usart_init(USART_UBRR);
	unsigned char chr=0;
	char ch;
	
	while(1){

	ch=usart_receive();
	

	while(ch!='\r'){
		

		if((ch >= 'A' && ch <= 'Z')){
			ch = ((ch-'A'+ key)%26)+'A';
		}
		
		else if ((ch >= 'a' && ch <= 'z')){
			ch = ((ch-'a'+ key)%26)+'a';
			}
		
		
		else {
				ch=ch;
		}
			usart_send(ch);
			ch=usart_receive();
		
		}
	}
	}
