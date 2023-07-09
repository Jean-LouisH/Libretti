#include "ConsoleMenu.hpp"
#include <iostream>
#include <vector>

void menu(std::string* fileName)
{
	std::cout << "\n\t\t\tLibretti Demos\n\n";

	std::vector<std::string> demos;
	std::string directoryPath;
#ifdef _DEBUG
	directoryPath = "../../../../../demos/data/";
#else 
	directoryPath = "data/";
#endif

	demos.push_back(directoryPath + "Mary Had a Little Lamb.txt");
	demos.push_back(directoryPath + "Starman Theme.txt");

	demos.push_back(directoryPath + "tests/Accidentals Test.txt");
	demos.push_back(directoryPath + "tests/Crescendo Test.txt");
	demos.push_back(directoryPath + "tests/Diminuendo Test.txt");
	demos.push_back(directoryPath + "tests/Dotted Note Test.txt");
	demos.push_back(directoryPath + "tests/Dynamic Accent Test.txt");
	demos.push_back(directoryPath + "tests/Dynamics Test.txt");
	demos.push_back(directoryPath + "tests/Multichannel Test.txt");
	demos.push_back(directoryPath + "tests/Octave Test.txt");
	demos.push_back(directoryPath + "tests/Panning Test.txt");
	demos.push_back(directoryPath + "tests/Sample Timbre Test.txt");
	demos.push_back(directoryPath + "tests/Slur Test.txt");
	demos.push_back(directoryPath + "tests/Staccato Test.txt");
	demos.push_back(directoryPath + "tests/Timbre Test.txt");
	demos.push_back(directoryPath + "tests/Trill Test.txt");
	demos.push_back(directoryPath + "tests/Varying Tempo Test.txt");

	demos.push_back(directoryPath + "scales/A Major Scale.txt");
	demos.push_back(directoryPath + "scales/A Minor Scale.txt");
	demos.push_back(directoryPath + "scales/Ab Major Scale.txt");
	demos.push_back(directoryPath + "scales/B Major Scale.txt");
	demos.push_back(directoryPath + "scales/B Minor Scale.txt");
	demos.push_back(directoryPath + "scales/Bb Major Scale.txt");
	demos.push_back(directoryPath + "scales/Bb Minor Scale.txt");
	demos.push_back(directoryPath + "scales/C Major Scale.txt");
	demos.push_back(directoryPath + "scales/C Minor Scale.txt");
	demos.push_back(directoryPath + "scales/C# Major Scale.txt");
	demos.push_back(directoryPath + "scales/C# Minor Scale.txt");
	demos.push_back(directoryPath + "scales/Cb Major Scale.txt");
	demos.push_back(directoryPath + "scales/D Major Scale.txt");
	demos.push_back(directoryPath + "scales/D Minor Scale.txt");
	demos.push_back(directoryPath + "scales/D# Minor Scale.txt");
	demos.push_back(directoryPath + "scales/Db Major Scale.txt");
	demos.push_back(directoryPath + "scales/E Major Scale.txt");
	demos.push_back(directoryPath + "scales/E Minor Scale.txt");
	demos.push_back(directoryPath + "scales/Eb Major Scale.txt");
	demos.push_back(directoryPath + "scales/Eb Minor Scale.txt");
	demos.push_back(directoryPath + "scales/F Major Scale.txt");
	demos.push_back(directoryPath + "scales/F Minor Scale.txt");
	demos.push_back(directoryPath + "scales/F# Major Scale.txt");
	demos.push_back(directoryPath + "scales/F# Minor Scale.txt");
	demos.push_back(directoryPath + "scales/G Major Scale.txt");
	demos.push_back(directoryPath + "scales/G Minor Scale.txt");
	demos.push_back(directoryPath + "scales/G# Minor Scale.txt");
	demos.push_back(directoryPath + "scales/Gb Major Scale.txt");

	std::cout << "Demos\n----\n";
	for (int i = 0; i < demos.size(); i++)
		std::cout << i + 1 << ". " << demos.at(i) << "\n";
	std::cout << "\nEnter demo number, or filepath to play -> ";

	std::getline(std::cin, *fileName);

	if (atoi(fileName->c_str()) >= 1 && atoi(fileName->c_str()) <= demos.size())
	{
		*fileName = demos[atoi(fileName->c_str()) - 1];
	}

	printf("\nOn the window, press 'ESC' to quit, 'p' to pause or play, 's' to stop, 'r' to reset, 'l' to load another demo.\n");
}