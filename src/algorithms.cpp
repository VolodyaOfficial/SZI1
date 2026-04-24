#include <vector>
#include <string>
#include "algorithms.h"

using namespace std;

static set<vector<int>> pathVisitedDFS;
static set<vector<int>> allVisitedDFS;

vector<int> makeGoalState(int rows, int cols) {
  vector<int> goal;
  for (int i = 1; i < rows * cols; ++i) {
    goal.push_back(i);
  }

  goal.push_back(0);
  return goal;
}

int findZero(const vector<int>& startBoard, Node node){
  for (int i = 0; i < Board.size(); i++) {
    if (Board[i] == 0) {
      node.zeroPos = i;
    }
  }
  return node.zeroPos;
 }

static bool DFSrec(const vector<int>& Board, int rows, int cols,
              const string& path, int zeroPos=0, int depth=0,
              int maxDepth, const vector<int>& goal, Result& result,
              char lastMove, const string& order){

    result.maxDepth = max(result.maxDepth, depth);;
    result.processed++;

    auto startTime = chrono::high_resolution_clock::now();

  if (allVisitedDFS.find(board) == allVisitedDFS.end()) {
    allVisitedDFS.insert(board);
    result.visited++;
  }

    if (Board == goal){
      return true;
    }
    if (depth >= limit){
      return false;
    }

    pathVisitedDFS.insert(board);

    for (char move : order) {
      if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()) {
        if (move == 'L' && (node.zeroPos % cols) != 0 && lastMove != 'R') {
          swap(Board[node.zeroPos], Board[node.zeroPos-1]);
          if (DFSrec(Board, rows, cols, path, node.zeroPos, depth, maxDepth, goal, result, move)){
             return true;
          }
          path.pop_back();
        }
      swap(board[zeroPos], board[zeroPos - 1]);
      }

      if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()) {
        if (move == 'R' && (node.zeroPos % cols) != cols && lastMove != 'L' ) {
          swap(Board[node.zeroPos], Board[node.zeroPos+1]);
          if (DFSrec(Board, rows, cols, path, node.zeroPos, depth, maxDepth, goal, result, move)){
            return true;
          }
          path.pop_back();
        }
        swap(board[zeroPos], board[zeroPos + 1]);
      }

      if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()) {
        if (move == 'U' && node.zeroPos > (cols-1) && lastMove != 'D' ) {
          swap(Board[node.zeroPos], Board[node.zeroPos-cols]);
          if (DFSrec(Board, rows, cols, path, node.zeroPos, depth, maxDepth, goal, result, move)){
            return true;
          }
          path.pop_back();
        }
        swap(board[zeroPos], board[zeroPos - cols]);
      }

      if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()) {
        if (move == 'D' && zeroPos < (Board.size()-cols) && lastMove != 'U' ) {
          swap(Board[node.zeroPos], Board[node.zeroPos-1]);
          if (DFSrec(Board, rows, cols, path, node.zeroPos, depth, maxDepth, goal, result, move)){
            return true;
          }
          path.pop_back();
        }
        swap(board[zeroPos], board[zeroPos - 1]);
      }
    }

  pathVisitedDFS.erase(board);
  return false;
}

Result DFS(const vector<int>& startBoard, int rows, int cols, const string& order, int limit) {
  auto startTime = chrono::high_resolution_clock::now();

  Result result;
  vector<int> goal = makeGoalState(rows, cols);
  pathVisitedDFS.clear();
  allVisitedDFS.clear();

  vector<int> board = startBoard;
  string path = "";
  int zeroPos = findZero(startBoard);

  if (DFSrec(board,rows,cols,path,zeroPos,0,limit,goal,result,'N',order)) {
    result.path = path;
  }
  else {
    result.path = "NOTHING";
  }

  auto endTime = chrono::high_resolution_clock::now();
  result.timeMs = chrono::duration<double, std::milli>(endTime - startTime).count();

  return result;
}