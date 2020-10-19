#include "../Game/Player.h"

Player::Player() :
  m_location({0.0f,0.0f,0.0f})
{

}

Player::~Player()
{

}

PlayerCoord Player::GetLocation()
{
  return m_location;
}