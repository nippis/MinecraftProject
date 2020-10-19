#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  m_movement(std::make_shared<Movement>(location, XMVectorZero())),
  m_bBox(std::make_shared<BoundingBox>(location, height, width, depth)),
  m_height(height), m_width(width), m_depth(depth)
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
  Ymin = XMVectorGetZ(location) - height / 2;
  Ymax = XMVectorGetZ(location) + height / 2;
  Zmin = XMVectorGetY(location) - depth / 2;
  Zmax = XMVectorGetY(location) + depth / 2;
}

void BoundingBox::Update(XMVECTOR movement)
{
  Xmin += XMVectorGetX(movement);
  Xmax += XMVectorGetX(movement);
  Ymin += XMVectorGetZ(movement);
  Ymax += XMVectorGetZ(movement);
  Zmin += XMVectorGetY(movement);
  Zmax += XMVectorGetY(movement);
}