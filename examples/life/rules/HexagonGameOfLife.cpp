//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"

void HexagonGameOfLife::Step(World& world) {
  // Iterates through the world
  for (int i = 0; i <world.SideSize(); i++) {
    for (int j = 0; j <world.SideSize(); j++) {
      const bool isCurrentSpaceAlive = world.Get({i,j});
      const int liveNeighbors = CountNeighbors(world, {i, j});

      if (isCurrentSpaceAlive) {
        // Underpopulation rule
        if (liveNeighbors < 2) {
          world.SetNext({i,j}, false);
        }
        // Continuation rule
        else if (liveNeighbors == 2) {
          world.SetNext({i,j}, true);
        } else {
          // Anything that does not get caught by the first two statements would fall under the overpopulation rule
          world.SetNext({i,j}, false);
        }
      } else {
        // 3 alive neighbor rule
        if (liveNeighbors == 2) {
          world.SetNext({i,j}, true);
        }
      }
    }
  }
}


int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int accumulator = 0;
  int startingPoint = point.x - static_cast<int>(point.y % 2 == 0);

  // All for loops iterate around the starting point with offsets inorder to find the neighbors of the point in specific regions

  // Live neighbors above
  for (int i = startingPoint; i < startingPoint + 2; i++) {
    // Here the offset is -1
    if (world.Get({i, point.y - 1})) {
      accumulator++;
    }
  }

  // Live neighbors below
  for (int i = startingPoint; i < startingPoint + 2; i++) {
    // Here the offset is +1
    if (world.Get({i, point.y + 1})) {
      accumulator++;
    }
  }

  // Live neighbors on sides
  startingPoint = point.x - 1;
  for (int i = startingPoint; i < startingPoint + 3; i++) {
    // Excludes self
    if (i != point.x) {
      // No offset needed
      if (world.Get({i, point.y})) {
        accumulator++;
      }
    }
  }

  return accumulator;
}
