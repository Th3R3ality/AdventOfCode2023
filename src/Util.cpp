#include "Pch.h"
#include "Puzzles.h"

#define LINE_MAX_LENGTH 256

std::vector<std::string> LoadInput(std::string inputPath) {
	std::vector<std::string> input;

	auto inputFile = std::ifstream(inputPath);

	if (inputFile.fail()) {
		return {};
	}

	char line[LINE_MAX_LENGTH];
	while (!inputFile.eof()) {
		memset(line, 0, LINE_MAX_LENGTH);
		inputFile.getline(line, LINE_MAX_LENGTH);
		input.push_back(line);
	}

	return input;
}

bool IsNum(char c) {
	return (c >= '0' && c <= '9');
}