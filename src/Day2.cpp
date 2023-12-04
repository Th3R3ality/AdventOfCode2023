#include "Pch.h"

#include "Puzzles.h"

bool getNextCount(char* line, int& count, int& index);
bool getNextIdentifier(char* line, char& identifier, int& index);

int part1(char* input);
bool verifyRules1(int count, char id);

int part2(char* input);
bool verifyRules2(int count, char id);

constexpr int LINE_MAX_LENGTH = 256;

void Day2() {
	auto input = std::ifstream("src\\input\\Day2.txt");

	int answer1 = 0, answer2 = 0;

	char line[LINE_MAX_LENGTH];
	while (!input.eof()) {
		memset(line, 0, LINE_MAX_LENGTH);
		input.getline(line, LINE_MAX_LENGTH);
		std::cout << line << std::endl;

		answer1 += part1(line);
		answer2 += part2(line);
	}

	
	std::cout << "Part 1 Answer: " << answer1 << std::endl;
	std::cout << "Part 2 Answer: " << answer2 << std::endl;

}

int part1(char* line) {
	int gameId, index = 0;
	getNextCount(line, gameId, index);

	int count;
	char id;
	while (getNextCount(line, count, index)) {
		getNextIdentifier(line, id, index);

		if (verifyRules1(count, id) == false) {
			//std::cout << "[-] Game " << gameId << ": INVALID\n";
			return 0;
		}
	}
	//std::cout << "[+] Game " << gameId << ": VALID\n";

	return gameId;
}
bool verifyRules1(int count, char id) {
	switch (id) {
	case 'r':
		if (count > 12)
			return false;
		break;

	case 'g':
		if (count > 13)
			return false;
		break;

	case 'b':
		if (count > 14)
			return false;
		break;
	}

	return true;
}


int part2(char* line) {
	int gameId, index = 0;
	getNextCount(line, gameId, index);
	

	int rmax = 0, gmax = 0, bmax = 0;
	int count;
	char id;
	while (getNextCount(line, count, index)) {
		getNextIdentifier(line, id, index);

		switch (id) {
		case 'r':
			if (count > rmax)
				rmax = count;
			break;
		case 'g':
			if (count > gmax)
				gmax = count;
			break;
		case 'b':
			if (count > bmax)
				bmax = count;
			break;
		}
		
	}
	//std::cout << "[+] Game Power: " << rmax * gmax * bmax << std::endl;
	return rmax * gmax * bmax;
}
bool verifyRules2(int count, char id) {
	return true;
}



bool getNextCount(char* line, int& count, int& index) {
	while (line[index] < '0' || line[index] > '9') {
		if (line[index] == '\0') {
			return 0;
		}
		index++;
	}
	count = line[index] - '0';

	index++;
	while (line[index] >= '0' && line[index] <= '9') {
		count = (count * 10) + (line[index] - '0');
		index++;
	}
	return 1;
}

bool getNextIdentifier(char* line, char& identifier, int& index) {
	while (line[index] < 'a' || line[index] > 'z') {
		if (line[index] == '\0') {
			return 0;
		}
		index++;
	}
	

	identifier = line[index];
	return 1;
}