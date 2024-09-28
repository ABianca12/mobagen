#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  Point2D point;
  Point2D nextPoint;
  Node node;
  std::vector<Point2D> neighbors;

  if (stack.empty() && visited.empty()) {
    stack.push_back(randomStartPoint(w));
  }

  if (!stack.empty()) {
    point = stack.back();
    node = w->GetNode(point);
    neighbors = getVisitables(w, point);

    if (!neighbors.empty()) {
      w->SetNodeColor(point, Color::Blue);
      visited[point.y][point.x] = true;

      nextPoint = neighbors[getRandomNumber() % neighbors.size()];
      stack.push_back(nextPoint);
    }

  }
  // Depth first search
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  if (p.x - 1 >= -sideOver2) {
    visitables.emplace_back(p.x - 1, p.y);
  }
  else if (p.x + 1 <= sideOver2) {
    visitables.emplace_back(p.x + 1, p.y);
  }

  if (p.y - 1 >= -sideOver2) {
    visitables.emplace_back(p.x, p.y - 1 );
  }
  else if (p.y + 1 <= sideOver2) {
    visitables.emplace_back(p.x, p.y + 1 );
  }

  return visitables;
}

int RecursiveBacktrackerExample::getRandomNumber() {
  int randomIndex = 0;
  std::vector<int> randomNums = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  if (randomIndex == randomNums.size()) {
    randomIndex = 0;
  }
  return randomNums[randomIndex++];
}