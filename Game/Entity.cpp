#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  m_movement(std::make_shared<Movement>(location)),
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
  Xmin = XMVectorGetX(location) - abs(width  / 2);
  Xmax = XMVectorGetX(location) + abs(width  / 2);
  Ymin = XMVectorGetY(location) - abs(height / 2);
  Ymax = XMVectorGetY(location) + abs(height / 2);
  Zmin = XMVectorGetZ(location) - abs(depth  / 2);
  Zmax = XMVectorGetZ(location) + abs(depth  / 2);
}

void BoundingBox::Update(XMVECTOR movement)
{
  Xmin += XMVectorGetX(movement);
  Xmax += XMVectorGetX(movement);
  Ymin += XMVectorGetY(movement);
  Ymax += XMVectorGetY(movement);
  Zmin += XMVectorGetZ(movement);
  Zmax += XMVectorGetZ(movement);
}