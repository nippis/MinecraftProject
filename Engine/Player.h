#pragma once

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <memory>

#include "Engine/Transform.h"
#include "Engine/Timer.h"
#include "Engine/Entity.h"

class Player :
  public Entity
{
public:
  Player(std::shared_ptr<Timer> timer);

  bool IsDropping() const;

  void Move(XMVECTOR movement, double deltaTime);
  void Reset();
  void Rotate(XMVECTOR rotation, double deltaTime);
  bool Jump();
  void Drop();
  void Stop();

  const float MOVEMENT_SPEED = 4.0f; // Movement per second
  const float ROTATION_SPEED = 3.14f; // Rotation per second 
  const float JUMP_SPEED = 4.0f; // Jump duration in seconds
  const float DROP_ACCELERATION = 10.0f; // Dropping acceleration u/s^2
             
private:     
  std::shared_ptr<Timer> m_jumpTimer;

  float m_dropSpeed;
  bool m_dropping;

};

