#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include "result.h"

bool readBoardFromFile(const std::string& fileName, std::vector<int>& board, int& rows, int& cols);
void saveSolutionToFile(const std::string& fileName, const Result& result);
void saveStatsToFile(const std::string& fileName, const Result& result);

#endif