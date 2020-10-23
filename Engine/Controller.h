#pragma once

#include "Game/Player.h"
#include "Engine/Keyboard.h"
#include "Engine/Mouse.h"
#include "Engine/Graphics/GraphicsEngine.h"

enum class MoveDir
{
  none,
  left,
  forwleft,
  forw,
  forwright,
  right,
  backright,
  back,
  backleft
};

class Controller
{
public:
  Controller(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Mouse> mouse, std::shared_ptr<GraphicsEngine> graphics, std::shared_ptr<Player> player);
  ~Controller();

  void MovePlayer(double dt);

private:
  MoveDir MovementDirection();
  MoveDir RotationDirection();

  std::shared_ptr<Keyboard> m_keyboard;
  std::shared_ptr<Mouse> m_mouse;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<GraphicsEngine> m_graphics;
};

