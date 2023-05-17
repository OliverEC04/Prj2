/*
 * ManchesterDecoder.h
 *
 * Created: 03-05-2023 11:09:57
 *  Author: ZakiN
 */


volatile bool intTrigger = false;

char* manchester_decoder(char bits[], int num_bits, int decoded_size) { //?
    
	char decoded_bits_array[4] = {1, 1, 1, 1};
	char* decoded_bits = decoded_bits_array;
	
	//int* decoded_bits = new int[4] { 0 };

    // Tjekker om de første 4 bits matcher [1, 1, 1, 0]
    if (bits[0] == 1 && bits[1] == 1 && bits[2] == 1 && bits[3] == 0) {
        // Dekod de næste 8 bits
        for (int i = 4; i < 12; i += 2) {
            if (bits[i] == 0 && bits[i + 1] == 1) {
                decoded_bits[(i - 4) / 2] = 0;
            }
            else if (bits[i] == 1 && bits[i + 1] == 0) {
                decoded_bits[(i - 4) / 2] = 1;
            }
            else {
                // Returner en tom vektor hvis dekodningen fejler
                decoded_size = 0; //?
                //delete[] decoded_bits;
                return NULL;
            }
        }
        decoded_size = 4; //?
    }
    else {
        // Returner en tom vektor hvis de første 4 bits ikke matcher
        decoded_size = 0; //?
        //delete[] decoded_bits;
        return NULL;
    }

    // Returner de dekodede bits
    return decoded_bits;
}


