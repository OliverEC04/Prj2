
/************************************************
* "uart.c":                                     *
* Implementation file for Mega2560 UART driver. *
* Using UART 0.                                 *
* Henning Hargaard, 16/11 2022                  *
*************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

// Target CPU frequency
#define XTAL 16000000

/*************************************************************************
USART initialization.
    Asynchronous mode.
    RX and TX enabled.
    No interrupts enabled.
    Number of Stop Bits = 1.
    No Parity.
    Baud rate = Parameter.
    Data bits = Parameter.
Parameters:
    BaudRate:Wanted Baud Rate (300-115200).
    Databit: Wanted number of Data Bits (5-8).
    Parity: 'E' (Even parity), 'O' (Odd parity), otherwise No Parity.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_Int)
{
	if ((BaudRate >= 110) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
	{
		// No interrupts enabled
		// Receiver enabled
		// Transmitter enabled
		// No 9 bit operation
		UCSR0B = 0b00011000;
		// Enable RX interrupt (if required by parameter)
		if (RX_Int)
		UCSR0B |= (1<<7);
		// Asynchronous operation, 1 stop bit
		// Bit 2 and bit 1 controls the number of data bits
		UCSR0C = (DataBit-5)<<1;
		// Set Baud Rate according to the parameter BaudRate
		UBRR0 = XTAL/(16*BaudRate) - 1;
	}
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return UCSR0A & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
	//double count = 0;
  // Wait for new character received
  while ( (UCSR0A & (1<<7)) == 0 )
  {
	  //++count;
	  //if(count >= 16000000)
	//  return '0';
  }                        
  // Then return it
  return UDR0;
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSR0A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
  // Repeat until zero-termination
  while (*Streng != 0)
  {
    // Send the character pointed to by "Streng"
    SendChar(*Streng);
    // Advance the pointer one step
    Streng++;
  }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
char array[7];
  // Convert the integer to an ASCII string (array), radix = 10 
  itoa(Tal, array, 10);
  // - then send the string
  SendString(array);
}

/************************************************************************/
