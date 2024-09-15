#include "JohnConway.h"

#include <numeric>

void JohnConway::Step(World& world) {
  // Iterates through the world
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      // Gets the state of the current space
      const bool isCurrentSpaceAlive = world.Get({i, j});
      // Gets the number of live neighbors to the current space
      const int liveNeighbors = CountNeighbors(world, {i, j});

      // Checks if the current space is alive or not
      if (isCurrentSpaceAlive) {
        // Underpopulation rule
        if (liveNeighbors < 2) {
          world.SetNext({i,j}, false);
        }
        // Continuation rule
        else if (liveNeighbors <= 3) {
          world.SetNext({i, j}, true);
        } else {
          // Anything that does not get caught by the first two statements would fall under the overpopulation rule
          world.SetNext({i, j}, false);
        }
      } else {
        // 3 alive neighbor rule
        if (liveNeighbors == 3) {
          world.SetNext({i, j}, true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // accumulator is the cumulative number of neighbors by adding a boolean, ex, is there is a 3x3 grid a result 9 means all squares are filled
  int accumulator = 0;

  // Iterates through the whole world
  for (int i = point.x - 1; i < point.x + 2; i++) {
    for (int j = point.y - 1; j < point.y + 2; j++) {
      // Excludes current space from being a neighbor
      if (point.x != i || point.y != j) {
        // Adds the boolean 1 or 0 value to the accumulator variable
        accumulator += static_cast<int>(world.Get({i,j}));
      }
    }
  }
  return accumulator;
}