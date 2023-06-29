#include "IntegrationTests.hpp"
#include <Libretti.h>


void LibrettiTests::IntegrationTests::run()
{
	this->intializingAndFinalizing();
}

void LibrettiTests::IntegrationTests::intializingAndFinalizing()
{
	lb_initialize();
	lb_finalize();
}