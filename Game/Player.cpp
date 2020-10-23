#include "../Game/Player.h"

Player::Player(std::shared_ptr<Timer> timer) :
  Entity({0.0f, 0.0f, 3.0f, 0.0f}, 0.2f, 0.2f, 2.0f),
  m_jumpTimer(timer),
  m_dropSpeed(0.0f),
  m_dropping(false)
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
  return m_movement->GetMovement();
}

// --------------------------
// Returns normalized xy plane forward vector
// --------------------------
DirectX::XMVECTOR Player::GetForward()
{
  return XMVector4Normalize(XMVectorSet(XMVectorGetX(m_movement->GetRotation()), XMVectorGetY(m_movement->GetRotation()), 0.0f, 0.0f));
}

DirectX::XMVECTOR Player::GetLeft()
{
  XMVECTOR camLeft = XMVector3Cross(m_movement->GetUp(), m_movement->GetRotation());
  return -XMVector4Normalize(XMVectorSet(XMVectorGetX(camLeft), XMVectorGetY(camLeft), 0.0f, 0.0f));
}

DirectX::XMVECTOR Player::GetUp()
{
  return m_movement->GetUp();
}

bool Player::IsDropping()
{
  return m_dropping;
}

void Player::Move(XMVECTOR movement, double deltaTime)
{
  m_movement->AddLocation(movement * MOVEMENT_SPEED * deltaTime);
  m_bBox->Update(movement * MOVEMENT_SPEED * deltaTime);

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
    m_bBox->Update(direction * m_dropSpeed * m_jumpTimer->getDeltaTime());
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
  m_bBox->Update(direction * m_dropSpeed * m_jumpTimer->getDeltaTime());
}

void Player::Stop()
{
  m_dropping = false;
  m_dropSpeed = 0.0f;
}
