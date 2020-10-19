#include "../Game/Player.h"

Player::Player() :
  m_movement(std::make_shared<Movement>())
{

}

Player::~Player()
{

}

DirectX::XMVECTOR Player::GetLocation()
{
  return m_movement->GetLocation();
}

DirectX::XMVECTOR Player::GetRotation()
{
  return m_movement->GetRotation();
}

DirectX::XMMATRIX Player::GetMovement()
{
  return m_movement->GetMovement();
}

void Player::Move(XMVECTOR movement, double deltaTime)
{
  m_movement->AddLocation(movement * MOVEMENT_SPEED * deltaTime);
}

void Player::Rotate(XMVECTOR rotation, double deltaTime)
{
  m_movement->AddRotation(rotation * ROTATION_SPEED * deltaTime);
}
