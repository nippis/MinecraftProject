#pragma once

#include <DirectXMath.h>
#include <memory>

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

private:
  std::shared_ptr<BoundingBox> m_bBox;
  DirectX::XMVECTOR m_location;
};

