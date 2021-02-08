#include "LZ78Compressor.h"
#include <map>
#include <iostream>
using namespace std;


/// <summary>
/// Dokonuje kompresji, używając algorytmu LZ78
/// Uwaga:
/// - Maksymalny rozmiar słownika to 65535, gdy zostanie przekroczony, wyrzucony zostanie wyjątek
/// </summary>
/// <param name="input">Ciąg znaków, który ma zostać zakodowany</param>
/// <returns>Zakodowany ciąg znaków</returns>
string LZ78Compressor::compress(string input)
{
	map<string, unsigned short> dictionary; //Słownik mapujący ciągi 
	string result = ""; //output
	string c = "";			
	unsigned short n = 1; //65535 możliwych wartości w słowniku

	for (unsigned int i = 0; i < input.length(); ++i)
	{
		string s = std::string(1, input[i]);
		if (dictionary.count(c + s)) //kontener map, posiada w sobie unikalne wartości kluczy, count więc będzie zwracało 1 jeśli wartość istnieje i analogicznie 0 
		{
			c = c + s;
		}
		else 
		{
			if (c.empty()) //symbol s jeszcze nie występuje w słowniku
			{
				result.append(shortToString(0) + s);
				dictionary.insert(pair<string, unsigned short>(s, n));
			}
			else
			{	//c jest w słowniku, dodajemy c + s 
				result.append(shortToString(dictionary[c]) + s);
				dictionary.insert(pair<string, unsigned short>(c + s, n));
			}

			if (n >= 65535) //Wyjątek kiedy przekraczamy maksymalną wielkość słownika
				throw "Exceeded maximum dictionary size";

			n++;
			c = "";
		}
	}
	return result;
}

/// <summary>
/// Dokonuje dekompresji algorytmem LZ78
/// Uwaga:
/// - Maksymalny rozmiar słownika to 65535, gdy zostanie przekroczony, wyrzucony zostanie wyjątek
/// - Zakłada, że długość kodu jest równa 3
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
string LZ78Compressor::decompress(string input)
{
	map<unsigned short, string> dictionary; //Słownik mapujący ciągi 
	string result = ""; //output
	unsigned short n = 1;

	for (unsigned int i = 0; i < input.length(); i += 3) //wiemy, że nasz program koduje po 3 bajty (2 z klucza, 1 z symbolu)
	{
		unsigned short k = stringToShort(string(1, input[i]) + string(1, input[i + 1]));
		string s = string(1, input[i + 2]);

		if (k == 0)
		{
			result.append(s);
			dictionary.insert(pair<unsigned short, string>(n, s));
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

/// <summary>
/// Zamienia unsigned short na 2 bajty i przechowuje je jako string
/// </summary>
/// <param name="input">ushort który zostanie zkonwertowany</param>
/// <returns>string o rozmiarze 2, każda litera jest jednym z bajtów shorta</returns>
string LZ78Compressor::shortToString(unsigned short input)
{
	unsigned char r[2];
	r[0] = (unsigned char)input & 0xff; //zabierz tylnią część (AND z 256)
	//(w AND musimy mieć jedynki na obu miejscach, żeby dokonać kopii. 0xff -> 256 a więc 1111 1111, wykonując AND wszystkie jedynki z input przenoszą się do wyniku.
	r[1] = (unsigned char)(input >> 8) & 0xff; //przesuń 8 bitów w prawo, i znowu zabierz tylnią część (AND z 256)
	return string(1, r[0]) + string(1, r[1]); //zwróć wartość
}

/// <summary>
/// Zamienia dwuznakowy string na unsigned short, wszystkie pozostałe znaki nie wpłyną na wynik (liczą się tylko dwa pierwsze)
/// </summary>
/// <param name="input">string który ma zostać przekonwertowany</param>
/// <returns>unsigned short utworzony z dwóch pierwszych liter ciągu</returns>
unsigned short LZ78Compressor::stringToShort(string input)
{
	//wyjaśnienie: przesuń 8 bitów z input 1 w prawo, wtedy dostajemy 16 bitową wartość, dodajemy pozostałe 8 bitów z input[0] używając OR
	//w OR jedynki zawsze się przenoszą.
	return (unsigned short)(((unsigned char)input[1] << 8) | 
		(unsigned char)input[0]); 
}