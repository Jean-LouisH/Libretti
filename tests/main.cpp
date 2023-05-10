#include "UnitTests.hpp"
#include "SystemTests.hpp"
#include "IntegrationTests.hpp"

#undef main //undo SDLmain definition

int main(int argc, char* argv[])
{
	LibrettiTests::UnitTests unitTests;
	LibrettiTests::IntegrationTests integrationTests;
	LibrettiTests::SystemTests systemTests;

	unitTests.run();
	integrationTests.run();
	systemTests.run();
	return 0;
}