#include "Pch.h"
#include "Puzzles.h"

void part1(std::vector<std::string>  input);
void part2(std::vector<std::string>  input);

std::vector<int> GatherWinningNumbers(std::string line, int& index);
bool GetNextNumber(std::string line, int& index, int& num);
bool IsWinningNumber(std::vector<int> winningNumbers, int num);
int FindSymbol(std::string line, char symbol);

void Day4() {
	std::cout << "Day 4 :3\n";

	std::vector<std::string> input = LoadInput("src\\input\\Day4.txt");

	//part1(input);
	part2(input);
}

void part1(std::vector<std::string> input) {
	int answer = 0;

	for (auto& line : input) {
		std::cout << line << std::endl;

		int gameValue = 0;
		int skipGameId;
		int index = 0;
		GetNextNumber(line, index, skipGameId);

		std::cout << "GameId: " << skipGameId << std::endl;

		auto winningNumbers = GatherWinningNumbers(line, index);

		while (index < line.length()) {
			int num = 0;
			if (!GetNextNumber(line, index, num)) {
				continue;
			}
			if (IsWinningNumber(winningNumbers, num)) {
				if (gameValue == 0) {
					gameValue = 1;
				}
				else {
					gameValue = gameValue * 2;
				}
			}
		}

		answer += gameValue;
	}

	std::cout << "Part 1 answer: " << answer << std::endl;
}

void part2(std::vector<std::string>  input) {
	int answer = 0;

	std::vector<int> cardCounts;

	for (auto& line : input) {
		std::cout << line << std::endl;

		int gameValue = 0;
		int gameId;
		int index = 0;

		GetNextNumber(line, index, gameId);
		if (cardCounts.size() < gameId) {
			cardCounts.resize(gameId);
		}
		cardCounts[gameId-1] += 1;

		auto winningNumbers = GatherWinningNumbers(line, index);

		while (index < line.length()) {
			int num = 0;
			if (!GetNextNumber(line, index, num)) {
				continue;
			}
			if (IsWinningNumber(winningNumbers, num)) {
				gameValue++;
			}
		}
		if (cardCounts.size() < gameId+gameValue) {
			cardCounts.resize(gameId+gameValue);
		}
		for (int i = 1; i <= gameValue; i++) {
			cardCounts[i + gameId-1] += 1 * cardCounts[gameId-1];
		}
		answer += cardCounts[gameId-1];
	}

	std::cout << "Part 2 answer: " << answer << std::endl;
}

std::vector<int> GatherWinningNumbers(std::string line, int& index) {
	int oldIndex = 0;
	int num = 0;
	int separatorIndex = FindSymbol(line, '|') + 1;
	std::vector<int> winningNumbers = {};

	do {
		oldIndex = index;
		if (GetNextNumber(line, index, num)) {
			if (separatorIndex > index) {
				winningNumbers.push_back(num);
				//std::cout << "found winning number: " << num << std::endl;
			}
		}

	} while (separatorIndex > index);

	index = oldIndex;

	return winningNumbers;
}

bool GetNextNumber(std::string line, int& index, int& num) {
	bool foundNum = false;
	num = 0;
	while (index < line.length()) {
		char c = line[index];
		index++;
		if (IsNum(c)) {
			num = (num * 10) + (c - '0');
			foundNum = true;
		}
		if (foundNum && !IsNum(c)) {
			return foundNum;
		}
	}
	return foundNum;
}

bool IsWinningNumber(std::vector<int> winningNumbers, int num) {
	for (auto& n : winningNumbers) {
		if (num == n) {
			return true;
		}
	}
	return false;
}

int FindSymbol(std::string line, char symbol) {
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == symbol) {
			return i;
		}
	}
	return -1;
}
