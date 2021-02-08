#include "Params.h"
#include <string>
#include <iostream>
using namespace std;

/// <summary>
/// Tworzy nowy obiekt typu Params, konwertuje parametry wprowadzone do programu
/// </summary>
Params::Params(int argc, char* argv[])
{
	std::string switches[5] = { "-i","-o","-r","-c","-h" }; //Flagi akceptowane przez nas
	int i = 1;
	help = false;
	while (i < argc)
	{
		for (int j = 0; j < 5; j++)
		{
			if (switches[j].compare(argv[i]) == 0)
			{
				switch (j)
				{
				case 0: //-i input 
					i++;//Przejdź do następnego parametru
					if (i >= argc)
						throw std::out_of_range("Za malo parametrow");
					inputPath = argv[i];
					break;
				case 1: //-o output
					i++; //Przejdź do następnego parametru
					if (i >= argc)
						throw std::out_of_range("Za malo parametrow");
					outputPath = argv[i];
					break;
				case 2: //-r read mode
					mode = 'R';
					break;
				case 3: //-c compress mode
					mode = 'C';
					break;
				case 4:
					Params::printHelp();
					help = true;
					return;
				default:
					throw std::invalid_argument("Bledna flaga");
				}
			}
		}
		i++;
	}

	if (outputPath.empty())
		throw std::invalid_argument("Brak flagi badz parametru flagi -o");
	if (inputPath.empty())
		throw std::invalid_argument("Brak flagi badz parametru flagi -i");
}


void Params::printHelp()
{
	std::cout << "-h - drukuje ten panel pomocy\n-i [sciezka do pliku] - WYMAGANY - sciezka do pliku, ktory ma zostac odczytany\n-o [sciezka do pliku] - WYMAGANY - sciezka w ktorej zostanie zapisany rezultat kompresji/dekompresji\n-r - DOMYSLNY - przelacza aplikacje w tryb odczytu/dekompresji\n-c - przelacza aplikacje w tryb kompresji" << endl;
}