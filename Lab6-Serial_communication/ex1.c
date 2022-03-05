#include <avr/io.h>
#define FOSC 16000000                                 //frequency of the oscillator
#define USARTBAUD_RATE 9600 
#define USART_UBRR FOSC/16/USARTBAUD_RATE-1           //usart baud rate register value


void usart_init(long MY_UBRR){
//Set baud rate
UBRR0H = (unsigned char)(MY_UBRR>>8);
UBRR0L = (unsigned char)MY_UBRR;
//enable transmitter and receiver
UCSR0B=(1<<RXEN0)|(1<<TXEN0);
//set ( asynchronous | No parity | 1 stop bit | 8 data bit )
UCSR0C = ( 0<<UMSEL00 | 0<<UPM00 |0<<USBS0| 3<<UCSZ00 );

}

void usart_send(unsigned char data){
//Wait for empty transmit buffer 
while (!( UCSR0A & (1<<UDRE0)));
//Put data into buffer, sends the data 
UDR0 = data;
}

unsigned char usart_receive(){
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)));
/* Get and return received data from buffer */
return UDR0;
}


int main (){
//initializing the usart

usart_init(USART_UBRR);

unsigned char ch=0;

char c;

char str[]="M I Rishard E/17/005\nA M F Shalha E/17/327\n";

while(1){

while(str[ch]!='\r'){
usart_send(str[ch]);
ch++;

}
//c=usart_receive();
//usart_send(c);
}

}

/*
Programming the AVR to transfer data serially (polling method)

1. Enable the USART transmitter (See TXEN0 bit in UCSR0B). The transmitter will override normal port operation for the TxD pin when enabled.

2. Select asynchronous mode. We will use 8-bit data frame, no parity, and one stop bit. (See UCSR0C register)

3. The UBRR0 is loaded to set the baud rate for serial data transfer. (Select a baud rate supported in the serial tool you use on your PC and accordingly calculate the value)

4. The character byte to be transmitted serially is written into the UDR0 register.

5. Monitor the UDRE0 bit of the UCSR0A register to make sure UDR0 is ready for the next byte.

6. To transmit the next character, go to step 4.

Programming the AVR to receive data serially (polling method)

1. Enable the USART receiver (See RXEN0 bit in UCSR0B). The receiver will override normal port operation for the RxD pin when enabled.

2. Select asynchronous mode. We will use 8-bit data frame, no parity, and one stop bit. (See UCSR0C register)

3. The UBRR0 is loaded to set the baud rate for serial data transfer. (Select a baud rate supported in the serial tool you use on your PC and accordingly calculate the value)

4. The RXC0 flag bit of the UCSR0A register is monitored for a HIGH to see if an entire character has been received yet.

5. When RXC0 is raised, the UDR register has the byte.

6. To receive the next character, go to step 5.

*/