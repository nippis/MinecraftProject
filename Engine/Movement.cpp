#include "Movement.h"

Movement::Movement() : 
  m_location({0.0, 0.0, 0.0, 0.0}),
  m_rotation({0.0, 0.0, 0.0, 0.0})
{
}

Movement::Movement(XMVECTOR location, XMVECTOR rotation) :
  m_location(location), m_rotation(rotation)
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
  m_rotation += rotationAdd;
}

void Movement::SetLocation(XMVECTOR location)
{
  m_location = location;
}

void Movement::SetRotation(XMVECTOR rotation)
{
  m_rotation = rotation;
}

XMMATRIX Movement::GetMovement()
{
  XMMATRIX movement = XMMatrixIdentity();
  movement *= XMMatrixTranslationFromVector(m_location);
  movement *= XMMatrixRotationRollPitchYawFromVector(m_rotation);

  return movement;
}

XMVECTOR Movement::GetLocation()
{
  return m_location;
}

XMVECTOR Movement::GetRotation()
{
  return m_rotation;
}
