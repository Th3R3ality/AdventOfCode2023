#include "Pch.h"

#include "Puzzles.h"

constexpr int LINE_MAX_LENGTH = 256;

int part1(std::vector<std::string> input);
int part2(std::vector<std::string> input);
bool checkForSymbols(std::vector<std::string> input, std::string symbols, int x, int y);
void createSymbolString(std::vector<std::string>input, std::string& symbolString);
bool isSymbol(char c, std::string symbols);
bool isNum(char c);
int getGearRatio(std::vector<std::string> input, int x, int y);
void getNextNumberPos(std::vector<std::string> input, int x, int y, int& index);
int getFullNumber(std::vector<std::string> input, int x, int y, int pos);
bool eol(std::string line, int idx);

void Day3() {
	std::cout << "DAY 3 v_v" << std::endl;

	std::string symbols;
	std::vector<std::string> input;

	auto inputFile = std::ifstream("src\\input\\Day3.txt");
	char line[LINE_MAX_LENGTH];

	while (!inputFile.eof()) {
		memset(line, 0, LINE_MAX_LENGTH);
		inputFile.getline(line, LINE_MAX_LENGTH);
		//std::cout << line << std::endl;
		input.push_back(line);
	}
	

	int answer1 = part1(input);
	int answer2 = part2(input);

	std::cout << "Answer for part 1: " << answer1 << std::endl;
	std::cout << "Answer for part 2: " << answer2 << std::endl;
}

int part1(std::vector<std::string> input) {

	std::string symbols;
	createSymbolString(input, symbols);

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

int part2(std::vector<std::string> input) {

	int answer = 0;
	for (int y = 0; y < input.size(); y++) {
		bool isPart = false;
		int currentNum = 0;

		std::cout << std::endl;
		if (y != 0)
			std::cout << input[y - 1] << std::endl;
		std::cout << input[y] << " <- " << std::endl;
		if (y != input.size() - 1)
			std::cout << input[y + 1] << std::endl;

		for (int x = 0; x < input[y].length(); x++) {
			char c = input[y][x];
			
			if (c == '*') {
				std::cout << "[+] Found gear: " << x << "," << y << std::endl;
				answer += getGearRatio(input, x, y);
			}
		}
	}

	return answer;
}

bool checkForSymbols(std::vector<std::string> input, std::string symbols, int x, int y) {
	int xBegin = (x - 1 < 0 ? 1 : 0);
	int yBegin = (y - 1 < 0 ? 1 : 0);
	int yEnd = (y + 1 > input.size()-1 ? 1 : 0);
	
	bool hasSymbol = false;

	for (int yOffset = -1 + yBegin; yOffset <= 1 - yEnd; yOffset++) {
		for (int xOffset = -1 + xBegin; xOffset <= 1; xOffset++) {
			char c = input[y + yOffset][x + xOffset];
			if (isSymbol(c, symbols)) {
				hasSymbol = true;
			}
		}
	}
	if (hasSymbol)
		return true;

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
			if (c != '.' && !isNum(c)) {
				symbolString.push_back(c);
			}
		}
	}
}

bool isNum(char c) {
	return (c >= '0' && c <= '9');
}

int getGearRatio(std::vector<std::string> input, int x, int y) {
	std::string symbols = "0123456789";
	if (!checkForSymbols(input, symbols, x, y)) {
		std::cout << "[-] Skipping, ratios found\n";
		return 0;
	}
	int index = 0, totalRatio = 1, ratioCount = 0;
	while (index < 9) {
		getNextNumberPos(input, x, y, index);
		if (index < 9) {
			if (index == -1) {
				index = 9;
			}
			std::cout << "[*] Found gear ratio at offset: " << (int)((float)(index - 1) / 3) - 1 << "," << ((index-1) % 3) - 1 << std::endl;
			ratioCount++;
			int ratio = getFullNumber(input, x, y, index - 1);
			std::cout << "[#] Gear ratio: " << ratio << std::endl;
			totalRatio = totalRatio * ratio;
		}
	}
	if (ratioCount == 2) {
		std::cout << "[#*#] Total gear ratio: " << totalRatio << std::endl;
		return totalRatio;
	}
	std::cout << "[!*] Incorrect number of ratios: " << ratioCount << std::endl;
	return 0;
}

void getNextNumberPos(std::vector<std::string> input, int x, int y, int& index) {
	bool yBegin = (y - 1 < 0);
	if (yBegin && (int)((float)index / 3) == 0) {
		index += 3;
	}
	bool foundNum = false;
	while (index < 9) {
		bool xBegin = (x - 1 < 0);
		if (xBegin && (index % 3 == 0)) {
			index += 1;
		}

		bool yEnd = (y + 1 > input.size() - 1);
		if (yEnd && y + (int)((float)index / 3) - 1 > input.size() - 1) {
			index = 9;
			return;
		}

		char c = input[y + (int)((float)index / 3) - 1][x + (index % 3) - 1];

		if (isNum(c)) {
			foundNum = true;
		}
		if (foundNum && (!isNum(c))) {
			return;
		}
		index++;
		if (foundNum && (index % 3 == 0)) {
			if (index == 9)
				index = -1;
			return;
		}
	}
	return;
}

int getFullNumber(std::vector<std::string> input, int x, int y, int pos) {
	x = x + ((pos % 3) - 1);
	y = y + ((int)((float)pos / 3) - 1);

	int fullNumber = 0;

	while (x >= 0 && isNum(input[y][x])) {
		x--;
	}
	x++;
	
	while (!eol(input[y], x) && isNum(input[y][x])) {
		fullNumber = (fullNumber * 10) + (input[y][x] - '0');
		x++;
	}

	return fullNumber;
}

bool eol(std::string line, int idx) {
	return (idx > line.size() - 1);
}