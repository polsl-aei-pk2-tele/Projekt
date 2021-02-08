// compress.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Params.h"
#include "LZ78Compressor.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc == 1) //jeśli użytkownik nie podał żadnych parametrów -> wyjdź
		return 1;

	try
	{
		Params p = Params(argc, argv); //Parse parametrów 
		//Odczyt z pliku 
		std::ifstream fileStream(p.inputPath);
		std::stringstream buff;
		buff << fileStream.rdbuf();
		string data = buff.str();


		ICompressor* cmp = new LZ78Compressor();
		string d = "";

		if (p.mode == 'C')
			d = cmp->compress(data);

		if (p.mode == 'R')
			d = cmp->decompress(data);

		//zapis do pliku
		ofstream outputStream;
		outputStream.open(p.outputPath);
		outputStream << d;
	}
	catch (string e)
	{
		cout << e;
	}
}
