#include "Params.h"
#include <string>
#include <iostream>




Params::Params(int argc, char* argv[])
{
	std::string switches[4] = { "-i","-o","-r","-c" };
	int i = 1;
	while (i < argc)
	{
		for (int j = 0; j < 4; j++)
		{
			if (switches[j].compare(argv[i]) == 0)
			{
				//switch found
				switch (j)
				{
				case 0:  //input flag
					//get next token
					i++;
					inputPath = argv[i];
					break;
				case 1: //output flag
					//get next token
					i++;
					outputPath = argv[i];
					break;
				case 2:
					mode = 'R';
					break;
				case 3:
					mode = 'C';
					break;
				default:
					throw "Unexpected switch/undefined statement";
				}
			}
		}
		i++;
	}
}