#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define MAXSIZE 10
#define ALPHABET_SIZE 15

// initialize the lcd screen with the pins used 
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);   //LiquidCrystal(rs, enable, d5, d4, d3, d6)
char done = '#'; 	//enter

char alphabet[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','*'};
char keypad[4][4] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};//2D array to define keys and positions in keypad

// array for hold the input pins 4 and 5 in portc and 4 and 5 in port b
int inputPins[4] = {4, 5, 4, 5};

char getKey() //functions to get keys pressed
{
  
  // polling to get inputs
  while (1) 
  {
    for (int i = 0; i < 4; i++)
    {
      
      PORTC &= 0b11110000;//input and output pins are set

      
      PORTC |= 1<<(i); //set the current line high (power the columns)

  
      for (int j = 0; j < 4; j++) //checking the rows
      {
        if (j < 2) //check pin 4 and pin 5 in port c
        {
          if ((PINC>>inputPins[j])&1)//check if pin 4 or pin 5 in port c is high
          {
            _delay_ms(350);
            return(keypad[i][j]); //return the cordinates
          }
        } 
        else //check pin 4 and pin 5 in port B
        {

          if ((PINB>>inputPins[j])&1)//check if pin 4 or pin 5 in port b is high
          {
            _delay_ms(350);
            return(keypad[i][j]); //return the cordinates
          }
        }
      }
    }
  }
}

// function to get the index of a character according to alphabet in key pad
int get_index(char c)
{
    int i = 0;
    // go through the alphabet and return the index
    for(i = 0; i < ALPHABET_SIZE; ++i){
        if(alphabet[i] == c) return i;
    }
    return '0';
}



void encrypt(char *str, int secret_key)
{
    int column = 0; //initialise the column
    int index = 0; //initialise the index
    char *word = str; //input arguments set to new pointer variable word
	
    while(1)//infinite loop
    {
        if(*word == done) break; //if word='#' then jump out of loop
      
        index = (get_index(*word) + secret_key) % ALPHABET_SIZE;  //cipher algorithm
      
      	lcd.setCursor(column, 1);      //set the cursor position where it needs to print
     	lcd.print(alphabet[index]);    //print charachter
    	
        column++;                   //increment the column
        word++;                     //increment the charachter in the word
    } 
}

int main()
{

  // set up the LCD
  lcd.begin(16, 2);
  
  // Set PC0, PC1, PC2, PC3 as outputs
  DDRC |= 0b00001111;
  // set PC4, PC5 as inputs
  DDRC &= ~(0b00110000);
  // set PB4, PB5 as inputs
  DDRB &= ~(0b00110000);  
  
  int X_cordinate = 0;
  int Y_cordinate = 0;
  
  char input, choice[2];
  int index = 0;
  int key = EEPROM.read(0);
  
  char plain_text[MAXSIZE];
  char encrypted[MAXSIZE];
    
  // infinite loop 
  while(1)
  {
 	lcd.setCursor(0, 0);                //1st row
	// Select option is displayed
	lcd.print("1- Encrypt Text"); //option 1
    lcd.setCursor(0, 1);           //2nd row
    lcd.print("2- New key");    //option 2
    
    
    input = getKey();       //get the input of user and assign to input variable     
    
    
    lcd.clear();            //clear the screen
    
    if(input == '1') //if option 1 is selected
    {
   	  lcd.setCursor(0, 0);
      lcd.print("Enter:");
      
      input = '0'; //input cleared
      X_cordinate = 0;
      Y_cordinate = 1; //always 2nd row
      
      index = 0; //index cleared
      lcd.setCursor(0, 1);
      
      // loop until done or exceed range
      while(input != done && index <= 9)
      {
      	input = getKey();
        lcd.print(input);
        X_cordinate++;
        
        // add to plain text array
        plain_text[index] = input; //keys that are typed are saved in an array
        index++;
              
        lcd.setCursor(X_cordinate, Y_cordinate); 
      }
     //plain_text[index] = done; //append the done symbol to the array
     lcd.clear();
		
     lcd.setCursor(0, 0);
     lcd.print("Encrypted Result: ");
    
     lcd.setCursor(0, 1);
     // encrypt and display/print the text 
     encrypt(plain_text, key);
     
     _delay_ms(2000);  
      
    }
     else if(input == '2')
     {
      key = 0;
      // promt user to get the key
      lcd.setCursor(0, 0);
      lcd.print("Enter key:");
      lcd.setCursor(0, 1);
      lcd.print("__");
      
      // get the secret key
      input = getKey();
      lcd.setCursor(0, 1);
      lcd.print(input);
      // get the first digit
      key += (input-'0')*10; //value as a multiple of 10
        
      _delay_ms(350);
      // get input for second digit
      input = getKey();
      lcd.setCursor(1, 1);
      lcd.print(input);
      key += (input-'0');         
       
      
      EEPROM.write(0,key);    // write key to EEPROM     
    }

    else
    {
        // display the error message
    	lcd.setCursor(4, 0);
      	lcd.write("Error!!");
      	_delay_ms(1000);
      	lcd.clear();
    }
    
    _delay_ms(350);
  
}
 return 0;

}


