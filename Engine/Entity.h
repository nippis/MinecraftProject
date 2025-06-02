#pragma once

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "Constants.h"
#include "Transform.h"

using namespace DirectX;

class Entity : public Transform
{
public:
  Entity(XMVECTOR location, float height, float width, float depth);
  virtual ~Entity() = default;

  const BoundingBox& GetBoundingBox() const;

protected:
  BoundingBox m_bBox;
  float m_height;
  float m_width;
  float m_depth;
};

