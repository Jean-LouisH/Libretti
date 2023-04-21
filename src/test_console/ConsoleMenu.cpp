#include "ConsoleMenu.hpp"
#include <iostream>
#include <vector>

void menu(std::string* fileName)
{
	system("cls");
	std::cout << "\n\t\t\tLibretti Console Test\n\n";
#ifdef _DEBUG
	std::vector<std::string> demos;
	std::string directoryPath = "../../../../../demos/";

	demos.push_back(directoryPath + "Mary Had a Little Lamb.txt");
	demos.push_back(directoryPath + "Starman Theme.txt");

	demos.push_back(directoryPath + "tests/C Major Scale.txt");
	demos.push_back(directoryPath + "tests/C Minor Scale.txt");
	demos.push_back(directoryPath + "tests/D Major Scale.txt");
	demos.push_back(directoryPath + "tests/Accidentals Test.txt");
	demos.push_back(directoryPath + "tests/Crescendo Test.txt");
	demos.push_back(directoryPath + "tests/Diminuendo Test.txt");
	demos.push_back(directoryPath + "tests/Dotted Note Test.txt");
	demos.push_back(directoryPath + "tests/Dynamic Accent Test.txt");
	demos.push_back(directoryPath + "tests/Dynamics Test.txt");
	demos.push_back(directoryPath + "tests/Multichannel Test.txt");
	demos.push_back(directoryPath + "tests/Octave Test.txt");
	demos.push_back(directoryPath + "tests/Panning Test.txt");
	demos.push_back(directoryPath + "tests/Slur Test.txt");
	demos.push_back(directoryPath + "tests/Staccato Test.txt");
	demos.push_back(directoryPath + "tests/Timbre Test.txt");
	demos.push_back(directoryPath + "tests/Trill Test.txt");
	demos.push_back(directoryPath + "tests/Varying Tempo Test.txt");

	std::cout << "Demos\n----\n";
	for (int i = 0; i < demos.size(); i++)
		std::cout << i + 1 << ". " << demos.at(i) << "\n";
	std::cout << "\nEnter demo number, or filepath to play -> ";

	std::getline(std::cin, *fileName);

	if (atoi(fileName->c_str()) >= 1 && atoi(fileName->c_str()) <= demos.size())
	{
		*fileName = demos[atoi(fileName->c_str()) - 1];
	}
#else
	std::cout << "Enter filepath to play -> ";
	std::getline(std::cin, *fileName);
#endif
}