#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>
#include "result.h"

using namespace std;

struct Node {
    vector<int> state;
    string path;
    int zeroPos;
    char lastMove;
};

static vector<string> getSearchOrders() {
    return {
        "RDUL",
        "RDLU",
        "DRUL",
        "DRLU",
        "LUDR",
        "LURD",
        "ULDR",
        "ULRD"
    };
}

static vector<string> getHeuristics() {
    return {
        "hamm",
        "manh"
    };
}

struct AStarNode {
    vector<int> state;
    string path;
    int zeroPos;
    char lastMove;
    int g;
    int h;
    int f;
};

struct CompareAStar {
    bool operator()(const AStarNode& a, const AStarNode& b) const;
};

class algorithms {
    int findZero(const vector<int>& startBoard);
    vector<int> makeGoalState(int rows, int cols);
    int heuristicValue(const vector<int>& board, const vector<int>& goal, int cols, const string& heuristic, const vector<int>& goal);
    int manhattam (const vector<int>& board,  int rows);
    Result BFS(const vector<int>& startBoard, int rows, int cols, const string& order);
    static bool DFSrec(vector<int>& startBoard, int rows, int cols,
                  const string& path,int zeroPos, int depth, int maxDepth,
                  const vector<int>& goal, Result& result, char move, const string& order);
    Result DFS(const vector<int>& startBoard, int rows, int cols, const string& order, int limit);
    Result aStar(const vector<int>& startBoard, int rows, int cols, const string& heuristic);
};


#endif
