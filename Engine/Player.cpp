#include "../Engine/Player.h"
#include "../Engine/Entity.h"
#include "../Engine/Timer.h"

Player::Player() :
  Entity({0.0f, 5.0f, 0.0f, 0.0f}, 0.2f, 1.8f, 0.2f),
  m_onGround(false), m_droppingVelocity(0.0f)
{
}

void Player::setOnGround()
{
  m_onGround = true;
  m_droppingVelocity = 0.0f;
}

void Player::drop()
{
  m_onGround = false;
}

void Player::addDroppingVelocity(double dt)
{
  m_droppingVelocity += DROP_ACCELERATION * dt;
}
