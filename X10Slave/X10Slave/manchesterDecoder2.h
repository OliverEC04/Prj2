
char manchesterDecoder2(char encodedByte)
{
	char decodedByte = 0;
	char checkByte;

	for (char i = 0; i < 4; i++)
	{
		checkByte = (encodedByte << (i * 2)); // Shift 2 right, since we only check the two right bits
		checkByte &= 0b11000000; // Set all other bits than the two left to 0
		
		if (checkByte == 0b10000000) // if 10 (1)
		{
			// Shift 1 left, and add 1 on right
			decodedByte = (decodedByte << 1);
			decodedByte |= 0b00000001;
		}
		else if (checkByte == 0b01000000) // if 01 (0)
		{
			// Shift 1 left
			decodedByte = (decodedByte << 1);
		}
		else
		{
			// Invalid number
		}
	}
	
	return decodedByte;
}