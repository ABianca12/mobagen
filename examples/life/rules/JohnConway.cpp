#include "JohnConway.h"

#include <numeric>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  // world.SetNext() sets next tile in buffer to dead or alive
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {

    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int accumulator = 0;

  for (int i = point.x - 1; i < point.x + 1; i++) {
    for (int j = point.y - 1; j < point.y + 1; j++) {
      if (point.x != i && point.y != j) {
        accumulator += world.Get({i,j});
      }
    }
  }
  // accumulator is the cumulative number of neighbors by adding a boolean, ex, is there is a 3x3 grid a result 9 means all squares are filled
  return accumulator;
}
