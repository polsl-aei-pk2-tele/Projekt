#pragma once
#include "ICompressor.h"
class LZ78Compressor : ICompressor
{

public:
	// Inherited via ICompressor
	virtual std::string compress(std::string input) override;
	virtual std::string decompress(std::string output) override;
};
