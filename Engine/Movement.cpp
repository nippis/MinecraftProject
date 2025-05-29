#include "Movement.h"

Movement::Movement() : 
  m_location({0.0f, 0.0f, 0.0f}),
  m_rotation({1.0f, 0.0f, 0.0f, 0.0f})
{
}

Movement::Movement(XMVECTOR location) :
  m_rotation({ 1.0f, 0.0f, 0.0f, 0.0f})
{
  XMStoreFloat3(&m_location, location);
}

Movement::~Movement()
{
}

void Movement::AddLocation(const XMVECTOR& locationAdd)
{
  XMStoreFloat3(&m_location, XMLoadFloat3(&m_location) + locationAdd);
}

void Movement::AddRotation(const XMVECTOR& rotationAdd)
{
  XMVECTOR rotation = XMLoadFloat4(&m_rotation);
  XMStoreFloat4(&m_rotation, XMQuaternionNormalize(XMQuaternionMultiply(rotationAdd, rotation)));
}

void Movement::SetLocation(const XMVECTOR& location)
{
  XMStoreFloat3(&m_location, location);
}

void Movement::SetRotation(const XMVECTOR& rotation)
{
  XMStoreFloat4(&m_rotation, rotation);
}

XMVECTOR Movement::GetLocationVec()
{
  return XMLoadFloat3(&m_location);
}

const XMFLOAT3& Movement::GetLocation()
{
  return m_location;
}

XMVECTOR Movement::GetRotationVec()
{
  return XMLoadFloat4(&m_rotation);
}

const XMFLOAT4& Movement::GetRotation()
{
  return m_rotation;
}
