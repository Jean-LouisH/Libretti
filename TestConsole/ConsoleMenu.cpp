#include "ConsoleMenu.hpp"
#include <iostream>

void menu(std::string* fileName)
{
	system("cls");
	std::cout << "\n\t\t\tLibretti Console Test\n\n";
#ifdef _DEBUG
	std::string demos[] = {
		{ "../Demos/Mary had a little lamb (feature test).txt" },
	{ "../Demos/Mary had a little lamb.txt" },
	{ "../Demos/Multichannel test.txt" },
	{ "../Demos/Single channel test.txt" },
	};
	std::cout << "Demos\n----\n1. Mary had a little lamb (feature test)\n";
	std::cout << "2. Mary had a little lamb\n";
	std::cout << "3. Multichannel test\n";
	std::cout << "4. Single channel test\n";
	std::cout << "\nEnter demo number, or filepath to play -> ";

	std::getline(std::cin, *fileName);

	if (*fileName == "1")
	{
		*fileName = demos[0];
	}
	else if (*fileName == "2")
	{
		*fileName = demos[1];
	}
	else if (*fileName == "3")
	{
		*fileName = demos[2];
	}
	else if (*fileName == "4")
	{
		*fileName = demos[3];
	}
#else
	std::cout << "Enter filepath to play -> ";
	std::getline(std::cin, *fileName);
#endif
}