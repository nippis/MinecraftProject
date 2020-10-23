#include "Movement.h"

Movement::Movement() : 
  m_location({0.0, 0.0, 0.0, 0.0}),
  m_rotation({1.0, 0.0, 0.0, 0.0}),
  m_up({0.0, 0.0, 1.0, 0.0})
{
}

Movement::Movement(XMVECTOR location) :
  m_location(location), m_rotation({ 1.0, 0.0, 0.0, 0.0 }),
  m_up({ 0.0, 0.0, 1.0, 0.0 })
{
}

Movement::~Movement()
{
}

void Movement::AddLocation(XMVECTOR locationAdd)
{
  m_location += locationAdd;
}

void Movement::AddRotation(XMVECTOR rotationAdd)
{
  m_rotation = XMVector4Transform(m_rotation, XMMatrixRotationRollPitchYawFromVector(rotationAdd));
  m_up = XMVector4Transform(m_up, XMMatrixRotationRollPitchYawFromVector(rotationAdd));
}

void Movement::SetLocation(XMVECTOR location)
{
  m_location = location;
}

void Movement::SetRotation(XMVECTOR rotation)
{
}

XMMATRIX Movement::GetMovement()
{
  XMMATRIX movement = XMMatrixIdentity();
  movement *= XMMatrixTranslationFromVector(m_location);
  movement *= XMMatrixRotationRollPitchYawFromVector(m_rotation);

  return XMMatrixTranslationFromVector(m_location);
}

XMVECTOR Movement::GetLocation()
{
  return m_location;
}

XMVECTOR Movement::GetRotation()
{
  return m_rotation;
}

XMVECTOR Movement::GetUp()
{
  return m_up;
}
