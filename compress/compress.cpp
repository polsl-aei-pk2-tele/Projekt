// compress.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Params.h"
#include "LZ78Compressor.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc == 1)
		return 1;


	Params p = Params(argc, argv);
	std::cout << p.inputPath << p.outputPath << p.mode << std::endl;


	LZ78Compressor cmp = LZ78Compressor();

	std::ifstream fileStream(p.inputPath);
	std::stringstream buff;
	buff << fileStream.rdbuf();
	string data = buff.str();
	cout << data << endl;
	string comp = cmp.compress(data);

	cout << comp << endl;

	string decomp = cmp.decompress(comp);
	cout << decomp << endl;


}