#include "io.h"

#include <filesystem>
#include <fstream>
#include <iomanip>

namespace fs = std::filesystem;

bool readBoardFromFile(const std::string& fileName, std::vector<int>& board, int& rows, int& cols) {
    std::ifstream in(fileName);

    if (!in.is_open()) {
        return false;
    }

    in >> rows >> cols;

    if (!in || rows <= 0 || cols <= 0) {
        return false;
    }

    board.clear();
    board.resize(rows * cols);

    for (int i = 0; i < rows * cols; ++i) {
        in >> board[i];
        if (!in) {
            return false;
        }
    }

    return true;
}

void saveSolutionToFile(const std::string& fileName, const Result& result) {
    fs::path outputPath(fileName);
    if (outputPath.has_parent_path()) {
        fs::create_directories(outputPath.parent_path());
    }

    std::ofstream out(fileName);

    if (!out.is_open()) {
        return;
    }

    if (result.path == "NOTHING") {
        out << -1 << "\n";
    }
    else {
        out << result.path.size() << "\n";
        out << result.path << "\n";
    }
}

void saveStatsToFile(const std::string& fileName, const Result& result) {
    fs::path outputPath(fileName);
    if (outputPath.has_parent_path()) {
        fs::create_directories(outputPath.parent_path());
    }

    std::ofstream out(fileName);

    if (!out.is_open()) {
        return;
    }

    if (result.path == "NOTHING") {
        out << -1 << "\n";
    }
    else {
        out << result.path.size() << "\n";
    }

    out << result.visited << "\n";
    out << result.processed << "\n";
    out << result.maxDepth << "\n";
    out << std::fixed << std::setprecision(3) << result.timeMs << "\n";
}