#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

using namespace std;

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

    // Gets current point from stack
    Point2D const p = frontier.front();
    // Removes current point form stack
    frontier.pop();
    // Erases current point from frontierSet
    frontierSet.erase(p);

    int const gridHalfSize = w->getWorldSideSize() / 2;
    if (p.y == gridHalfSize || p.x == gridHalfSize || p.y == -gridHalfSize || p.x == -gridHalfSize) {
      borderExit = p;
      break;
    }

    // Sets the current point as visited
    visited[p] = true;
    vector<Point2D> neighbors = getVisitableNeighbors(w, p, frontierSet, visited);

    if (!neighbors.empty()) {
      for (auto const n : neighbors) {
        cameFrom[n] = p;
        frontier.push(n);
        frontierSet.insert(n);
      }
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  vector<Point2D> pathToExit;

  if (borderExit != Point2D::INFINITE) {
    Point2D currentExit = borderExit;

    while (currentExit != catPos) {
      pathToExit.push_back(currentExit);
      currentExit = cameFrom[currentExit];
    }
  }

  return pathToExit;
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* world, Point2D p, std::unordered_set<Point2D>& queue,
                                                  std::unordered_map<Point2D, bool>& visited) {
  int startPoint = p.x - static_cast<int>(p.y % 2 == 0);
  vector<Point2D> visitables;

  // Looks for open neighbors above
  for (int i = startPoint; i < startPoint + 2; i++) {
    Point2D const checkNeighbor = {i, p.y - 1};

    if (!queue.contains(checkNeighbor) && !visited.contains(checkNeighbor) && !world->getContent(checkNeighbor) && world->getCat() != checkNeighbor) {
      visitables.push_back(checkNeighbor);
    }
  }

  // Looks for open neighbors below
  for (int i = startPoint; i < startPoint + 2; i++) {
    Point2D const checkNeighbor = {i, p.y + 1};

    if (!queue.contains(checkNeighbor) && !visited.contains(checkNeighbor) && !world->getContent(checkNeighbor) && world->getCat() != checkNeighbor) {
      visitables.push_back(checkNeighbor);
    }
  }

  // Looks for open neighbors on all sides and makes sure the current point is not included
  startPoint = p.x - 1;
  for (int i = startPoint; i < startPoint + 3; i++) {
    if (i != p.x) {
      Point2D const checkNeighbor = {i, p.y};

      if (!queue.contains(checkNeighbor) && !visited.contains(checkNeighbor) && !world->getContent(checkNeighbor)
          && world->getCat() != checkNeighbor) {
        visitables.push_back(checkNeighbor);
      }
    }
  }

  // Returns vector of all valid neighbors
  return visitables;
}
int Agent::heuristic(const Point2D p, int SideSizeOver2) {

  if (p.x - p.y > 0 && p.x + p.y > 0) {

  }
}


