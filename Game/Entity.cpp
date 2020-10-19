#include "Entity.h"

Entity::Entity(DirectX::XMVECTOR location) :
  m_movement(std::make_shared<Movement>(location, DirectX::XMVectorZero()))
{
}

Entity::~Entity()
{
}

DirectX::XMVECTOR Entity::GetLocation()
{
  return m_movement->GetLocation();
}

std::shared_ptr<BoundingBox> Entity::GetBoundingBox()
{
  return m_bBox;
}
