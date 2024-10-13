#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"

#include <unordered_map>

#include <unordered_set>
#include <vector>

class World;

class Agent {
public:
  // AStar Struct
  struct AStarNode {
    Point2D point;
    AStarNode() = default;
    AStarNode(Point2D p) : point(p) {};
    int weight = 0;
    int heuristic = 0;

    // < Operator overloading
    bool operator<(const AStarNode &other) const {
      return (weight + heuristic) > (other.weight + other.heuristic);
    }

    // Manhattan heuristic calculation
    int calculateHeuristicManhattan(const Point2D& other) const {
      return abs(point.x - other.x) + abs(point.y - other.y);
    }

    // Closest side heuristic calculation
    int calculateHeuristicCloseSide(const Point2D& other, int halfSideSize) const {
      // Checks right side
      if (other.x - other.y > 0 && other.x + other.y > 0) {
        // Returns right side distance
        return halfSideSize - other.x;
      }
      // Checks top side
      else if (other.x - other.y < 0 && other.x + other.y > 0) {
        // Returns top side distance
        return halfSideSize - other.y;
      }
      // Checks left side
      else if (other.x - other.y < 0 && other.x + other.y < 0) {
        // Returns left side distance
        return other.x - halfSideSize;
      }else{
        // Returns bottom distance if all other cases fail
        return other.y - halfSideSize;
      }
    }
  };

  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* world, Point2D p, std::unordered_set<Point2D>& queue, std::unordered_map<Point2D, bool>& visited);
  Point2D manhattanExit(World* world, Point2D p);
  std::vector<Point2D> AStar(World* world);

  int heuristic(Point2D p, int SideSizeOver2);
};

#endif  // AGENT_H