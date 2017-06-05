//============================================================================
// Name        : Eternity.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

#include "core/Puzzle.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Specify file to solve" << std::endl;
		exit(0);
	}
	std::string filename = argv[1];
	std::cout << "Loading: " << filename << std::endl;
	Puzzle puzzle(filename);
	
	std::cout << "Solving... ";
	puzzle.solve();
	std::cout << " [SOLVED]" << std::endl;
	
	std::cout << "Writing solution." << std::endl;
	puzzle.write();
	
	std::cout << "Bye" << std::endl;
}
