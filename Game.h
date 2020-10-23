#pragma once

#include <memory>


#include "Engine/Graphics/GraphicsEngine.h"
#include "Game/Player.h"
#include "Engine/Keyboard.h"
#include "Engine/Timer.h"
#include "Engine/CollisionDetector.h"
#include "Engine/Controller.h"

class Game
{
public:
  Game(HWND hWnd, std::shared_ptr<Keyboard> keyboard);
  virtual ~Game() = default;

  void run(MSG *msg);

private:

  void calculateFrameStatistics();	// computes fps and spf

  std::shared_ptr<World> m_world;

  std::shared_ptr<GraphicsEngine> m_graphics;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<Keyboard> m_keyboard;
  std::shared_ptr<CollisionDetector> m_cDetector;
  std::shared_ptr<Controller> m_playerController;

  // timer
  std::shared_ptr<Timer> m_timer;					// high-precision timer
  int m_fps;							// frames per second
  double m_mspf;					    // milliseconds per frame

};

