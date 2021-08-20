// ArgumentParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "argument_parser.hpp"

SE7::argument_parser arg_parser = {
	{ "-flag1", { SE7::argument() } },
	{ "-flag2", { SE7::argument(), SE7::argument() } },
	{ "-flag3", { SE7::argument(), SE7::argument(), SE7::argument() } },
};

int main(int argc, const char *argv[]) {
	const char *argv2[] = { 
		"-flag1", "arg1", 
		"-flag2", "arg1", "arg2", 
		"-flag3", "arg1", "arg2", "arg3"
	};

	int argc2 = sizeof(argv2) / sizeof(const char *);

	try {
		arg_parser.parse(argc2, argv2);

		for (std::pair<const std::string, std::vector<SE7::argument>> &p : arg_parser) {
			std::cout << p.first << "\n";

			for (SE7::argument &arg : p.second) {
				std::cout << "\t" << arg.get_value() << "\n";
			}
		}
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
