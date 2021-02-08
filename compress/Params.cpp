#include "Params.h"
#include <string>
#include <iostream>


/// <summary>
/// Tworzy nowy obiekt typu Params, konwertuje parametry wprowadzone do programu
/// </summary>
Params::Params(int argc, char* argv[])
{
	std::string switches[4] = { "-i","-o","-r","-c" }; //Flagi akceptowane przez nas
	int i = 1;
	while (i < argc)
	{
		for (int j = 0; j < 4; j++)
		{
			if (switches[j].compare(argv[i]) == 0)
			{
				switch (j)
				{
				case 0: //-i input 
					i++;//Przejdź do następnego parametru
					if (i >= argc)
						throw std::out_of_range("Za mało parametrów");
					inputPath = argv[i];
					break;
				case 1: //-o output
					i++; //Przejdź do następnego parametru
					if (i >= argc)
						throw std::out_of_range("Za mało parametrów");
					outputPath = argv[i];
					break;
				case 2: //-r read mode
					mode = 'R';
					break;
				case 3: //-c compress mode
					mode = 'C';
					break;
				default:
					throw std::invalid_argument("Błędna flaga");
				}
			}
		}
		i++;
	}

	if (outputPath.empty())
		throw std::invalid_argument("Brak flaga bądź parametru flagi -o");
	if (inputPath.empty())
		throw std::invalid_argument("Brak flaga bądź parametru flagi -i");
}

