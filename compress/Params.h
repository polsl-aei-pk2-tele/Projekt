#pragma once
#include <string>
#include <vector>
/// <summary>
/// Klasa dekodująca parametry linii wiersza poleceń
/// </summary>
class Params
{
public:
	/// <summary>
	/// Ścieżka zapisu rezultatu
	/// </summary>
	std::string outputPath; 
	/// <summary>
	/// Ścieżka pliku do odczytu
	/// </summary>
	std::string inputPath;
	/// <summary>
	/// Tryb pracy programu
	/// Możliwe ustawienia
	/// R - READ - odczyt i dekompresja z pliku, znajdującego się na inputPath, rezultat zostanie zapisany do outputPath
	/// C - COMPRESS - kompresja danych z pliku znajdującego się na inputPath, rezultat zostanie zapisany do outputPath
	/// </summary>
	char mode = 'R';
	/// <summary>
	/// Tworzy instancję klasy Params i odczytuje parametry podane w linii polecenia
	/// </summary>
	/// <param name="argc"></param>
	/// <param name="argv"></param>
	Params(int argc, char* argv[]);
	/// <summary>
	/// Drukuje pomoc, do strumienia standardowego
	/// </summary>
	static void printHelp();
};