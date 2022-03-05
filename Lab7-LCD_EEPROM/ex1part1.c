#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
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

unsigned char usart_receive(){
/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
		;
/* Get and return received data from buffer */
	return UDR0;
}

void EEPROMWrite(unsigned int address, char data){
	while (EECR & (1<<EEPE)); //wait until previous writes are completed. once the EEPE is cleared only we can start writting. Previous writting is done

	EEAR=address;  //input the address of EEPROM where the data should be written
	EEDR=data; //input the data which is supposed to be written

	EECR|=(1<<EEMPE); //master write is enabled
	EECR|=(1<<EEPE); //slave write is enabled

}

char EEPROMread(unsigned int address){
	while (EECR & (1<<EEPE)); //wait until previous writes are completed.

	EEAR=address;  //input the address of EEPROM where the data should be read from

	EECR|=(1<<EERE); //read is enabled

	return EEDR; //return  the data that is read into the EEDR
}


int main (){

	usart_init(USART_UBRR);
	char message [1024];
	char charachter;
	unsigned int i=0;
	unsigned int mem_addr=0;

		while(charachter!='\r'){
			
			charachter = usart_receive();
			message[i]=charachter;

			i++;

		}
	
		for(int j=0;j<i;j++){

			EEPROMWrite(mem_addr,message[j]);

			mem_addr++;	

		}
	

	return 0;


}


/*

Writing to EEPROM The following procedure should be followed when writing the EEPROM (the order of steps 3 and 4 is not essential):
 1. Wait until a previous EEPROM write is finished (till EEPE becomes zero) 
 2. Write new EEPROM address 
 3. Write new EEPROM data 
 4. Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR 
 5. Within four clock cycles after setting EEMPE, write a logical one to EEPE

Reading from EEPROM 
1. Wait until a previous EEPROM write is finished (till EEPE becomes zero) 
2. Write new EEPROM address 
3. Start EEPROM read by writing to EERE 
4. Read the EEPROM data from data register

*/