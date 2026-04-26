#include <iostream>
#include <string>
#include <vector>
#include "io.h"
#include "algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 6) {
        cerr << "Uzycie: " << argv[0] << " <strategia> <parametr> <plik_wej> <plik_sol> <plik_stats>" << endl;
        return 1;
    }


    string strategy = argv[1];    // bfs, dfs, astr
    string parameter = argv[2];   // RDUL, LUDR, manh, hamm
    string inputFile = argv[3];
    string solFile = argv[4];
    string statsFile = argv[5];

    vector<int> board;
    int rows = 0, cols = 0;


    if (!readBoardFromFile(inputFile, board, rows, cols)) {
        cerr << "Błąd: Nie mozna odczytac pliku " << inputFile << endl;
        return 1;
    }

    algorithms solver;
    Result result;


    if (strategy == "bfs") {
        result = solver.BFS(board, rows, cols, parameter);
    } 
    else if (strategy == "dfs") {
        int maxDepth = 20; 
        result = solver.DFS(board, rows, cols, parameter, maxDepth);
    } 
    else if (strategy == "astr") {
        result = solver.aStar(board, rows, cols, parameter);
    } 
    else {
        cerr << "Błąd: Nieznana strategia '" << strategy << "'" << endl;
        return 1;
    }


    saveSolutionToFile(solFile, result);
    saveStatsToFile(statsFile, result);

    return 0;
}