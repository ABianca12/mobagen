#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  for (auto i : neighborhood) {
    if (i->getPosition().x == boid->getPosition().x && i->getPosition().y == boid->getPosition().y) {
      continue;
    }

    Vector2f dir = { i->getPosition().x - boid->getPosition().x, i->getPosition().y - boid->getPosition().y };

    float dist = dir.x * dir.x + dir.y * dir.y;

    if (dist >= separatingForce.x + separatingForce.y) {
      continue;
    }

    Vector2f hat = {dir.x/dist, dir.y/dist};
    float strength = 1/dist;
    separatingForce.x += hat.x * strength;
    separatingForce.y += hat.y * strength;
  }


  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }

  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
