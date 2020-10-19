#pragma once

#include <memory>


#include "Engine/GraphicsEngine.h"
#include "Game/Player.h"
#include "Engine/Keyboard.h"
#include "Timer.h"

class Game
{
public:
  Game(HWND hWnd, std::shared_ptr<Keyboard> keyboard);
  virtual ~Game() = default;

  void run(MSG *msg);

private:

  void calculateFrameStatistics();	// computes fps and spf

  std::shared_ptr<GraphicsEngine> m_graphics;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<Keyboard> m_keyboard;

  // timer
  std::shared_ptr<Timer> m_timer;					// high-precision timer
  int m_fps;							// frames per second
  double m_mspf;					    // milliseconds per frame

  virtual void update(double dt);
};
