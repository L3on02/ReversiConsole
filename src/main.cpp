#include <iostream>
#include <string>
#include <cstdlib> // for rand(), srand(), ...
#include <ctime>

#include "Controller.h"
#include "Board.h"
#include <unistd.h>

int main()
{
	srand(time(0)); // since we will need a random generator later
	
	Controller controller;
	controller.start();

	return 0;
}