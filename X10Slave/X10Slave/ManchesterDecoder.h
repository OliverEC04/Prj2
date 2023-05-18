/*
 * ManchesterDecoder.h
 *
 * Created: 03-05-2023 11:09:57
 *  Author: ZakiN
 */


volatile bool intTrigger = false;

void manchester_decoder(const int* bits, int num_bits, int* decoded_bits, int& decoded_size) {
	// Check if the first 4 bits match [1, 1, 1, 0]
	if (bits[0] == 1 && bits[1] == 1 && bits[2] == 1 && bits[3] == 0) {
		// Decode the next 8 bits
		for (int i = 4; i < 12; i += 2) {
			if (bits[i] == 0 && bits[i + 1] == 1) {
				decoded_bits[(i - 4) / 2] = 0;
			}
			else if (bits[i] == 1 && bits[i + 1] == 0) {
				decoded_bits[(i - 4) / 2] = 1;
			}
			else {
				// Set decoded size to 0 if decoding fails
				decoded_size = 0;
				return;
			}
		}
		decoded_size = 4;
	}
	else {
		// Set decoded size to 0 if the first 4 bits don't match
		decoded_size = 0;
	}
}
