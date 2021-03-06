﻿// compress.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
		if (p.help)
			return 0;


		//Odczyt z pliku 
		std::ifstream fileStream(p.inputPath, ios::binary);
		std::stringstream buff;
		buff << fileStream.rdbuf();
		string data = buff.str();


		ICompressor* cmp = new LZ78Compressor();
		string d = "";
		ofstream outputStream;

		if (p.mode == 'C') //compress mode
			d = cmp->compress(data);


		if (p.mode == 'R') //read mode
			d = cmp->decompress(data);



		outputStream.open(p.outputPath, std::ios::out | ios::binary );
		outputStream.write(d.c_str(), static_cast<std::streamsize>(sizeof(char)) * d.size());

	}
	catch (const std::exception& e)
	{
		cerr << endl << e.what() << endl;
	}

}
