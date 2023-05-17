/*
 * manchesterDecoder2.cpp
 *
 * Created: 17-05-2023 11:01:58
 *  Author: olive
 */ 
#include <string.h>


#define ADDRESS_SIZE 4

char* testInput = "111010100101";
char defuck = 0;

void manchesterDecoder2(char* inputBits, char* outputBuffer, char inputSize, char outputSize)
{
	char addressBits[5] = "1110";
	//strncpy(addressBits, inputBits, ADDRESS_SIZE);
	
	char dataBits[9] = "10100101";
	//strncpy(dataBits, inputBits + ADDRESS_SIZE, inputSize - ADDRESS_SIZE);
	
	char decodedBits[5] = "0000";
	
	if (strcmp(addressBits, "1110") == 0)
	{
		char ite = 0;
		for (char i = 0; i < inputSize - ADDRESS_SIZE - 1; i += 2)
		{
			if (dataBits[i] == '0' && dataBits[i + 1] == '1')
			{
				char zero = '0';
				decodedBits[ite] = '0';
			}
			else if (dataBits[i] == '1' && dataBits[i + 1] == '0')
			{
				char one = '1';
				decodedBits[ite] = '1';
			}
			else
			{
				defuck = 3;
			}
			
			ite++;
		}
	}
	else
	{
		defuck = 4;
	}
	
	outputBuffer = decodedBits;
}

int main(void)
{
	char myOutput[5];
	manchesterDecoder2(testInput, myOutput, 13, 5);
	
	return 0;
}
