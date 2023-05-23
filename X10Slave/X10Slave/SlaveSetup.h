/*
 * SlaveSetup.h
 *
 * Created: 26-04-2023 13:19:39
 *  Author: ZakiN
 */ 


#ifndef SLAVESETUP_H_
#define SLAVESETUP_H_
#include <avr/interrupt.h>

void setUpInterruptZeroCross()
{
	//Initiering af port E, pin 3 som input til ZeroCross
	DDRE = 0;														
	
	//Any edge interrupt for INT5 enabled
	EICRB |= 0b00000100;														
	
	//Ekstern interrupt enable for INT5
	EIMSK |= 0b00100000;														
	
	//Initiering af port B, pin 11 som output til ZeroCross
	DDRB |= 0b00100000;															
}

#endif /* SLAVESETUP_H_ */


















//Finde en løsning til at skrive manchestercode som returnerer "int"

///////////////////////////////////////////////
//////////KODE TIL KAFFEMASKINE OSV.///////////
///////////////////////////////////////////////
/*

	- Skriv koden med en if-statement, som undersøger om de første bits er "1110"
	- Hvis dette passer laves der nogle if-sætning til hver af de forskellige maskiner en masse variable som skal arbejde ud fra true/false (boolean)
	- Hvis kaffemaskine eksempelvist er høj sættes den igang
	
	Slaven tager sig ikke af tiden, det håndterer masteren!!!!!!!!!!!!! Slaven skal bare udfører kommandoen så snart den er modtaget.

*/

/////////////////////////////////////////
//////////Spørgsmål til Torben///////////
/////////////////////////////////////////

//Skal vi have en funktion, som fortæller hvornår vores zero-cross interrupt er klar til at modtage noget nyt og hvor langt tid skal der gå
//Skal vi have en funktion, som fortæller hvornår vores interrupt er klar til at modtage noget nyt
//Skal vi have noget udover zero-cross interruptet

//Hvad bruges vi vores recieveCommand() funktion til, og hvordan får vi den til at registrerer et højt eller lavt hver gang der kommer et burst
//Skal vores recieveCommand() bruge vores funktioner til kaffemaskinen osv. eller skrives de ind i et main program.

