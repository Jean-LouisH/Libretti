#include "console_menu.hpp"
#include <iostream>
#include <vector>
#include <libretti.h>

void menu(std::string* file_name)
{
	std::cout << "\n\t\t\t_libretti Demos\n\n";

	std::vector<std::string> demos;
	std::string directory_path;
#ifdef _DEBUG
	directory_path = LIBRETTI_DEMOS_DIRECTORY;
#else 
	directory_path = "data/";
#endif

	demos.push_back(directory_path + "Mary Had a Little Lamb.txt");
	demos.push_back(directory_path + "Starman Theme.txt");

	demos.push_back(directory_path + "tests/Accidentals Test.txt");
	demos.push_back(directory_path + "tests/Crescendo Test.txt");
	demos.push_back(directory_path + "tests/Diminuendo Test.txt");
	demos.push_back(directory_path + "tests/Dotted Note Test.txt");
	demos.push_back(directory_path + "tests/Dynamic Accent Test.txt");
	demos.push_back(directory_path + "tests/Dynamics Test.txt");
	demos.push_back(directory_path + "tests/Multichannel Test.txt");
	demos.push_back(directory_path + "tests/Octave Test.txt");
	demos.push_back(directory_path + "tests/Panning Test.txt");
	demos.push_back(directory_path + "tests/Sample Timbre Test.txt");
	demos.push_back(directory_path + "tests/Slur Test.txt");
	demos.push_back(directory_path + "tests/Staccato Test.txt");
	demos.push_back(directory_path + "tests/Timbre Test.txt");
	demos.push_back(directory_path + "tests/Trill Test.txt");
	demos.push_back(directory_path + "tests/Varying Tempo Test.txt");

	demos.push_back(directory_path + "scales/A Major Scale.txt");
	demos.push_back(directory_path + "scales/A Minor Scale.txt");
	demos.push_back(directory_path + "scales/Ab Major Scale.txt");
	demos.push_back(directory_path + "scales/B Major Scale.txt");
	demos.push_back(directory_path + "scales/B Minor Scale.txt");
	demos.push_back(directory_path + "scales/Bb Major Scale.txt");
	demos.push_back(directory_path + "scales/Bb Minor Scale.txt");
	demos.push_back(directory_path + "scales/C Major Scale.txt");
	demos.push_back(directory_path + "scales/C Minor Scale.txt");
	demos.push_back(directory_path + "scales/C# Major Scale.txt");
	demos.push_back(directory_path + "scales/C# Minor Scale.txt");
	demos.push_back(directory_path + "scales/Cb Major Scale.txt");
	demos.push_back(directory_path + "scales/D Major Scale.txt");
	demos.push_back(directory_path + "scales/D Minor Scale.txt");
	demos.push_back(directory_path + "scales/D# Minor Scale.txt");
	demos.push_back(directory_path + "scales/Db Major Scale.txt");
	demos.push_back(directory_path + "scales/E Major Scale.txt");
	demos.push_back(directory_path + "scales/E Minor Scale.txt");
	demos.push_back(directory_path + "scales/Eb Major Scale.txt");
	demos.push_back(directory_path + "scales/Eb Minor Scale.txt");
	demos.push_back(directory_path + "scales/F Major Scale.txt");
	demos.push_back(directory_path + "scales/F Minor Scale.txt");
	demos.push_back(directory_path + "scales/F# Major Scale.txt");
	demos.push_back(directory_path + "scales/F# Minor Scale.txt");
	demos.push_back(directory_path + "scales/G Major Scale.txt");
	demos.push_back(directory_path + "scales/G Minor Scale.txt");
	demos.push_back(directory_path + "scales/G# Minor Scale.txt");
	demos.push_back(directory_path + "scales/Gb Major Scale.txt");

	std::cout << "Demos\n----\n";
	for (int i = 0; i < demos.size(); i++)
		std::cout << i + 1 << ". " << demos.at(i) << "\n";
	std::cout << "\nEnter demo number, or filepath to play -> ";

	std::getline(std::cin, *file_name);

	if (atoi(file_name->c_str()) >= 1 && atoi(file_name->c_str()) <= demos.size())
	{
		*file_name = demos[atoi(file_name->c_str()) - 1];
	}

	printf("\nOn the window, press 'ESC' to quit, 'p' to pause or play, 's' to stop, 'r' to reset, 'l' to load another demo.\n");
}