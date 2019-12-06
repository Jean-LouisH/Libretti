#include "ConsoleMenu.hpp"
#include <iostream>
#include <vector>

void menu(std::string* fileName)
{
	system("cls");
	std::cout << "\n\t\t\tLibretti Console Test\n\n";
#ifdef _DEBUG
	std::vector<std::string> demos;

	demos.push_back("../Demos/Mary Had a Little Lamb.txt");
	demos.push_back("../Demos/Starman Theme.txt");

	demos.push_back("../Demos/Tests/C Major Scale.txt");
	demos.push_back("../Demos/Tests/C Minor Scale.txt");
	demos.push_back("../Demos/Tests/D Major Scale.txt");
	demos.push_back("../Demos/Tests/Accidentals Test.txt");
	demos.push_back("../Demos/Tests/Crescendo Test.txt");
	demos.push_back("../Demos/Tests/Diminuendo Test.txt");
	demos.push_back("../Demos/Tests/Dotted Note Test.txt");
	demos.push_back("../Demos/Tests/Dynamic Accent Test.txt");
	demos.push_back("../Demos/Tests/Dynamics Test.txt");
	demos.push_back("../Demos/Tests/Multichannel Test.txt");
	demos.push_back("../Demos/Tests/Octave Test.txt");
	demos.push_back("../Demos/Tests/Panning Test.txt");
	demos.push_back("../Demos/Tests/Slur Test.txt");
	demos.push_back("../Demos/Tests/Staccato Test.txt");
	demos.push_back("../Demos/Tests/Timbre Test.txt");
	demos.push_back("../Demos/Tests/Trill Test.txt");
	demos.push_back("../Demos/Tests/Varying Tempo Test.txt");

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