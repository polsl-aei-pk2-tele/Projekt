#pragma once
#include "ICompressor.h"
class LZ78Compressor : public ICompressor
{

private:
	std::string shortToString(unsigned short input);
	unsigned short stringToShort(std::string input);
public:
	// Inherited via ICompressor
	virtual std::string compress(std::string input) override;
	virtual std::string decompress(std::string input) override;

};
