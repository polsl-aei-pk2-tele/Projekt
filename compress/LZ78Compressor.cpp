#include "LZ78Compressor.h"
#include <map>
#include <iostream>
using namespace std;


string LZ78Compressor::compress(string input)
{
	map<string, unsigned short> dictionary; //Słownik mapujący ciągi 
	string result = ""; 			// the compressed output
	string c = "";			// the character of the charstream under examination by the algorithm
	unsigned short n = 1; //65535 possible dictioanry size

	for (unsigned int i = 0; i < input.length(); ++i)
	{
		string s = std::string(1, input[i]);
		if (dictionary.count(c + s)) //we found occurence in dictionary
		{
			c = c + s;
		}
		else //there is no occurence in dictionary
		{
			if (c.empty())
			{
				result.append(shortToString(0) + s);
				dictionary.insert(pair<string, unsigned short>(s, n));
			}
			else
			{
				result.append(shortToString(dictionary[c]) + s);
				dictionary.insert(pair<string, unsigned short>(c + s, n));
			}

			if (n >= 65535)
				throw "Exceeded maximum dictionary size";

			n++;
			c = "";
		}
	}
	return result;
}


string LZ78Compressor::decompress(string input)
{
	map<unsigned short, string> dictionary; //Słownik mapujący ciągi 
	string result = ""; 			// the compressed output
	unsigned short n = 1;

	for (unsigned int i = 0; i < input.length(); i += 3) //we know that our tokens have 3 bytes in width (2 keys, 1 char)
	{
		unsigned short k = stringToShort(string(1,input[i]) + string(1,input[i + 1]));
		string s = string(1,input[i + 2]);

		if (k == 0)
		{
			result.append(s);
			dictionary.insert(pair<unsigned short, string>(n,s));
			n++;
		}
		else 
		{
			result.append(dictionary[k] + s);
			dictionary.insert(pair<unsigned short, string>(n, dictionary[k] + s));
			n++;
		}
	}

	return result;
}

string LZ78Compressor::shortToString(unsigned short input)
{
	unsigned char r[2];
	r[0] = (unsigned char)input & 0xff;
	r[1] = (unsigned char)(input >> 8) & 0xff;
	return string(1, r[0]) + string(1, r[1]);
}

unsigned short LZ78Compressor::stringToShort(string input)
{
	return (unsigned short)(((unsigned char)input[1] << 8) |
		(unsigned char)input[0]);
}