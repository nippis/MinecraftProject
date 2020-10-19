#include "Move.h"

const float ROTATING_SPEED = 3.14f;
const float MOVING_SPEED = 2.0f;

Move::Move() : 
  m_location({0.0, 0.0, 0.0, 0.0}),
  m_rotation({0.0, 0.0, 0.0, 0.0})
{
}

Move::Move(XMVECTOR location, XMVECTOR rotation) :
  m_location(location), m_rotation(rotation)
{
}

Move::~Move()
{
}
