#pragma once

#include <DirectXMath.h>
#include <memory>

#include "Engine/Movement.h"

struct BoundingBox
{
  DirectX::XMVECTOR Xmin;
  DirectX::XMVECTOR Xmax;
  DirectX::XMVECTOR Ymin;
  DirectX::XMVECTOR Ymax;
  DirectX::XMVECTOR Zmin;
  DirectX::XMVECTOR Zmax;
};

class Entity
{
public:
  Entity(DirectX::XMVECTOR location);
  ~Entity();

  DirectX::XMVECTOR GetLocation();

  std::shared_ptr<BoundingBox> GetBoundingBox();

protected:
  std::shared_ptr<BoundingBox> m_bBox;
  std::shared_ptr<Movement> m_movement;
};

