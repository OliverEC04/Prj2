/*
 * UART.h
 *
 * Created: 26-04-2023 11:47:56
 *  Author: Karl-Emil
 */ 


#ifndef UART_H_
#define UART_H_
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_int);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
#endif /* UART_H_ */