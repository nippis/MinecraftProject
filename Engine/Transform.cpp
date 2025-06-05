#include "Transform.h"

Transform::Transform() : 
  m_location({0.0f, 0.0f, 0.0f}),
  m_forward({ 0.0f, 0.0f, -1.0f }),
  m_up({0.0f, 1.0f, 0.0f})
{
}

Transform::Transform(XMVECTOR location) :
  m_forward({ 0.0f, 0.0f, -1.0f }),
  m_up({ 0.0f, 1.0f, 0.0f })
{
  XMStoreFloat3(&m_location, location);
}

void Transform::AddLocation(const XMVECTOR& locationAdd)
{
  XMStoreFloat3(&m_location, XMLoadFloat3(&m_location) + locationAdd);
}

void Transform::AddRotation(const XMVECTOR& rotationAdd)
{
  XMStoreFloat3(&m_forward, XMVector3Transform(XMLoadFloat3(&m_forward), XMMatrixRotationRollPitchYawFromVector(rotationAdd)));
  XMStoreFloat3(&m_up, XMVector3Transform(XMLoadFloat3(&m_up), XMMatrixRotationRollPitchYawFromVector(rotationAdd)));
}

void Transform::SetLocation(const XMVECTOR& location)
{
  XMStoreFloat3(&m_location, location);
}

void Transform::SetDirection(const XMVECTOR& forward)
{
  XMStoreFloat3(&m_forward, forward);
}

void Transform::SetUp(const XMVECTOR& up)
{
  XMStoreFloat3(&m_up, up);
}

XMVECTOR Transform::GetLocation() const
{
  return XMLoadFloat3(&m_location);
}

XMVECTOR Transform::GetDirection() const
{
  return XMLoadFloat3(&m_forward);
}

XMVECTOR Transform::GetForwardXZ() const
{
  return XMVector3Normalize(XMVectorSet(m_forward.x, 0, m_forward.z, 0));
}

XMVECTOR Transform::GetUp() const
{
  return XMLoadFloat3(&m_up);
}

XMVECTOR Transform::GetRightXZ() const
{
  return XMVector3Normalize(XMVector3Cross(GetForwardXZ(), Y_POS));
}
