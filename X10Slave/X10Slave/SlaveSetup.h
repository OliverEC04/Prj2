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


















//Finde en l�sning til at skrive manchestercode som returnerer "int"

///////////////////////////////////////////////
//////////KODE TIL KAFFEMASKINE OSV.///////////
///////////////////////////////////////////////
/*

	- Skriv koden med en if-statement, som unders�ger om de f�rste bits er "1110"
	- Hvis dette passer laves der nogle if-s�tning til hver af de forskellige maskiner en masse variable som skal arbejde ud fra true/false (boolean)
	- Hvis kaffemaskine eksempelvist er h�j s�ttes den igang
	
	Slaven tager sig ikke af tiden, det h�ndterer masteren!!!!!!!!!!!!! Slaven skal bare udf�rer kommandoen s� snart den er modtaget.

*/

/////////////////////////////////////////
//////////Sp�rgsm�l til Torben///////////
/////////////////////////////////////////

//Skal vi have en funktion, som fort�ller hvorn�r vores zero-cross interrupt er klar til at modtage noget nyt og hvor langt tid skal der g�
//Skal vi have en funktion, som fort�ller hvorn�r vores interrupt er klar til at modtage noget nyt
//Skal vi have noget udover zero-cross interruptet

//Hvad bruges vi vores recieveCommand() funktion til, og hvordan f�r vi den til at registrerer et h�jt eller lavt hver gang der kommer et burst
//Skal vores recieveCommand() bruge vores funktioner til kaffemaskinen osv. eller skrives de ind i et main program.

