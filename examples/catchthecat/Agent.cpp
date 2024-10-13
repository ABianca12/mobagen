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

Point2D Agent::manhattanExit(World* world, Point2D point) {
  // Variable declaration
  int const SideSizeOver2 = world->getWorldSideSize() / 2;
  int xWallDistance = SideSizeOver2 - abs(point.x);
  int yWallDistance = SideSizeOver2 - abs(point.y);

  // Checks left wall distance
  if (xWallDistance < yWallDistance && point.x < 0) {
    return {-SideSizeOver2, point.y};
  }
  // Checks top wall distance
  else if (xWallDistance > yWallDistance && point.y < 0) {
    return {point.x, -SideSizeOver2};
  }
  // Checks right wall distance
  else if (yWallDistance > xWallDistance && point.x > 0) {
    return {SideSizeOver2, point.y};
  }
  // Checks bottom wall distance
  else if (yWallDistance < xWallDistance && point.y > 0) {
    return {point.x, SideSizeOver2};
  }

  // Returns closets point
  return {point.x, point.y};
}

vector<Point2D> Agent::AStar(World* world) {
  // Variable declaration
  unordered_map<Point2D, Point2D> previousPoint;
  priority_queue<AStarNode> frontier;
  unordered_set<Point2D> frontierSet;
  unordered_map<Point2D, bool> visitables;
  Point2D endGoal = {0, 0};

  AStarNode start = AStarNode(world->getCat());

  if (world->getUsingManhattan()) {
    endGoal = manhattanExit(world, start.point);
    // Calculates the start node heuristic using manhattan
    start.heuristic = start.calculateHeuristicManhattan(endGoal);
  }else{
    // Calculates the start node heuristic using the closest side method
    start.heuristic = start.calculateHeuristicCloseSide(start.point, world->getWorldSideSize() / 2);
  }

  // Adds the start node to the frontier
  frontier.push(start);
  // Adds the start node to the frontierSet
  frontierSet.insert(start.point);
  // If a border isn't found, a random point is returned
  Point2D borderExit = Point2D::INFINITE;

  while (!frontier.empty()) {
    // Gets the current node from the queue
    AStarNode const node = frontier.top();
    // Removes current node form priority queue
    frontier.pop();
    // Removes current node form the frontierSet
    frontierSet.erase(node.point);

    int const sideSizeOver2 = world->getWorldSideSize() / 2;

    if (node.point.x == sideSizeOver2 || node.point.x == -sideSizeOver2 || node.point.y == sideSizeOver2 || node.point.y == -sideSizeOver2) {
      borderExit = node.point;
      break;
    }

    // Sets the node as visited
    visitables[node.point] = true;
    vector<Point2D> neighbors = getVisitableNeighbors(world, node.point, frontierSet, visitables);

    // While there are neighbors, the previous point is updated and then added to the queue
    if (!neighbors.empty()) {
      for (Point2D const n : neighbors) {
        previousPoint[n] = node.point;
        AStarNode otherNeighborNode = AStarNode(n);
        otherNeighborNode.weight = node.weight + 1;

        // Test check
        if (world->getUsingManhattan()) {
          start.heuristic = start.calculateHeuristicManhattan(endGoal);
        } else {
          start.heuristic = start.calculateHeuristicCloseSide(start.point, world->getWorldSideSize() / 2);
        }

        frontier.push(otherNeighborNode);
        frontierSet.insert(n);
      }
    }
  }

  vector<Point2D> pathToExit;
  // If an end goal is found, the path is built
  if (borderExit != Point2D::INFINITE) {
    Point2D currentExit = borderExit;

    // Checks all previous points form the goal
    while (currentExit != start.point) {
      pathToExit.push_back(currentExit);
      currentExit = previousPoint[currentExit];
    }
  }

  return pathToExit;
}