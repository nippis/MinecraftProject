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
  // Singleton accessor
  static std::shared_ptr<Game> Instance(HWND hWnd = nullptr)
  {
    if (!m_instance)
      m_instance = std::make_shared<Game>(hWnd);
    return m_instance;
  }

  // Delete copy/move constructors and assignment operators
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  std::shared_ptr<Keyboard> getKeyboard() const { return m_keyboard; }

  virtual ~Game() = default;

  void run(MSG *msg);

private:
  Game(HWND hWnd);

  void calculateFrameStatistics();	// computes fps and spf

  static std::shared_ptr<Game> m_instance;	// singleton instance
  std::shared_ptr<World> m_world;

  std::shared_ptr<GraphicsEngine> m_graphics;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<Keyboard> m_keyboard;
  std::shared_ptr<Controller> m_playerController;

  // timer
  std::shared_ptr<Timer> m_timer;					// high-precision timer
  int m_fps = 0;							// frames per second
  double m_mspf = 0;					    // milliseconds per frame
};
