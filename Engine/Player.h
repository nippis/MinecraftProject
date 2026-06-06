#pragma once

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <memory>

#include "Engine/Entity.h"

class Timer;

class Player :
  public Entity
{
public:
  Player();

  static constexpr float MOVEMENT_SPEED = 4.0f; // Movement per second
  static constexpr float ROTATION_SPEED = 3.14f; // Rotation per second 
  static constexpr float JUMP_SPEED = 4.0f; // Jump duration in seconds
  static constexpr float DROP_ACCELERATION = 10.0f; // Dropping acceleration u/s^2

  void setOnGround();
  void drop();
  void addDroppingVelocity(double dt);
  void jump();

  bool onGround() const { return m_onGround; }
  float getDroppingVelocity() const { return m_droppingVelocity; };

private:
  bool m_onGround;
  float m_droppingVelocity;
};

