#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>
#include "result.h"

using namespace std;

class algorithms {
    getSearchOrders();
    getSearchHeuristics();
    Result BFS(const vector<int>& startBoard, int rows, int cols, const string& order);
    Result DFS(const vector<int>& startBoard, int rows, int cols, const string& order, int maxDepth);
    Result aStar(const vector<int>& startBoard, int rows, int cols, bool heuristic);
};


#endif
