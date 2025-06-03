#include "Controller.h"
#include <ranges>
#include <algorithm>

Controller::Controller(std::shared_ptr<Keyboard> keyboard, 
                       std::shared_ptr<Mouse> mouse, 
                       std::shared_ptr<GraphicsEngine> graphics, 
                       std::shared_ptr<Player> player,
                       std::shared_ptr<World> world) :
  m_keyboard(keyboard), m_mouse(mouse), m_player(player), m_graphics(graphics), m_world(world),
  m_collisionDetector(std::make_shared<CollisionDetector>()), m_mouseControl(false)
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
      return m_player->GetRightXZ();
    break;
  case (MoveDir::forw):
    if (XMVectorGetX(XMVector3AngleBetweenNormals(m_player->GetDirection(), m_player->GetForwardXZ())) < XM_PIDIV2 - 0.07)
      return -m_player->GetRightXZ();
    break;
  case (MoveDir::left):
    return { 0.0f, 1.0f, 0.0f, 0.0f };
  case (MoveDir::right):
    return { 0.0f, -1.0f, 0.0f, 0.0f };
  case (MoveDir::backright):
    return m_player->GetRightXZ() * 0.707f + XMVectorSet(0.0f, 0.0f, 0.707f, 1.0f);
  case (MoveDir::forwright):
    return -m_player->GetRightXZ() * 0.707f + XMVectorSet(0.0f, 0.0f, 0.707f, 1.0f);
  case (MoveDir::backleft):
    return m_player->GetRightXZ() * 0.707f + XMVectorSet(0.0f, 0.0f, -0.707f, 1.0f);
  case (MoveDir::forwleft):
    return -m_player->GetRightXZ() * 0.707f + XMVectorSet(0.0f, 0.0f, -0.707f, 1.0f);
  }
  return XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
}

XMVECTOR Controller::GetPlayerRotationFromMouse() const
{
  POINT cursorPos;
  GetCursorPos(&cursorPos);
  float yaw = XMConvertToRadians(cursorPos.x * 0.1f);
  float pitch = XMConvertToRadians(cursorPos.y * 0.1f);
  XMVECTOR rotation = XMVectorSet(0.0f, yaw, pitch, 0.0f);
  SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // Reset cursor position to centerm
  return rotation;
}

void Controller::MovePlayer(double dt)
{
  if (m_keyboard->IsPressed(KEY_MOUSE_CONTROL))
  {
    m_mouseControl = true;
  }
  else if (m_keyboard->IsPressed(KEY_KEYB_CONTROL))
  {
    m_mouseControl = false;
  }
  XMVECTOR movement = GetPlayerTranslation();
  XMVECTOR rotation;
  if (m_mouseControl)
    rotation = GetPlayerRotationFromMouse();
  else
    rotation = GetPlayerRotation();

  // Törmäystarkastelu seinien ja maan kanssa
  bool onGround = true;

  /*for (std::shared_ptr<Block> block : (m_world->GetBlocks()))
  {
    XMVECTOR collidingNormal = m_collisionDetector->GetCollidingNormal(m_player, block);
    if (XMVector4Equal(collidingNormal,XMVectorZero()))
      continue;
    movement = m_collisionDetector->GetUnblockedDirection(movement, collidingNormal);
    if (XMVector4Equal(collidingNormal, XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)))
        onGround = true;
  }
  if (!onGround && !m_player->IsDropping())
  {
    m_player->Drop();
  }
  else if (m_player->IsDropping())
  {
    m_player->Stop();
  }
  else
  {

  }
  // Tuplahyppyjen estämiseksi tämän voi siirtää tuohon yläpuolelle
  if (m_keyboard->JumpInQueue())
    m_player->Jump();
  */
  m_player->Move(movement, dt);
  m_player->Rotate(rotation, dt);
}
