#include "game.h"
#include <iostream>
#include <stdexcept>

using namespace std;

#include <stdio.h>


int main()
{
	Game app;

	try {
		app.run();
	} catch (const std::exception & error) {
		cerr << error.what() << '\n';
		return -1;
	}

	return 0;
}
