#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f seperationForce = {0,0};
  Vector2f boidAgentVector = {0,0};
  double boidMagnitude = 0.0;

  for (Boid* i : neighborhood) {
    if (!neighborhood.empty() && i != boid) {
      boidMagnitude = (boid->transform.position - i->transform.position).getMagnitude();
      if (boidMagnitude <= desiredMinimalDistance) {
        boidAgentVector = boid->transform.position - i->transform.position;
        seperationForce += desiredMinimalDistance * boidAgentVector / boidAgentVector.sqrMagnitude();
      }
    }else {
      return seperationForce;
    }
  }

  return seperationForce;
}



bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}