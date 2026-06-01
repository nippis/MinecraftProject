#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  Transform(location)
{
  XMFLOAT3 locationFloat3{XMVectorGetX(location), XMVectorGetY(location), XMVectorGetZ(location)};
  XMFLOAT3 extents{width / 2, depth / 2, height / 2};
  m_bBox = BoundingBox(locationFloat3, extents);
}

const BoundingBox& Entity::GetBoundingBox() const
{
  return m_bBox;
}