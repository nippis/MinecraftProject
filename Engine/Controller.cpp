#include "Controller.h"
#include <ranges>
#include <algorithm>

Controller::Controller(std::shared_ptr<Keyboard> keyboard, 
                       std::shared_ptr<Mouse> mouse, 
                       std::shared_ptr<GraphicsEngine> graphics, 
                       std::shared_ptr<Player> player,
                       std::shared_ptr<World> world) :
  m_keyboard(keyboard), m_mouse(mouse), m_player(player), m_graphics(graphics), m_world(world),
  m_mouseControl(false)
{

}

Controller::~Controller()
{
}

MoveDir Controller::MovementDirection() const
{
  MoveDir direction = MoveDir::none;

  if (m_keyboard->IsPressed(KEY_LEFT))
    direction = MoveDir::left;
  if (m_keyboard->IsPressed(KEY_FORW))
    direction = MoveDir::forw;
  if (m_keyboard->IsPressed(KEY_RIGHT))
    direction = MoveDir::right;
  if (m_keyboard->IsPressed(KEY_BACK))
    direction = MoveDir::back;

  if (m_keyboard->IsPressed(KEY_LEFT) && m_keyboard->IsPressed(KEY_FORW))
    direction = MoveDir::forwleft;
  if (m_keyboard->IsPressed(KEY_RIGHT) && m_keyboard->IsPressed(KEY_FORW))
    direction = MoveDir::forwright;
  if (m_keyboard->IsPressed(KEY_RIGHT) && m_keyboard->IsPressed(KEY_BACK))
    direction = MoveDir::backright;
  if (m_keyboard->IsPressed(KEY_LEFT) && m_keyboard->IsPressed(KEY_BACK))
    direction = MoveDir::backleft;
  if (m_keyboard->IsPressed(KEY_FORW) && m_keyboard->IsPressed(KEY_BACK))
    direction = MoveDir::none;
  if (m_keyboard->IsPressed(KEY_LEFT) && m_keyboard->IsPressed(KEY_RIGHT))
    direction = MoveDir::none;

  if (m_keyboard->IsPressed(KEY_FORW) && m_keyboard->IsPressed(KEY_BACK) && m_keyboard->IsPressed(KEY_LEFT))
    direction = MoveDir::left;
  if (m_keyboard->IsPressed(KEY_FORW) && m_keyboard->IsPressed(KEY_BACK) && m_keyboard->IsPressed(KEY_RIGHT))
    direction = MoveDir::right;
  if (m_keyboard->IsPressed(KEY_LEFT) && m_keyboard->IsPressed(KEY_RIGHT) && m_keyboard->IsPressed(KEY_FORW))
    direction = MoveDir::forw;
  if (m_keyboard->IsPressed(KEY_LEFT) && m_keyboard->IsPressed(KEY_RIGHT) && m_keyboard->IsPressed(KEY_BACK))
    direction = MoveDir::back;

  return direction;
}

MoveDir Controller::RotationDirection() const
{
  MoveDir direction = MoveDir::none;

  if (m_keyboard->IsPressed(KEY_YAW_LEFT))
    direction = MoveDir::left;
  if (m_keyboard->IsPressed(KEY_PITCH_UP))
    direction = MoveDir::forw;
  if (m_keyboard->IsPressed(KEY_YAW_RIGHT))
    direction = MoveDir::right;
  if (m_keyboard->IsPressed(KEY_PITCH_DOWN))
    direction = MoveDir::back;

  if (m_keyboard->IsPressed(KEY_YAW_LEFT) && m_keyboard->IsPressed(KEY_PITCH_UP))
    direction = MoveDir::forwleft;
  if (m_keyboard->IsPressed(KEY_YAW_RIGHT) && m_keyboard->IsPressed(KEY_PITCH_UP))
    direction = MoveDir::forwright;
  if (m_keyboard->IsPressed(KEY_YAW_RIGHT) && m_keyboard->IsPressed(KEY_PITCH_DOWN))
    direction = MoveDir::backright;
  if (m_keyboard->IsPressed(KEY_YAW_LEFT) && m_keyboard->IsPressed(KEY_PITCH_DOWN))
    direction = MoveDir::backleft;
  if (m_keyboard->IsPressed(KEY_PITCH_UP) && m_keyboard->IsPressed(KEY_PITCH_DOWN))
    direction = MoveDir::none;
  if (m_keyboard->IsPressed(KEY_YAW_LEFT) && m_keyboard->IsPressed(KEY_YAW_RIGHT))
    direction = MoveDir::none;

  if (m_keyboard->IsPressed(KEY_PITCH_UP) && m_keyboard->IsPressed(KEY_PITCH_DOWN) && m_keyboard->IsPressed(KEY_YAW_LEFT))
    direction = MoveDir::left;
  if (m_keyboard->IsPressed(KEY_PITCH_UP) && m_keyboard->IsPressed(KEY_PITCH_DOWN) && m_keyboard->IsPressed(KEY_YAW_RIGHT))
    direction = MoveDir::right;
  if (m_keyboard->IsPressed(KEY_YAW_LEFT) && m_keyboard->IsPressed(KEY_YAW_RIGHT) && m_keyboard->IsPressed(KEY_PITCH_UP))
    direction = MoveDir::forw;
  if (m_keyboard->IsPressed(KEY_YAW_LEFT) && m_keyboard->IsPressed(KEY_YAW_RIGHT) && m_keyboard->IsPressed(KEY_PITCH_DOWN))
    direction = MoveDir::back;

  return direction;
}

XMVECTOR Controller::GetPlayerTranslation() const
{
  switch (MovementDirection())
  {
  case (MoveDir::back):
    return -m_player->GetForwardXZ();
  case (MoveDir::right):
    return m_player->GetRightXZ();
  case (MoveDir::forw):
    return m_player->GetForwardXZ();
  case (MoveDir::left):
    return -m_player->GetRightXZ();
  case (MoveDir::backright):
    return 0.707 * (-m_player->GetForwardXZ() + m_player->GetRightXZ());
  case (MoveDir::forwright):
    return 0.707 * (m_player->GetForwardXZ() + m_player->GetRightXZ());
  case (MoveDir::backleft):
    return 0.707 * (-m_player->GetForwardXZ() - m_player->GetRightXZ());
  case (MoveDir::forwleft):
    return 0.707 * (m_player->GetForwardXZ() - m_player->GetRightXZ());
  }
  return XMVECTOR();
}

XMVECTOR Controller::GetPlayerRotation() const
{
  switch (RotationDirection())
  {
  case (MoveDir::back):
    if (XMVectorGetX(XMVector3AngleBetweenNormals(m_player->GetDirection(), m_player->GetForwardXZ())) < XM_PIDIV2 - 0.07)
      return -m_player->GetRightXZ();
    break;
  case (MoveDir::forw):
    if (XMVectorGetX(XMVector3AngleBetweenNormals(m_player->GetDirection(), m_player->GetForwardXZ())) < XM_PIDIV2 - 0.07)
      return m_player->GetRightXZ();
    break;
  case (MoveDir::left):
    return Y_POS;
  case (MoveDir::right):
    return -Y_POS;
  case (MoveDir::forwright):
    return sqrt2 * (m_player->GetRightXZ() - Y_POS);
  case (MoveDir::backright):
    return sqrt2 * (- m_player->GetRightXZ() - Y_POS);
  case (MoveDir::forwleft):
    return sqrt2 * (m_player->GetRightXZ() + Y_POS);
  case (MoveDir::backleft):
    return sqrt2 * (-m_player->GetRightXZ() + Y_POS);
  }
  return XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
}

void Controller::MovePlayer(double dt)
{
  XMVECTOR movement = GetPlayerTranslation() * Player::MOVEMENT_SPEED * dt;

  BoundingBox testBox = m_player->GetBoundingBox();
  testBox.Center.x += XMVectorGetX(movement);
  float maxOffset = 0.0f;
  for (auto& block : m_world->GetBlocks())
  {
    float offset = CollisionDetector::ResolveX(testBox, block->GetBoundingBox());
    if (offset > 0.0f && offset > maxOffset)
    {
      maxOffset = offset;
    }
  }
  testBox.Center.x += XMVectorGetX(movement) > 0 ? -maxOffset : maxOffset;

  testBox.Center.z += XMVectorGetZ(movement);
  maxOffset = 0.0f;
  for (auto& block : m_world->GetBlocks())
  {
    float offset = CollisionDetector::ResolveZ(testBox, block->GetBoundingBox());
    if (offset > 0.0f && offset > maxOffset)
    {
      maxOffset = offset;
    }
  }
  testBox.Center.z += XMVectorGetZ(movement) > 0 ? -maxOffset : maxOffset;

  XMVECTOR newLocation = XMLoadFloat3(&testBox.Center);

  if (m_keyboard->JumpInQueue())
    m_player->jump();

  if (m_player->getDroppingVelocity() >= 0.0f)
  {
    m_player->drop();
    for (auto& block : m_world->GetBlocks())
    {
      XMVECTOR blockL = block->GetLocation();
      if (floorf(XMVectorGetX(blockL) == floorf(XMVectorGetX(newLocation))) &&
          floorf(XMVectorGetZ(blockL) == floorf(XMVectorGetZ(newLocation))) &&
          (-floorf(XMVectorGetY(blockL)) + (XMVectorGetY(newLocation) - 2.0f) < 0.01f))
      {
        m_player->setOnGround();
        break;
      }
    }
  }

  if (!m_player->onGround())
  {
    m_player->addDroppingVelocity(dt);
    XMVECTOR drop = { 0.0f, -m_player->getDroppingVelocity() * dt, 0.0f, 0.0f };
    newLocation += drop;
  }
  m_player->SetLocation(newLocation);

  XMVECTOR rotation = GetPlayerRotation() * Player::ROTATION_SPEED * dt;

  m_player->SetDirection(XMVector3Transform(m_player->GetDirection(), XMMatrixRotationRollPitchYawFromVector(rotation)));
  m_player->SetUp(XMVector3Transform(m_player->GetUp(), XMMatrixRotationRollPitchYawFromVector(rotation)));
}
