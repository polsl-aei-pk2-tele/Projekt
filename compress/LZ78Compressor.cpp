#include "LZ78Compressor.h"
#include <map>
#include <iostream>
using namespace std;


/// <summary>
/// Dokonuje kompresji, używając algorytmu LZ78
/// Uwaga:
/// - Maksymalny rozmiar słownika to 4,294,967,295, gdy zostanie przekroczony, wyrzucony zostanie wyjątek
/// </summary>
/// <param name="input">Ciąg znaków, który ma zostać zakodowany</param>
/// <returns>Zakodowany ciąg znaków</returns>
string LZ78Compressor::compress(string input)
{
	map<string, unsigned int> dictionary; //Słownik mapujący ciągi 
	string result = ""; //output
	string c;
	unsigned int n = 1; // 4,294,967,295 możliwych wartości w słowniku

	if (input.empty())
		return "";

	for (unsigned int i = 0; i <= input.length(); i++)
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
				result.append(intToString(0) + s);
				dictionary.insert(pair<string, unsigned int>(s, n));
			}
			else
			{	//c jest w słowniku, dodajemy c + s 
				result.append(intToString(dictionary[c]) + s);
				dictionary.insert(pair<string, unsigned int>(c + s, n));
			}

			if (n >= 4294967295) //Wyjątek kiedy przekraczamy maksymalną wielkość słownika
				throw std::out_of_range("Exceeded maximum dictionary size");

			n++;
			c.clear();
		}
	}
	return result;
}

/// <summary>
/// Dokonuje dekompresji algorytmem LZ78
/// Uwaga:
/// - Maksymalny rozmiar słownika to 4,294,967,295, gdy zostanie przekroczony, wyrzucony zostanie wyjątek
/// - Zakłada, że długość kodu jest równa 5
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
string LZ78Compressor::decompress(string input)
{
	map<unsigned int, string> dictionary; //Słownik mapujący ciągi 
	string result = ""; //output
	unsigned int n = 1;
	if (input.empty())
		return "";

	for (unsigned int i = 0; i < input.length(); i += 5) //wiemy, że nasz program koduje po 5 bajtów (4 z klucza, 1 z symbolu)
	{
		if (i + 3 >= input.length())
			break;

		unsigned int k = stringToInt(string(1, input[i]) + string(1, input[i + 1]) + string(1, input[i + 2]) + string(1, input[i + 3]));
		string s = string(1, input[i + 4]);

		if (k == 0)
		{
			result.append(s);
			dictionary.insert(pair<unsigned int, string>(n, s));
			n++;
		}
		else
		{
			result.append(dictionary[k] + s);
			dictionary.insert(pair<unsigned int, string>(n, dictionary[k] + s));
			n++;
		}
	}

	return result.substr(0, result.size() - 1);;
}

/// <summary>
/// Zamienia unsigned int na 4 bajty i przechowuje je jako string
/// </summary>
/// <param name="input">uint który zostanie zkonwertowany</param>
/// <returns>string o rozmiarze 4, każda litera jest jednym z bajtów int</returns>
string LZ78Compressor::intToString(unsigned int input)
{
	unsigned char r[4];
	r[0] = (unsigned char)input & 0xff; //zabierz tylnią część (AND z 256)
	//(w AND musimy mieć jedynki na obu miejscach, żeby dokonać kopii. 0xff -> 256 a więc 1111 1111, wykonując AND wszystkie jedynki z input przenoszą się do wyniku.
	r[1] = (unsigned char)(input >> 8) & 0xff; //przesuń 8 bitów w prawo, i znowu zabierz tylnią część (AND z 256)
	r[2] = (unsigned char)(input >> 16) & 0xff; //przesuń 8 bitów w prawo, i znowu zabierz tylnią część (AND z 256)
	r[3] = (unsigned char)(input >> 24) & 0xff; //przesuń 8 bitów w prawo, i znowu zabierz tylnią część (AND z 256)
	return string((char*)r, 4); //zwróć wartość
}

/// <summary>
/// Zamienia czteroznakowy string na unsigned int, wszystkie pozostałe znaki nie wpłyną na wynik (liczą się tylko cztery pierwsze)
/// </summary>
/// <param name="input">string który ma zostać przekonwertowany</param>
/// <returns>unsigned int utworzony z czterech pierwszych liter ciągu</returns>
unsigned int LZ78Compressor::stringToInt(string input)
{
	//wyjaśnienie: przesuń 24 bitów z input 1 w prawo, wtedy dostajemy 32 bitową wartość (w naszych komputerach teraz mamy wartości 64 bitowe, wiec nie musimy się bać o wyjście/przewinięcie poza komórkę), dodajemy pozostałe 8 bitów z input[0] używając OR
	//w OR jedynki zawsze się przenoszą.
	return (unsigned short)(((unsigned char)input[3] << 24) | ((unsigned char)input[2] << 16) | ((unsigned char)input[1] << 8) |
		(unsigned char)input[0]);
}