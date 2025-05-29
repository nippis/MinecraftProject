#pragma once

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <memory>

#include "Engine/Movement.h"

class Entity
{
public:
  Entity(XMVECTOR location, float height, float width, float depth);
  ~Entity();

  XMVECTOR GetLocation();
  XMVECTOR GetRotation();

  const BoundingBox& GetBoundingBox();

protected:
  BoundingBox m_bBox;
  std::shared_ptr<Movement> m_movement;

  float m_height;
  float m_width;
  float m_depth;
};

