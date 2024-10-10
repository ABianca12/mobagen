#include "../World.h"
#include "RecursiveBacktrackerExample.h"
#include <array>
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  // Variable Declaration
  Point2D point;
  Point2D nextPoint;
  Point2D orientation;
  Node node;
  std::vector<Point2D> neighbors;

  // Checks if stack is empty
  if (stack.empty()) {
    // Adds starting point to the stack
    stack.push_back(randomStartPoint(w));
  }

  // Checks if stack is not empty
  if (!stack.empty()) {
    // Gets the current point from the stack
    point = stack.back();
    // Gets the node associated with the current point
    node = w->GetNode(point);
    // Gets the neighbors of the current point
    neighbors = getVisitables(w, point);

    // Checks if there are neighbors to travel to
    if (!neighbors.empty()) {
      // Sets the nodes color to blue showing it has been visited
      w->SetNodeColor(point, Color::Blue);
      // Marks the current node as visited
      visited[point.y][point.x] = true;

      // Uses a random number to choose the next point
      nextPoint = neighbors[getRandomNumber() % neighbors.size()];
      // Adds the next point to the stack
      stack.push_back(nextPoint);

      // Calculates the orientation needed inorder to travel to the next point
      orientation = nextPoint - point;

      // Checks the right
      if (orientation.x == 1) {
        node.SetEast(false);
      }
      // Checks the left
      else if (orientation.x == -1) {
        node.SetWest(false);
      }
      // Checks below
      else if (orientation.y == 1) {
        node.SetSouth(false);
      }
      // Checks above
      else if (orientation.y == -1) {
        node.SetNorth(false);
      }

      // Sets the point with the wall data
      w->SetNode(point, node);

      // Checks if there are no neighbors
    }else{
      // Sets point to the end of the stack
      point = stack.back();
      // Sets the point to green meaning it has been checked
      w->SetNodeColor(point, Color::Green);
      // Removes the last node in the stack
      stack.pop_back();
    }

  }
  // Returns false when the stack is empty
  return !stack.empty();
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

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // Checks right neighbor
  if (p.x + 1 <= sideOver2 && !visited[p.y][p.x + 1] && w->GetNodeColor(p.Right()) != Color::Green) {
    visitables.emplace_back(p.x + 1, p.y);
  }

  // Checks right neighbor
  if (p.x - 1 >= -sideOver2 && !visited[p.y][p.x - 1] && w->GetNodeColor(p.Left()) != Color::Green) {
    visitables.emplace_back(p.x - 1, p.y);
  }

  // Checks bottom neighbor
  if (p.y + 1 <= sideOver2 && !visited[p.y + 1][p.x] && w->GetNodeColor(p.Down()) != Color::Green) {
    visitables.emplace_back(p.x, p.y + 1);
  }

  // Checks top neighbor
  if (p.y - 1 >= -sideOver2 && !visited[p.y - 1][p.x] && w->GetNodeColor(p.Up()) != Color::Green) {
    visitables.emplace_back(p.x, p.y - 1);
  }

  return visitables;
}

int RecursiveBacktrackerExample::getRandomNumber() {
  static int index = 0;
  const std::array randNums = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  // Resets index if at the end of the array
  if (index == std::size(randNums)) {
    index = 0;
  }

  // Returns a random number based upon
  return randNums[index++];
}