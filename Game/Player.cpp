#include "../Game/Player.h"

Player::Player(std::shared_ptr<Timer> timer) :
  Entity({0.0f, 3.0f, 0.0f, 0.0f}, 0.2f, 1.8f, 0.2f),
  m_jumpTimer(timer),
  m_dropSpeed(0.0f),
  m_dropping(false)
{
  m_jumpTimer->stop();
}

Player::~Player()
{

}

// --------------------------
// Returns normalized xy plane forward vector
// --------------------------
DirectX::XMVECTOR Player::GetForward()
{
  return XMVector4Normalize(XMVectorSet(XMVectorGetX(m_movement->GetRotationVec()), XMVectorGetY(m_movement->GetRotationVec()), 0.0f, 0.0f));
}

DirectX::XMVECTOR Player::GetLeft()
{
  return XMVector3Rotate(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), m_movement->GetRotationVec());
}

DirectX::XMVECTOR Player::GetUp()
{
  return XMVector3Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), m_movement->GetRotationVec());
}

bool Player::IsDropping()
{
  return m_dropping;
}

void Player::Move(XMVECTOR movement, double deltaTime)
{
  m_movement->AddLocation(movement * MOVEMENT_SPEED * deltaTime);
  m_bBox.Transform(m_bBox, XMMatrixTranslationFromVector(movement * MOVEMENT_SPEED * deltaTime));
}

void Player::Rotate(XMVECTOR rotation, double deltaTime)
{
  m_movement->AddRotation(rotation * ROTATION_SPEED * deltaTime);
}

bool Player::Jump()
{
  if (true)//m_dropSpeed == 0.0f)
  {
    m_dropSpeed = -JUMP_SPEED;
    m_dropping = true;
    XMVECTOR direction = { 0.0f, 0.0f, -1.0f, 0.0f };
    m_movement->AddLocation(direction * m_dropSpeed * m_jumpTimer->getDeltaTime());
    m_bBox.Transform(m_bBox, XMMatrixTranslationFromVector(direction * m_dropSpeed * m_jumpTimer->getDeltaTime()));
    return true;
  }
  else
    return false;
}

void Player::Drop()
{
  m_dropping = true;
  m_dropSpeed += m_jumpTimer->getDeltaTime() * DROP_ACCELERATION;
  XMVECTOR direction = { 0.0f, 0.0f, -1.0f, 0.0f };
  m_movement->AddLocation(direction * m_dropSpeed * m_jumpTimer->getDeltaTime());
  m_bBox.Transform(m_bBox, XMMatrixTranslationFromVector(direction * m_dropSpeed * m_jumpTimer->getDeltaTime()));
}

void Player::Stop()
{
  m_dropping = false;
  m_dropSpeed = 0.0f;
}
