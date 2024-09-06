#include "CohesionRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/gtx/dual_quaternion.hpp"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f centerMassPosition;
  for (int i = 0; i < neighborhood.size(); i++) {
    centerMassPosition += neighborhood[i]->getPosition();
  }

  centerMassPosition /= neighborhood.size();
  // n is the number of agents within the radius, < operation, excluding the target agent
  // Find number of agents within radius, that is n
  // Pcm is the groups center of mass, it is all the agents within the radius's positions added together, divided by the number of agents
  //
  // Force is equal to (current agent's position * centerMassPosition)/radius
  cohesionForce = (boid->getPosition() - centerMassPosition)/boid->getDetectionRadius();

  // find center of mass

  return cohesionForce;
}