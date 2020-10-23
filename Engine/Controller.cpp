#include "Controller.h"

Controller::Controller(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Mouse> mouse, std::shared_ptr<GraphicsEngine> graphics, std::shared_ptr<Player> player) :
  m_keyboard(keyboard), m_mouse(mouse), m_player(player), m_graphics(graphics)
{

}

Controller::~Controller()
{
}

MoveDir Controller::MovementDirection()
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

MoveDir Controller::RotationDirection()
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

void Controller::MovePlayer(double dt)
{
  XMVECTOR movement = { 0.0, 0.0, 0.0, 0.0 };
  XMVECTOR rotation = { 0.0, 0.0, 0.0, 0.0 };
  switch (MovementDirection())
  {
    case (MoveDir::back):
      movement = -m_player->GetForward();
      break;
    case (MoveDir::right):
      movement = -m_player->GetLeft();
      break;
    case (MoveDir::forw):
      movement = m_player->GetForward();
      break;
    case (MoveDir::left):
      movement = m_player->GetLeft();
      break;
    case (MoveDir::backright):
      movement = 0.707 * (-m_player->GetForward() - m_player->GetLeft());
      break;
    case (MoveDir::forwright):
      movement = 0.707 * (m_player->GetForward() - m_player->GetLeft());
      break;
    case (MoveDir::backleft):
      movement = 0.707 * (-m_player->GetForward() + m_player->GetLeft());
      break;
    case (MoveDir::forwleft):
      movement = 0.707 * (m_player->GetForward() + m_player->GetLeft());
      break;
  }

  switch (RotationDirection())
  {
    case (MoveDir::back):
      if (XMVectorGetX(XMVector4AngleBetweenNormals(m_player->GetRotation(), m_player->GetForward())) < XM_PIDIV2-0.07 ||
          XMVectorGetZ(m_player->GetRotation()) >= 0.0f)
        rotation = -m_player->GetLeft();
      break;
    case (MoveDir::right):
      rotation = { 0.0f, 0.0f, 1.0f, 0.0f };
      break;
    case (MoveDir::forw):
      if (XMVectorGetX(XMVector4AngleBetweenNormals(m_player->GetRotation(), m_player->GetForward())) < XM_PIDIV2-0.07 ||
          XMVectorGetZ(m_player->GetRotation()) <= 0.0f)
        rotation = m_player->GetLeft();
      break;
    case (MoveDir::left):
      rotation = { 0.0f, 0.0f, -1.0f, 0.0f };
      break;
    case (MoveDir::backright):
      rotation = -m_player->GetLeft() * 0.707f + XMVectorSet( 0.0f, 0.0f, 0.707f, 0.0f );
      break;
    case (MoveDir::forwright):
      rotation = m_player->GetLeft() * 0.707f + XMVectorSet(0.0f, 0.0f, 0.707f, 0.0f);
      break;
    case (MoveDir::backleft):
      rotation = -m_player->GetLeft() * 0.707f + XMVectorSet(0.0f, 0.0f, -0.707f, 0.0f);
      break;
    case (MoveDir::forwleft):
      rotation = m_player->GetLeft() * 0.707f + XMVectorSet(0.0f, 0.0f, -0.707f, 0.0f);
      break;
  }

  m_player->Move(movement, dt);
  m_player->Rotate(rotation, dt);
}
