#include "Entity.h"

using namespace DirectX;

Entity::Entity(XMVECTOR location, float height, float width, float depth) :
  m_height(height), m_width(width), m_depth(depth), m_forward({ 0.0f, 0.0f, -1.0f }),
  m_up({ 0.0f, 1.0f, 0.0f })
{
  m_bBox = BoundingBox({XMVectorGetX(location), XMVectorGetY(location), XMVectorGetZ(location)}, {width / 2, depth / 2, height / 2});
}

const BoundingBox& Entity::GetBoundingBox() const
{
  return m_bBox;
}

void Entity::AddLocation(const XMVECTOR& locationAdd)
{
  XMStoreFloat3(&m_bBox.Center, XMLoadFloat3(&m_bBox.Center) + locationAdd);
}

void Entity::AddRotation(const XMVECTOR& rotationAdd)
{
  XMStoreFloat3(&m_forward, XMVector3Transform(XMLoadFloat3(&m_forward), XMMatrixRotationRollPitchYawFromVector(rotationAdd)));
  XMStoreFloat3(&m_up, XMVector3Transform(XMLoadFloat3(&m_up), XMMatrixRotationRollPitchYawFromVector(rotationAdd)));
}

void Entity::SetLocation(const XMVECTOR& location)
{
  XMStoreFloat3(&m_bBox.Center, location);
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
  return XMLoadFloat3(&m_bBox.Center);
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
