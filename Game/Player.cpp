#include "../Game/Player.h"

Player::Player(std::shared_ptr<Timer> timer) :
  Entity(DirectX::XMVectorZero()),
  m_jumpState(0.0f),
  m_jumpTimer(timer)
{
  m_jumpTimer->stop();
}

Player::~Player()
{

}

DirectX::XMVECTOR Player::GetRotation()
{
  return m_movement->GetRotation();
}

DirectX::XMMATRIX Player::GetMovement()
{
  return m_movement->GetMovement() * XMMatrixTranslation(0.0f, -GetJumpHeight(), 0.0f);
}

void Player::Move(XMVECTOR movement, double deltaTime)
{
  m_movement->AddLocation(movement * MOVEMENT_SPEED * deltaTime);
}

void Player::Rotate(XMVECTOR rotation, double deltaTime)
{
  m_movement->AddRotation(rotation * ROTATION_SPEED * deltaTime);
}

bool Player::Jump()
{
  if (m_jumpState <= 0)
  {
    m_jumpState += m_jumpTimer->getDeltaTime() / JUMP_DURATION;
    return true;
  }
  else
  {
    return false;
  }
}

float Player::GetJumpHeight()
{
  if (m_jumpState > 0.0f && m_jumpState < 1.0f)
  {
    m_jumpState += m_jumpTimer->getDeltaTime() / JUMP_DURATION;
    return float(-pow((2.0 * m_jumpState - 1.0), (2.0)) + 1.0);
  }
  else
  {
    m_jumpState = 0.0f;
    return m_jumpState;
  }

}
