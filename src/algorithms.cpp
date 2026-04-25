#include <vector>
#include <string>
#include "algorithms.h"

#include <queue>
#include <set>
#include <map>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

set<vector<int>> pathVisitedDFS;
 set<vector<int>> allVisitedDFS;

vector<int> algorithms::makeGoalState(int rows, int cols) {
  vector<int> goal;
  for (int i = 1; i < rows * cols; ++i) {
    goal.push_back(i);
  }

  goal.push_back(0);
  return goal;
}

int algorithms::findZero(const vector<int>& startBoard){
  for (int i = 0; i < startBoard.size(); ++i) {
    if (startBoard[i] == 0) {
      return i;
    }
  }
  return -1;
 }

int algorithms::manhattan(const vector<int>& board, int cols) {
  int dist = 0;

  for (int i = 0; i < board.size(); ++i) {
    if (board[i] != 0) {
      int value = board[i];
      int row = i / cols;
      int col = i % cols;

      int goalRow = (value - 1) / cols;
      int goalCol = (value - 1) % cols;

      dist += fabs(row - goalRow) + fabs(col - goalCol);
    }
  }
  return dist;
}
int algorithms::hamming(const std::vector<int>& board, const std::vector<int>& goal) {
  int count = 0;

  for (int i = 0; i < board.size(); ++i) {
    if (board[i] != 0 && board[i] != goal[i]) {
      ++count;
    }
  }

  return count;
}


int algorithms::heuristicValue(const vector<int>& board, const vector<int>& goal, int cols, const string& heuristic) {
   if (heuristic == "hamm") {
     return hamming(board, goal);
   }

  if (heuristic == "manh") {
    return manhattan(board, cols);
  }

  return 0;
}


bool CompareAStar::operator()(const AStarNode& a, const AStarNode& b) const {
  if (a.f == b.f) {
    return a.h > b.h;
  }
  return a.f > b.f;
}

bool algorithms::DFSrec(vector<int>& Board, int rows, int cols,
              string& path, int zeroPos, int depth,
              int maxDepth, const vector<int>& goal, Result& result,
              char lastMove, const string& order){

    result.maxDepth = max(result.maxDepth, depth);
    result.processed++;

  if (allVisitedDFS.find(Board) == allVisitedDFS.end()) {
    allVisitedDFS.insert(Board);
    result.visited++;
  }

    if (Board == goal){
      return true;
    }
    if (depth >= maxDepth){
      return false;
    }

    pathVisitedDFS.insert(Board);

    for (char move : order) {

        if (move == 'L' && ((zeroPos % cols) != 0) && (lastMove != 'R')) {
          swap(Board[zeroPos], Board[zeroPos-1]);
          if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()){
            path+=move;
            if (DFSrec(Board, rows, cols, path, zeroPos - 1, depth + 1, maxDepth, goal, result, move, order)){
              return true;
            }
            path.pop_back();
        }
      swap(Board[zeroPos], Board[zeroPos - 1]);
      }

        if (move == 'R' && ((zeroPos % cols) != cols - 1) && (lastMove != 'L') ) {
          swap(Board[zeroPos], Board[zeroPos+1]);
          if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()){
            path+=move;
          if (DFSrec(Board, rows, cols, path, zeroPos + 1, depth + 1, maxDepth, goal, result, move, order)){
            return true;
          }
          path.pop_back();
        }
        swap(Board[zeroPos], Board[zeroPos + 1]);
      }

        if (move == 'U' && (zeroPos > (cols-1)) && (lastMove != 'D') ) {
          swap(Board[zeroPos], Board[zeroPos-cols]);
          if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()){
            path+=move;
          if (DFSrec(Board, rows, cols, path, zeroPos - cols, depth + 1, maxDepth, goal, result, move, order)){
            return true;
          }
          path.pop_back();
        }
        swap(Board[zeroPos], Board[zeroPos - cols]);
      }

        if (move == 'D' && (zeroPos < (Board.size()-cols)) && (lastMove != 'U') ) {
          swap(Board[zeroPos], Board[zeroPos + cols]);
          if (pathVisitedDFS.find(Board) == pathVisitedDFS.end()){
            path+=move;
          if (DFSrec(Board, rows, cols, path, zeroPos + cols, depth + 1, maxDepth, goal, result, move, order)){
            return true;
          }
          path.pop_back();
        }
        swap(Board[zeroPos], Board[zeroPos + cols]);
      }
    }

  pathVisitedDFS.erase(Board);
  return false;
}


Result algorithms::DFS(const vector<int>& startBoard, int rows, int cols, const string& order, int limit) {
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
  result.timeMs = chrono::duration<double, milli>(endTime - startTime).count();

  return result;
}

Result algorithms::aStar(const vector<int>& startBoard, int rows, int cols, const string& heuristic){
  auto startTime = chrono::high_resolution_clock::now();

  Result result;
  vector<int> goal = makeGoalState(rows, cols);
  string order = "LRUD";
  map<vector<int>, int> bestG;
  priority_queue<AStarNode, vector<AStarNode>, CompareAStar> pq;

  AStarNode star;
  star.state = startBoard;
  star.path = "";
  star.zeroPos = findZero(star.state);
  star.lastMove = 'N';
  star.g=0;
  star.h=heuristicValue(startBoard, goal, cols, heuristic);
  star.f=star.g + star.h;

  pq.push(star);
  bestG[star.state] = 0;
  result.visited = 1;

  while (!pq.empty()) {
    AStarNode cur = pq.top();
    pq.pop();

    if (bestG.find(cur.state) != bestG.end() && cur.g > bestG[cur.state]) {
      continue;
    }

    result.processed++;
    result.maxDepth = max(result.maxDepth, (int)cur.path.size());

    if (cur.state == goal) {
      result.path = cur.path;

      auto endTime = chrono::high_resolution_clock::now();
      result.timeMs = chrono::duration<double, milli>(endTime - startTime).count();
      return result;
    }

    for (char move : order) {
      if (move == 'L' && ((cur.zeroPos % cols) != 0)){
        AStarNode next = cur;
        swap(next.state[cur.zeroPos], next.state[cur.zeroPos - 1]);
        next.zeroPos = findZero(next.state);
        next.path += move;
        next.lastMove = move;
        next.g++;
        next.h = heuristicValue(next.state, goal, cols, heuristic);
        next.f = next.g + next.h;

        if (bestG.find(next.state) == bestG.end() || next.g < bestG[next.state]) {
          if (bestG.find(next.state) == bestG.end()) {
            result.visited++;
          }
         bestG[next.state] = next.g;
          pq.push(next);
        }
        }

        if (move == 'R' && ((cur.zeroPos % cols) != cols - 1)){
          AStarNode next = cur;
          swap(next.state[cur.zeroPos], next.state[cur.zeroPos + 1]);
          next.zeroPos = findZero(next.state);
          next.path += move;
          next.lastMove = move;
          next.g++;
          next.h = heuristicValue(next.state, goal, cols, heuristic);
          next.f = next.g + next.h;

          if (bestG.find(next.state) == bestG.end() || next.g < bestG[next.state]) {
            if (bestG.find(next.state) == bestG.end()) {
              result.visited++;
            }
            bestG[next.state] = next.g;
            pq.push(next);
          }
          }

          if (move == 'U' && (cur.zeroPos > (cols-1))){
             AStarNode next = cur;
            swap(next.state[cur.zeroPos], next.state[cur.zeroPos - cols]);
             next.zeroPos = findZero(next.state);
             next.path += move;
             next.lastMove = move;
             next.g++;
             next.h = heuristicValue(next.state, goal, cols, heuristic);
             next.f = next.g + next.h;

             if (bestG.find(next.state) == bestG.end() || next.g < bestG[next.state]) {
               if (bestG.find(next.state) == bestG.end()) {
                 result.visited++;
               }
              bestG[next.state] = next.g;
               pq.push(next);
             }
            }
            if (move == 'D' && cur.zeroPos < (cur.state.size()-cols)){
               AStarNode next = cur;
               swap(next.state[cur.zeroPos], next.state[cur.zeroPos + cols]);
               next.zeroPos = findZero(next.state);
               next.path += move;
               next.lastMove = move;
               next.g++;
               next.h = heuristicValue(next.state, goal, cols, heuristic);
               next.f = next.g + next.h;

               if (bestG.find(next.state) == bestG.end() || next.g < bestG[next.state]) {
                 if (bestG.find(next.state) == bestG.end()) {
                   result.visited++;
                 }
                 bestG[next.state] = next.g;
                 pq.push(next);
           }
         }
       }
    }
        result.path = "NOTHING";

        auto endTime = chrono::high_resolution_clock::now();
        result.timeMs = chrono::duration<double, milli>(endTime - startTime).count();

        return result;
  }

Result algorithms::BFS(const vector<int>& startBoard, int rows, int cols, const string& order) {
    auto startTime = chrono::high_resolution_clock::now();
    Result result;
    vector<int> goal = makeGoalState(rows, cols);

    queue<Node> q;
    set<vector<int>> visited;

    int initialZero = findZero(startBoard);
    Node startNode = {startBoard, "", initialZero, 'N'};
    q.push(startNode);
    visited.insert(startBoard);
    result.visited++;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();
        result.processed++;

        // Оновлюємо максимальну глибину (це довжина шляху)
        result.maxDepth = max(result.maxDepth, (int)current.path.size());

        if (current.state == goal) {
            result.path = current.path;
            auto endTime = chrono::high_resolution_clock::now();
            result.timeMs = chrono::duration<double, milli>(endTime - startTime).count();
            return result;
        }

        for (char move : order) {
            int newZeroPos = -1;

            if (move == 'L' && (current.zeroPos % cols) != 0) newZeroPos = current.zeroPos - 1;
            else if (move == 'R' && (current.zeroPos % cols) != (cols - 1)) newZeroPos = current.zeroPos + 1;
            else if (move == 'U' && current.zeroPos >= cols) newZeroPos = current.zeroPos - cols;
            else if (move == 'D' && current.zeroPos < (rows - 1) * cols) newZeroPos = current.zeroPos + cols;

            if (newZeroPos != -1) {
                vector<int> newBoard = current.state;
                swap(newBoard[current.zeroPos], newBoard[newZeroPos]);

                if (visited.find(newBoard) == visited.end()) {
                    visited.insert(newBoard);
                    result.visited++;
                    Node nextNode = {newBoard, current.path + move, newZeroPos, move};
                    q.push(nextNode);
                }
            }
        }
    }

    result.path = "NOTHING";
    auto endTime = chrono::high_resolution_clock::now();
    result.timeMs = chrono::duration<double, milli>(endTime - startTime).count();
    return result;
}
