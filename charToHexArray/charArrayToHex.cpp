//============================================================================
// Name        : charArrayToHex.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>


using namespace std;


/**
 * Method to convert a char array to array of hex values for storing SHA-1 certs
 * @param c - pointer to char array from JSON
 * @param h	- pointer to const uint8_t array (location within eepromState)
 * @return success (1) or fail (0)
 */
bool charArrayToHex(const char *c, uint8_t *h, unsigned int size){

	unsigned int i;
	uint8_t temp_result[size];
	int pos = 0;

	for (i = 0; i < size; i++){

		temp_result[i] = 0;

		while(c[pos] != 'x'){
			pos++;

			if (c[pos]  == '\'' || c[pos]  == '"' || c[pos]  == 0)
				// Reached end of string
				return false;
		}

		// got to 'x'; next char is of interest
		pos++;

		for (int k = 16; k > 0; k = k - 15){
			//cout << "pos = " << pos << " ,c[pos] = " << c[pos] << endl;
			// Found a hex? Check both digits valid
			if (c[pos] >= '0' && c[pos] <= '9'){
				temp_result[i] += ((int)c[pos] - 48) * k;
				//printf("0 -> 9 temp_result[i]  = 0x%02x \n",temp_result[i]);
			}
			else if (c[pos] >= 'A' && c[pos] <= 'F'){
				temp_result[i] += ((int)c[pos] - 55) * k;
				//printf("A -> F temp_result[i]  = 0x%02x \n",temp_result[i]);
			}
			else
				// Somethings wrong!
				return false;

			pos++;
		}
		// printf("temp_result[i]  = 0x%02X\n",temp_result[i]);
	}

	if (i == size){
		// Filled buffer
		memcpy(h,temp_result, size);
		return true;
	}
	else
		// fail
		return false;
}

int main() {

	const char* temp = "0x94, 0xFC, 0xF6, 0x23, 0x6C, 0x37,	0xD5, 0xE7, 0x92, 0x78, 0x3C, 0x0B, 0x5F, 0xAD, 0x0C, 0xE4, 0x9E, 0xFD,	0x9E, 0xA8";
	uint8_t dest[20];


	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	charArrayToHex(temp, dest, sizeof(dest));

	cout << "dest now contains: ";

	for (unsigned int i = 0; i < sizeof(dest); i++){
		//cout << hex << dest[i];
		printf("0x%02X, ", dest[i]);
	}

	printf("\n");


	return 0;
}
