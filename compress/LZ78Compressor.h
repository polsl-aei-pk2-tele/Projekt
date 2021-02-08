#pragma once
#include "ICompressor.h"
class LZ78Compressor : public ICompressor
{

private:
	std::string intToString(unsigned int input);
	unsigned int stringToInt(std::string input);
public:
	// Inherited via ICompressor
	virtual std::string compress(std::string input) override;
	virtual std::string decompress(std::string input) override;

};
