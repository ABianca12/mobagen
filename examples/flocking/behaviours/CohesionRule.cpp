#include "CohesionRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/gtc/constants.hpp"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f centerMass = {0,0};
  int numberInRadius = 0;

  for (auto i :neighborhood) {
    if (!neighborhood.empty() && i != boid) {
      const double distanceToBoid = (i->transform.position - boid->transform.position).getMagnitude();
      if (distanceToBoid <= boid->getDetectionRadius()) {
        centerMass += i->transform.position;
        numberInRadius++;
      }
      centerMass /= numberInRadius;

      cohesionForce = centerMass - boid->transform.position;

      if (cohesionForce.getMagnitude() <= boid->getDetectionRadius()) {
        return (cohesionForce / boid->getDetectionRadius());
      }
    }
  }
  return cohesionForce;
}