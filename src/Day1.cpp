#include "Pch.h"
#include "Puzzles.h"


void Day1()
{
    std::cout << "Day 1 :)\n";
    std::ifstream input("src\\input\\Day1.txt");
    if (input.fail()) {
        std::cout << "f's in the chat\n";
        return;
    }
    
    int answer1 = 0;
    int answer2 = 0;

    char c = 0;
    int a = 0, b = 0;
    
    while (input.get(c)) {
        if (c >= '0' && c <= '9') {
            if (!a) {
                a = c - '0';
            }
            b = c - '0';
        }

        if (c == '\n') {
            std::cout << " : " << a << b;
            answer1 += (a * 10) + b;
            a = 0; b = 0;
        }
        std::cout << c;
    }
    std::cout << " : " << a << b;
    answer1 += (a * 10) + b;


    a = 0; b = 0;
    constexpr const char* spellings[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    input.close();
    input = std::ifstream("src\\input\\Day1.txt");

    a = 0, b = 0;
    char line[64];
    memset(line, 0, 64);
    int num = 0;
    while (input.getline(line, 64)) {
        for (int idx = 0; idx < 64; idx++) {

            if (line[idx] >= '0' && line[idx] <= '9') {
                num = line[idx] - '0';
                //std::cout << "found int: " << line[idx] << " == " << num << "\n";
            }

            for (int i = 0; i < sizeof(spellings) / sizeof(char*); i++) {
                int jdx = 0;
                while (idx + jdx < 64) {
                    if (line[idx + jdx] == '0') break;

                    if (line[idx + jdx] != spellings[i][jdx]) {
                        break;
                    }
                    if (spellings[i][jdx + 1] == '\0') {
                        num = i + 1;
                        //std::cout << "found spelling: " << num << " == " << spellings[i] << "\n";
                        break;
                    }
                    jdx++;
                }
            }

            if (!a) {
                a = num;
            }
            b = num;
        }
        std::cout << line << " : " << a << b << '\n';
        answer2 += (a * 10) + b;
        a = 0; b = 0; num = 0;
        memset(line, 0, 64);
    }

    std::cout << "Part 1 answer: " << answer1 << std::endl;
    std::cout << "Part 2 answer: " << answer2 << std::endl;
}
