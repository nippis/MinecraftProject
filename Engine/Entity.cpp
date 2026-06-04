#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  m_height(height), m_width(width), m_depth(depth), m_forward({ 0.0f, 0.0f, -1.0f }),
  m_up({ 0.0f, 1.0f, 0.0f })
{
  m_bBox = BoundingBox({0.0f, 0.0f, 0.0f }, {width / 2, depth / 2, height / 2});
  SetLocation(location);
}

const BoundingBox& Entity::GetBoundingBox() const
{
  return m_bBox;
}

void Entity::SetLocation(const XMVECTOR& location)
{
  XMStoreFloat3(&m_location, location);
  m_bBox.Center = m_location;
}

void Entity::SetDirection(const XMVECTOR& forward)
{
  XMStoreFloat3(&m_forward, forward);
}

void Entity::SetUp(const XMVECTOR& up)
{
  XMStoreFloat3(&m_up, up);
}

XMVECTOR Entity::GetLocation() const
{
  return XMLoadFloat3(&m_location);
}

XMVECTOR Entity::GetDirection() const
{
  return XMLoadFloat3(&m_forward);
}

XMVECTOR Entity::GetForwardXZ() const
{
  return XMVector3Normalize(XMVectorSet(m_forward.x, 0, m_forward.z, 0));
}

XMVECTOR Entity::GetUp() const
{
  return XMLoadFloat3(&m_up);
}

XMVECTOR Entity::GetRightXZ() const
{
  return XMVector3Normalize(XMVector3Cross(GetForwardXZ(), Y_POS));
}
