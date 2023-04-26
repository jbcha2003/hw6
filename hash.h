#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				HASH_INDEX_T w[5] = {0, 0, 0, 0, 0};
				int val = 0;
				int wIndex = 4;
				//string temp = "";
				for (int i = k.length() - 1; i >= 0; i--) {
					val++;
					if (val == 6 || i == 0) {
						std::string temp = k.substr(i, val);
						while (temp.length() < 6) {
							temp = 'a' + temp;
						}
						HASH_INDEX_T a1 = letterDigitToNumber(temp[0]);
						HASH_INDEX_T a2 = letterDigitToNumber(temp[1]);
						HASH_INDEX_T a3 = letterDigitToNumber(temp[2]);
						HASH_INDEX_T a4 = letterDigitToNumber(temp[3]);
						HASH_INDEX_T a5 = letterDigitToNumber(temp[4]);
						HASH_INDEX_T a6 = letterDigitToNumber(temp[5]);
						HASH_INDEX_T total =	(((((a1 * 36) + a2) * 36 + a3) *36 + a4) * 36 + a5) * 36 + a6;
						w[wIndex] = total;
						wIndex -= 1;
						val = 0;
					}
				}
				
				return (rValues[0] * w[0])+ (rValues[1] * w[1]) + (rValues[2] * w[2]) + (rValues[3] * w[3]) + (rValues[4] * w[4]);
				


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
				letter = tolower(letter);
        // Add code here or delete this helper function if you do not want it
				if ((int)letter >= 48 && (int)letter <= 57) {
					int val = (int)letter - 22; 
					HASH_INDEX_T digit = static_cast<HASH_INDEX_T>(val);
					return digit;
				}
				else {
					int val = (int)letter - 97;
					HASH_INDEX_T digit = static_cast<HASH_INDEX_T>(val);
					return digit;
				}
		}

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
