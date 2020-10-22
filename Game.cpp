#include "Game.h"

Game::Game(HWND hWnd, std::shared_ptr<Keyboard> keyboard) :
  m_timer(std::make_shared<Timer>()),
  m_keyboard(keyboard),
  m_cDetector(std::make_shared<CollisionDetector>()),
  m_world(std::make_shared<World>())
{
  m_player = std::make_shared<Player>(m_timer);
  m_graphics = std::make_shared<GraphicsEngine>(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, m_world, m_player);
}

void Game::run(MSG *msg)
{
  // reset (start) the timer
  m_timer->reset();

  while (true)
  {

    if (PeekMessage(msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(msg);
      DispatchMessage(msg);

      if ((*msg).message == WM_QUIT)
        break;
    }

    m_timer->tick();

    // compute fps
    calculateFrameStatistics();

    MoveDir direction = MovementDirection();
    MoveDir rotation = RotationDirection();

    bool onGround = false;
    for (std::shared_ptr<Block> block : (m_world->GetBlocks()))
    {
      if (m_cDetector->CollideY(m_player, block))
      {
        onGround = true;
        break;
      }
    }
    if (!onGround)
    {
      m_player->Drop();
    }
    else
    {
      m_player->Stop();
    }

    if (m_keyboard->JumpInQueue())
      m_player->Jump();

    // now update the game logic based on the input and the elapsed time since the last frame
    if (direction != MoveDir::none || rotation != MoveDir::none)
      update(m_timer->getDeltaTime(), direction, rotation);

    // generate output
    m_graphics->RenderFrame();
  }
}

void Game::calculateFrameStatistics()
{
  static int nFrames;				    // number of frames seen
  static double elapsedTime;		    // time since last call
  nFrames++;

  // compute average statistics over one second
  if ((m_timer->getTotalTime() - elapsedTime) >= 1.0)
  {
    // set fps and mspf
    m_fps = nFrames;
    m_mspf = 1000.0 / (double)m_fps;

    // reset
    nFrames = 0;
    elapsedTime += 1.0;
  }
}

MoveDir Game::MovementDirection()
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

  return direction;
}

MoveDir Game::RotationDirection()
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

  return direction;
}

void Game::update(double dt, MoveDir direction, MoveDir rotdirection)
{
  XMVECTOR movement = { 0.0, 0.0, 0.0, 0.0 };
  XMVECTOR rotation = { 0.0, 0.0, 0.0, 0.0 };
  switch (direction)
  {
    case (MoveDir::back):
      movement = -m_graphics->GetCamForward();
      break;
    case (MoveDir::right):
      movement = -m_graphics->GetCamLeft();
      break;
    case (MoveDir::forw):
      movement = m_graphics->GetCamForward();
      break;
    case (MoveDir::left):
      movement = m_graphics->GetCamLeft();
      break;
    case (MoveDir::backright):
      movement = { -0.707f, 0.707f, 0.0f, 0.0f };
      break;
    case (MoveDir::forwright):
      movement = { 0.707f, 0.707f, 0.0f, 0.0f };
      break;
    case (MoveDir::backleft):
      movement = { -0.707f, -0.707f, 0.0f, 0.0f };
      break;
    case (MoveDir::forwleft):
      movement = { 0.707f, -0.707f, 0.0f, 0.0f };
      break;
  }

  switch (rotdirection)
  {
    case (MoveDir::back):
      rotation = { 0.0f, -1.0f, 0.0f, 0.0f };
      break;
    case (MoveDir::right):
      rotation = { 0.0f, 0.0f, 1.0f, 0.0f };
      break;
    case (MoveDir::forw):
      rotation = { 0.0f, 1.0f, 0.0f, 0.0f };
      break;
    case (MoveDir::left):
      rotation = { 0.0f, 0.0f, -1.0f, 0.0f };
      break;
    case (MoveDir::backright):
      rotation = { -0.707f, 0.707f, 0.0f, 0.0f };
      break;
    case (MoveDir::forwright):
      rotation = { 0.707f, 0.707f, 0.0f, 0.0f };
      break;
    case (MoveDir::backleft):
      rotation = { -0.707f, -0.707f, 0.0f, 0.0f };
      break;
    case (MoveDir::forwleft):
      rotation = { 0.707f, -0.707f, 0.0f, 0.0f };
      break;
  }
  m_player->Move(movement, dt);
  m_player->Rotate(rotation, dt);
}
