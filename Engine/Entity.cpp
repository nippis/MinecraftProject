#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  Transform(location), m_height(height), m_width(width), m_depth(depth)
{
  m_bBox = BoundingBox({XMVectorGetX(location), XMVectorGetY(location), XMVectorGetZ(location)}, {width / 2, depth / 2, height / 2});
}

Entity::~Entity()
{
}

const BoundingBox& Entity::GetBoundingBox()
{
  return m_bBox;
}