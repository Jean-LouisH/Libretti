#include "ConsoleMenu.hpp"
#include <iostream>

void menu(std::string* fileName)
{
	system("cls");
	std::cout << "\n\t\t\tLibretti Console Test\n\n";
#ifdef _DEBUG
	std::string demos[] = {
		{ "../Demos/Also sprach zarathustra.txt" },
	{ "../Demos/Mary had a little lamb.txt" },
	{ "../Demos/Flight of the bumblebee.txt" },
	{ "../Demos/Less talk more rokk.txt" },
	{ "../Demos/Single channel test.txt" },
	{ "../Demos/Multichannel test.txt" }
	};
	std::cout << "Demos\n----\n1. Also sprach zarathustra\n";
	std::cout << "2. Mary had a little lamb\n";
	std::cout << "3. Flight of the bumblebee\n";
	std::cout << "4. Less talk more rokk\n";
	std::cout << "5. Single channel test\n";
	std::cout << "6. Multichannel test\n\n";
	std::cout << "Enter demo number, or filepath to play -> ";

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
	else if (*fileName == "5")
	{
		*fileName = demos[4];
	}
#else
	std::cout << "Enter filepath to play -> ";
	std::getline(std::cin, *fileName);
#endif
}