#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  // Chooses pathing algorithm
  std::vector<Point2D> path = world->getUsingBFS() ? generatePath(world) : AStar(world);

  // If path is not empty the last element in the path is returned
  if (!path.empty()) {
    return path[path.size() - 1];
  }

  // If path is empty randomly choose neighbor
  auto rand = Random::Range(0, 5);
  int index = rand;
  auto pos = world->getCat();

  // Create a movement options vector
  std::vector<Point2D> directions = {};
  directions.push_back(World::NE(pos));
  directions.push_back(World::NW(pos));
  directions.push_back(World::E(pos));
  directions.push_back(World::W(pos));
  directions.push_back(World::SW(pos));
  directions.push_back(World::SE(pos));

  if (world->getContent(directions[rand])) {
    index++;

    while (rand != index) {
      if (index >= directions.size()) {
        index = 0;
      }

      if (!world->getContent(directions[rand])) {
        // Returns if there is an available neighbor to move to
        return directions[index];
      }

      index++;
    }

    // Returned if all neighbors are blocked
    return Point2D::INFINITE;
  }

  return directions[rand];
}
