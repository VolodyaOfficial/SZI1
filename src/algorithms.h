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

class algorithms {
    int findZero(const vector<int>& startBoard);
    vector<int> makeGoalState(int rows, int cols);
    getSearchOrders();
    getSearchHeuristics();
    Result BFS(const vector<int>& startBoard, int rows, int cols, const string& order);
    static bool DFSrec(const vector<int>& startBoard, int rows, int cols,
                  const string& path,int zeroPos, int depth, int maxDepth,
                  const vector<int>& goal, Result& result, char move, const string& order);

    Result DFS(const vector<int>& startBoard, int rows, int cols, const string& order, int limit);
    Result aStar(const vector<int>& startBoard, int rows, int cols, bool heuristic);
};


#endif
