#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  m_movement(std::make_shared<Movement>(location, XMVectorZero())),
  m_bBox(std::make_shared<BoundingBox>(location, height, width, depth))
{
}

Entity::~Entity()
{
}

XMVECTOR Entity::GetLocation()
{
  return m_movement->GetLocation();
}

std::shared_ptr<BoundingBox> Entity::GetBoundingBox()
{
  return m_bBox;
}

BoundingBox::BoundingBox(XMVECTOR location, float height, float width, float depth)
{
  Xmin = XMVectorGetX(location) - width / 2;
  Xmax = XMVectorGetX(location) + width / 2;
  Ymin = XMVectorGetY(location) - height / 2;
  Ymax = XMVectorGetY(location) + height / 2;
  Zmin = XMVectorGetZ(location) - depth / 2;
  Zmax = XMVectorGetZ(location) + depth / 2;
}
