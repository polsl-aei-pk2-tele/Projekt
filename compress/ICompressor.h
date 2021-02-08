#pragma once
#include <string>

/// <summary>
/// Interfejs dla kompresora
/// </summary>
class ICompressor
{
public:
	/// <summary>
	/// Przeprowadza kompresję na ciągu wejściowym "input"
	/// </summary>
	/// <param name="input">Ciąg wejściowy</param>
	/// <returns>Ciąg zkompresowany</returns>
	virtual std::string compress(std::string input) = 0;
	/// <summary>
	/// Przeprowadza dekompresję na ciągu wejściowym
	/// </summary>
	/// <param name="input">Ciąg wejściowy</param>
	/// <returns>Ciąg zdekompresowany</returns>
	virtual std::string decompress(std::string output) = 0;

	~ICompressor() {};
};