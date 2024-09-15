//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"

void HexagonGameOfLife::Step(World& world) {

}


int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int accumulator = 0;
  int startingPoint = (point.x - 1) - static_cast<int>(point.y % 2 == 0);

  // Live neighbors on sides
  for (int i = startingPoint; i < startingPoint + 3; i++) {
    // Excludes self
    if (i != point.x) {
      if (world.Get({i, point.y})) {
        accumulator++;
      }
    }
  }

  // Live neighbors above
  startingPoint = point.x + 1;
  for (int i = startingPoint; i < startingPoint + 2; i++) {
    if (world.Get({i, point.y - 1})) {
      accumulator++;
    }
  }

  // Live neighbors below
  for (int i = startingPoint; i < startingPoint + 2; i++) {
    if (world.Get({i, point.y + 1})) {
      accumulator++;
    }
  }

  return accumulator;
}
