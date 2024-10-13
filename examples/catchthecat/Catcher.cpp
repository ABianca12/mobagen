#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;

  // Chooses pathing algorithm
  std::vector<Point2D> path = world->getUsingBFS() ? generatePath(world) : AStar(world);

  if (!path.empty()) {
    return path[0];
  }

  std::vector<Point2D> neighbors = getVisitableNeighbors(world);
  auto rand = Random::Range(0, neighbors.size() - 1);

  return neighbors[rand];
}

std::vector<Point2D> Catcher::getVisitableNeighbors(World* world) {
  // Gets cat position
  auto cat = world->getCat();
  // Calculates x offset start based on the y level
  int start = cat.x - static_cast<int>(cat.y % 2 == 0);
  std::vector<Point2D> visitables;

  // Finds cat's neighbors above
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, cat.y - 1};
    if (!world->getContent(checkPoint)) {
      visitables.push_back(checkPoint);
    }
  }

  // Finds cat's neighbors below
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, cat.y + 1};
    if (!world->getContent(checkPoint)) {
      visitables.push_back(checkPoint);
    }
  }

  // Finds cat's neighbors on the same y level, excluding the current point
  start = cat.x - 1;
  for (int i = start; i < start + 3; i++) {
    if (i != cat.x) {
      Point2D const checkPoint = {i, cat.y};
      if (!world->getContent(checkPoint)) {
        visitables.push_back(checkPoint);
      }
    }
  }

  // Returns neighbors
  return visitables;
}
