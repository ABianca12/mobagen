#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f averageVelocity = Vector2f::zero();
  int numberInRadius = 0;

  for (auto i :neighborhood) {
    if (!neighborhood.empty()) {
      const double distanceToBoid = (i->transform.position - boid->transform.position).getMagnitude();
      if (distanceToBoid <= boid->getDetectionRadius()) {
        averageVelocity += i->velocity;
        numberInRadius++;
      }
      averageVelocity /= numberInRadius;
    }
  }

  return Vector2f::normalized(averageVelocity);
}