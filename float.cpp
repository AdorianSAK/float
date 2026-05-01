//	Please, use the third line as the compile method
//	Keep in mind that this was thinked for gnuLinux systems
//	g++ -std=c++20 *.cpp -o app
//	made with ♥️
//===
//	Rquired Libraries
//===

#include <iostream>
#include <fstream>
#include <cstdint>
#include <termios.h>
#include <unistd.h>
#include <bit> 

//===
//	Definitions
//===

#define B_DARKGREEN "\e[48;5;22m"
#define CYAN "\e[38;5;045m"
#define RESET "\033[0m"
#define WHITE "\e[38;5;255m"

struct quantity
{
	bool sign = false;
	int exponent = 0;
	int mantissa = 0;
};

//===
//	Prototyping
//===

void showSPlash();
void clearScreen();
std::string jump(int y, int x);
std::string showExponen(const int exponent);
std::string showSign(const bool sign);
float buildFloat(const quantity value);
std::string showMantissa(const int mantissa);
char readKey();
void printScreen();
quantity multiply(quantity a, quantity b);
quantity add(quantity a, quantity b);
quantity subtract(quantity a, quantity b);
quantity divide(quantity a, quantity b);
quantity decomposeFloat(float f);

int allignY = 20;
int allignX = 4;
quantity first;
quantity second;
quantity third;

/*
int bitGrid[2][32];
int X = 0;
int Y = 0;
*/

//===
//	Start of Program
//===

int main()
{
	first.exponent = 127;
	first.sign = true;
	first.mantissa = 6012416;
	second.exponent = 128;
	float sFloat = 0.0;

	clearScreen();
	showSPlash();
	char userKey;
	do
	{
		printScreen();
		userKey = readKey();
		switch(userKey)
		{
		case 'm':

			third = multiply(first, second);
			break;
		case 's':
			third = add(first, second);
			break;
		case 'd':
			third = subtract(first, second);
			break;
		case 'f':
			third = divide(first, second);
			break;
		case '1':
			std::cout << jump(allignY, allignX + 52);
			std::cout << "            ";
			std::cout << jump(allignY, allignX + 52);
			std::cin >> sFloat;
			first = decomposeFloat(sFloat);
			break;
		case '2':
			std::cout << jump(allignY + 4, allignX + 52);
			std::cout << "            ";
			std::cout << jump(allignY + 4, allignX + 52);
			std::cin >> sFloat;
			second = decomposeFloat(sFloat);
			break;
		case 'q':
			clearScreen();
			std::cout << "Thanks for using.\n";
			break;
		}
		//std::cout << "You pressed " << userKey << '\n';
	}while(userKey != 'q');
	

	return 0;
}

//===
//	Functions
//===
	
void showSPlash()
{
	std::ifstream splash("splash.txt");
	if(splash.is_open())
	{
		std::string line;
		int counter = 1;
		while(std::getline(splash, line))
		{
			if(counter == 10)
			{
				std::cout << CYAN << line << RESET << '\n';
			}else if(counter == 16)
			{
				std::cout << WHITE << line << '\n';
				for(int i = 0; i < 29; i ++)
				{
					std::cout << "║" << jump(counter + (i + 1), 99) << "║\n";
				}
			}else
			{
				std::cout << line << '\n';
			}
			counter ++;
		}
		std::cout << RESET;
	}else
	{
		std::cout << "Failed o open splash.\n";
	}
	splash.close();
}

void printScreen()
{
	std::cout << jump(allignY - 2, allignX + 10);
	//std::cout << "Edit mode: Binary";
	std::cout << "Binary";
	std::cout << jump(allignY, allignX);
	std::cout << " " << showSign(first.sign) << "  " << showExponen(first.exponent)
			  << "  " << showMantissa(first.mantissa);
	std::cout << jump(allignY, allignX + 52);
	std::cout << buildFloat(first);
	std::cout << jump(allignY + 1, allignX);
	std::cout << "└─┘└────────┘└───────────────────────┘";
	std::cout << jump(allignY + 2, allignX);
	std::cout << "Sign, Exponent, Mantissa";
	//	Second
	std::cout << jump(allignY + 4, allignX + 52);
	std::cout << buildFloat(second);
	std::cout << jump(allignY + 4, allignX);
	std::cout << " " << showSign(second.sign) << "  "  << showExponen(second.exponent)
			  << "  " << showMantissa(second.mantissa);
	std::cout << jump(allignY + 5, allignX);
	std::cout << "└─┘└────────┘└───────────────────────┘";
	std::cout << jump(allignY + 6, allignX);
	std::cout << "Sign, Exponent, Mantissa";

	//	results
	std::cout << jump(allignY + 8, allignX);
	std::cout << " " << showSign(third.sign) << "  " << showExponen(third.exponent)
			  << "  " << showMantissa(third.mantissa);
	std::cout << jump(allignY + 7, allignX + 52);
	std::cout << "Result";
	std::cout << jump(allignY + 8, allignX + 52);
	std::cout << "                        ";
	std::cout << jump(allignY + 8, allignX + 52);
	std::cout << buildFloat(third);
	std::cout << jump(allignY + 9, allignX);
	std::cout << "└─┘└────────┘└───────────────────────┘";
	std::cout << jump(allignY + 10, allignX);
	std::cout << "Sign, Exponent, Mantissa";

	std::cout << jump(allignY + 14, 38);
	std::cout << "Press " << CYAN << "S" << RESET << " to sum";
	std::cout << jump(allignY + 15, 38);
	std::cout << "Press " << CYAN << "D" << RESET << " to substract";
	std::cout << jump(allignY + 16, 38);
	std::cout << "Press " << CYAN << "M" << RESET << " to multiply";
	std::cout << jump(allignY + 17, 38);
	std::cout << "Press " << CYAN << "F" << RESET << " to divide";

	std::cout << jump(allignY + 19, 38);
	std::cout << "Press " << CYAN << "1" << RESET << " to modify first value";
	std::cout << jump(allignY + 20, 38);
	std::cout << "Press " << CYAN << "2" << RESET << " to modify second value";
	std::cout << jump(allignY + 22, 38);
	std::cout << "Press " << CYAN << "Q" << RESET << " to quit";

	std::cout << std::endl;
}

float buildFloat(const quantity value)
{
	uint32_t bits = 0;
	if(value.sign)
	{
		bits = bits | (1 << 31);
	}
	bits = bits | (value.exponent << 23);
	bits = bits | (value.mantissa);

	float f = std::bit_cast<float>(bits);
	//std::cout << bits << "\t";
	return f;
}

std::string showExponen(const int exponent)
{
	std::string str;
	for(int i = 7; i >= 0; i --)
	{
		if((exponent >> i) & 1)
		{
			str += '1';
		}else
		{
			str += '0';
		}
	}
	return str;
}

std::string showMantissa(const int mantissa)
{
	std::string str;
	for(int i = 22; i >= 0; i --)
	{
		if((mantissa >> i) & 1)
		{
			str += '1';
		}else
		{
			str += '0';
		}
	}
	return str;
}

std::string showSign(const bool sign)
{
	if(sign)
	{
		return "1";
	}else
	{
		return "0";
	}
}

quantity multiply(quantity a, quantity b)
{
    quantity result;

    // 1. Sign
    result.sign = a.sign ^ b.sign;

    // 2. Exponent (remove bias, add, reapply bias)
    int expA = a.exponent - 127;
    int expB = b.exponent - 127;
    int expResult = expA + expB;

    // 3. Mantissas (add implicit 1)
    uint32_t mantA = (1 << 23) | a.mantissa;
    uint32_t mantB = (1 << 23) | b.mantissa;

    // 4. Multiply mantissas (this becomes 48 bits)
    uint64_t mantResult = (uint64_t)mantA * mantB;

    // 5. Normalize (VERY IMPORTANT)
    if (mantResult & (1ULL << 47)) // overflow (2.xxxxx)
    {
        mantResult >>= 24;
        expResult += 1;
    }
    else
    {
        mantResult >>= 23;
    }

    // 6. Store result
    result.exponent = expResult + 127;
    result.mantissa = mantResult & 0x7FFFFF;

    return result;
}

quantity add(quantity a, quantity b)
{
    quantity result;

    // 1. Add implicit leading 1
    int32_t mantA = (1 << 23) | a.mantissa;
    int32_t mantB = (1 << 23) | b.mantissa;

    int expA = a.exponent;
    int expB = b.exponent;

    // 2. Align exponents
    if (expA > expB)
    {
        mantB >>= (expA - expB);
        result.exponent = expA;
    }
    else
    {
        mantA >>= (expB - expA);
        result.exponent = expB;
    }

    // 3. Apply sign (convert to signed integers)
    if (a.sign) mantA = -mantA;
    if (b.sign) mantB = -mantB;

    // 4. Add mantissas
    int32_t mantResult = mantA + mantB;

    // 5. Determine sign
    result.sign = (mantResult < 0);
    if (result.sign) mantResult = -mantResult;

    // 6. Normalize
    if (mantResult == 0)
    {
        result.exponent = 0;
        result.mantissa = 0;
        result.sign = 0;
        return result;
    }

    // Normalize right (overflow)
    while (mantResult >= (1 << 24))
    {
        mantResult >>= 1;
        result.exponent++;
    }

    // Normalize left (underflow)
    while (mantResult < (1 << 23))
    {
        mantResult <<= 1;
        result.exponent--;
    }

    // 7. Remove implicit 1
    result.mantissa = mantResult & 0x7FFFFF;

    return result;
}

quantity subtract(quantity a, quantity b)
{
    b.sign = !b.sign;   // flip sign of b
    return add(a, b);   // reuse your addition
}

quantity divide(quantity a, quantity b)
{
    quantity result;

    // 1. Sign
    result.sign = a.sign ^ b.sign;

    // 2. Exponent
    int expA = a.exponent - 127;
    int expB = b.exponent - 127;
    int expResult = expA - expB;

    // 3. Mantissas (add implicit 1)
    uint32_t mantA = (1 << 23) | a.mantissa;
    uint32_t mantB = (1 << 23) | b.mantissa;

    // 4. Divide mantissas (shift numerator for precision)
    uint64_t mantResult = ((uint64_t)mantA << 23) / mantB;

    // 5. Normalize
    if (mantResult >= (1 << 24))
    {
        mantResult >>= 1;
        expResult++;
    }
    else
    {
        while (mantResult < (1 << 23))
        {
            mantResult <<= 1;
            expResult--;
        }
    }

    // 6. Store result
    result.exponent = expResult + 127;
    result.mantissa = mantResult & 0x7FFFFF;

    return result;
}

quantity decomposeFloat(float f)
{
    quantity q;

    uint32_t bits = std::bit_cast<uint32_t>(f);

    // Extract sign (bit 31)
    q.sign = (bits >> 31) & 1;

    // Extract exponent (bits 30–23)
    q.exponent = (bits >> 23) & 0xFF;

    // Extract mantissa (bits 22–0)
    q.mantissa = bits & 0x7FFFFF;

    return q;
}

//===
//	System functions
//===

void clearScreen()	//	Removes everything on screen.
{
	std::cout << "\033[2J\033[1;1H";
}

std::string jump(int y, int x)
{
	return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H";
	//std::cout << "\033[6;11H";
}

char readKey()
{
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set new settings

    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) < 0) ch = 0; // Read single char

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    return ch;
}
