#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  m_movement(std::make_shared<Movement>(location)),
  m_height(height), m_width(width), m_depth(depth)
{
  m_bBox = BoundingBox(m_movement->GetLocation(), { width/2, depth/2, height/2 });
}

Entity::~Entity()
{
}

XMVECTOR Entity::GetLocation()
{
  return m_movement->GetLocationVec();
}

DirectX::XMVECTOR Entity::GetRotation()
{
  return m_movement->GetRotationVec();
}

const BoundingBox& Entity::GetBoundingBox()
{
  return m_bBox;
}