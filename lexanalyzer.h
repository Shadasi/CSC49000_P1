#include <iostream>
#include <fstream>
#include <iomanip>

#ifndef LEXANALYZER_H
#define LEXANALYZER_H


class lexanalyzer
{
public:
    lexanalyzer(char*[]);
    void charReader();
    void checkKeywords(std::string);
    void printToken(std::string, std::string);
private:
    char current;
    std::string token;
    std::ifstream input;
    std::ofstream output;
};

#endif // LEXANALYZER_H
