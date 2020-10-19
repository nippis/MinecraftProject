#pragma once

#include <DirectXMath.h>
#include <memory>

#include "../Engine/Movement.h"

class Player
{
public:
  Player();
  virtual ~Player();

  DirectX::XMVECTOR GetLocation();
  DirectX::XMVECTOR GetRotation();
  DirectX::XMMATRIX GetMovement();

  void Move(XMVECTOR movement, double deltaTime);
  void Rotate(XMVECTOR rotation, double deltaTime);

  const float MOVEMENT_SPEED = 2.0f; // Movement per second
  const float ROTATION_SPEED = 3.14f; // Rotation per second 
             
private:     
  std::shared_ptr<Movement> m_movement;

};

