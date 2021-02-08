// compress.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Params.h"

int main(int argc, char* argv[]) {

	if (argc == 1)
		return 1;
	

	Params p = Params(argc, argv);
	std::cout << p.inputPath << p.outputPath << p.mode << std::endl;
}