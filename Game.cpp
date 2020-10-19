#include "Game.h"

Game::Game(HWND hWnd, std::shared_ptr<Keyboard> keyboard) :
  m_player(std::make_shared<Player>()),
  m_timer(std::make_shared<Timer>()),
  m_keyboard(keyboard)
{
  m_graphics = std::make_shared<GraphicsEngine>(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, m_player);
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

    // acquire input
    if (m_keyboard->IsPressed(VK_LEFT))
      m_graphics->UpdateVertexBuffer(1);
    if (m_keyboard->IsPressed(VK_UP))
      m_graphics->UpdateVertexBuffer(2);
    if (m_keyboard->IsPressed(VK_RIGHT))
      m_graphics->UpdateVertexBuffer(3);
    if (m_keyboard->IsPressed(VK_DOWN))
      m_graphics->UpdateVertexBuffer(4);
    if (m_keyboard->IsPressed(0x57))
      m_graphics->UpdateVertexBuffer(5);

    // now update the game logic based on the input and the elapsed time since the last frame
    update(m_timer->getDeltaTime());

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

void Game::update(double dt)
{
}
