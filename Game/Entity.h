#pragma once

#include <DirectXMath.h>
#include <memory>

#include "Engine/Movement.h"

struct BoundingBox
{
  BoundingBox(DirectX::XMVECTOR location, float height, float width, float depth);

  float Xmin;
  float Xmax;
  float Ymin;
  float Ymax;
  float Zmin;
  float Zmax;
};

class Entity
{
public:
  Entity(DirectX::XMVECTOR location, float height, float width, float depth);
  ~Entity();

  DirectX::XMVECTOR GetLocation();

  std::shared_ptr<BoundingBox> GetBoundingBox();

protected:
  std::shared_ptr<BoundingBox> m_bBox;
  std::shared_ptr<Movement> m_movement;

  float m_height;
  float m_width;
  float m_depth;
};

