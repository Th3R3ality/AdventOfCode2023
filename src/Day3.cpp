#include "Pch.h"

#include "Puzzles.h"

constexpr int LINE_MAX_LENGTH = 256;

int part1(std::vector<std::string> input, std::string symbols);
bool checkForSymbols(std::vector<std::string> input, std::string symbols, int x, int y);
void createSymbolString(std::vector<std::string>input, std::string& symbolString);
bool isSymbol(char c, std::string symbols);


void Day3() {
	std::cout << "DAY 3 v_v" << std::endl;

	std::string symbols;
	std::vector<std::string> input;

	auto inputFile = std::ifstream("src\\input\\Day3.txt");
	char line[LINE_MAX_LENGTH];

	while (!inputFile.eof()) {
		memset(line, 0, LINE_MAX_LENGTH);
		inputFile.getline(line, LINE_MAX_LENGTH);
		std::cout << line << std::endl;
		input.push_back(line);
	}
	
	createSymbolString(input, symbols);

	int answer1 = part1(input, symbols);

	std::cout << "Answer for part 1: " << answer1 << std::endl;
}

int part1(std::vector<std::string> input, std::string symbols) {
	int answer = 0;

	for (int y = 0; y < input.size(); y++) {
		bool isPart = false;
		int currentNum = 0;

		if (y != 0)
			std::cout << input[y-1] << std::endl;
		std::cout << input[y] << std::endl;
		if (y != input.size()-1)
			std::cout << input[y+1] << std::endl;
		for (int x = 0; x < input[y].length(); x++) {
			if (input[y][x] == '.' || isSymbol(input[y][x], symbols)) {
				if (isPart) {
					answer += currentNum;
					std::cout << "Added: " << currentNum << std::endl;
				}
				isPart = false;
				currentNum = 0;
				continue;
			}

			if (input[y][x] >= '0' && input[y][x] <= '9') {
				currentNum = (currentNum * 10) + (input[y][x] - '0');
				if (!isPart && checkForSymbols(input, symbols, x, y)) {
					std::cout << "SYMBOL ON CHAR\n";
					isPart = true;
				}
			}
		}
		if (isPart) {
			answer += currentNum;
			std::cout << "Added: " << currentNum << std::endl;
		}
		isPart = false;
		currentNum = 0;
	}

	return answer;
}

bool checkForSymbols(std::vector<std::string> input, std::string symbols, int x, int y) {
	int xBegin = (x - 1 < 0 ? 1 : 0);
	int yBegin = (y - 1 < 0 ? 1 : 0);
	int yEnd = (y + 1 > input.size()-1 ? 1 : 0);
	
	for (int yOffset = -1 + yBegin; yOffset <= 1 - yEnd; yOffset++) {
		for (int xOffset = -1 + xBegin; xOffset <= 1; xOffset++) {
			char c = input[y + yOffset][x + xOffset];
			if (isSymbol(c, symbols)) {
				return true;
			}
		}
	}

	return false;
}

bool isSymbol(char c, std::string symbols) {
	for (int idx = 0; idx < symbols.length(); idx++) {
		if (c == symbols[idx]) {
			return true;
		}
	}
	return false;
}

void createSymbolString(std::vector<std::string> input, std::string& symbolString) {
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].length(); j++) {
			char c = input[i][j];
			if (c != '.' && !(c >= '0' && c <= '9')) {
				symbolString.push_back(c);
			}
		}
	}
}