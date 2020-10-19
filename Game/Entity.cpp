#include "Entity.h"

Entity::Entity(DirectX::XMVECTOR location) :
  m_location(location)
{
}

Entity::~Entity()
{
}

DirectX::XMVECTOR Entity::GetLocation()
{
  return m_location;
}

std::shared_ptr<BoundingBox> Entity::GetBoundingBox()
{
  return m_bBox;
}
