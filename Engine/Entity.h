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

  const BoundingBox& GetBoundingBox() const;

  float height() const { return m_bBox.Extents.x; }
  float width() const { return m_bBox.Extents.y; }
  float depth() const { return m_bBox.Extents.z; }

protected:
  BoundingBox m_bBox;
};

