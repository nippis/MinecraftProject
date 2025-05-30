#include "Game.h"

Game::Game(HWND hWnd)
{
  m_world = std::make_shared<World>();
  m_timer = std::make_shared<Timer>();
  m_player = std::make_shared<Player>(m_timer);
  m_graphics = std::make_shared<GraphicsEngine>(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, m_world, m_player);
  m_playerController = std::make_shared<Controller>(m_keyboard, nullptr, m_graphics, m_player, m_world);
  m_keyboard = std::make_shared<Keyboard>();
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

    // now update the game logic based on the input and the elapsed time since the last frame
    m_playerController->MovePlayer(m_timer->getDeltaTime());

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

