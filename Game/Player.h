#pragma once

#include <DirectXMath.h>
#include <memory>

#include "Engine/Movement.h"
#include "Engine/Timer.h"

class Player
{
public:
  Player(std::shared_ptr<Timer> timer);
  virtual ~Player();

  DirectX::XMVECTOR GetLocation();
  DirectX::XMVECTOR GetRotation();
  DirectX::XMMATRIX GetMovement();

  void Move(XMVECTOR movement, double deltaTime);
  void Rotate(XMVECTOR rotation, double deltaTime);
  bool Jump();

  const float MOVEMENT_SPEED = 2.0f; // Movement per second
  const float ROTATION_SPEED = 3.14f; // Rotation per second 
  const float JUMP_DURATION = 1.0f; // Jump duration in seconds
             
private:     
  float GetJumpHeight();
  
  float m_jumpState;
  std::shared_ptr<Movement> m_movement;
  std::shared_ptr<Timer> m_jumpTimer;

};

