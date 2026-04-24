#ifndef RESULT_H
#define RESULT_H

#include <string>

using namespace std;

struct Result {
    string path;
    int visited = 0;
    int processed = 0;
    int maxDepth = 0;
    double timeMs = 0.0;
};

#endif