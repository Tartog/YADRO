#include <iostream>
#include <fstream>
#include <string>
#include "Computer_Club.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Incorrect input !" << endl;
		return 0;
	}

	string file_name = argv[1];

	Computer_Club test;
	test.take_configuration(file_name);

	test.computer_club_work();

	return 0;
}
