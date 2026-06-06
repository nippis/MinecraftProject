#pragma once

#include "Engine/Player.h"
#include "Engine/Keyboard.h"
#include "Engine/Mouse.h"
#include "Engine/Graphics/GraphicsEngine.h"
#include "Game/World.h"
#include "Engine/CollisionDetector.h"

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
  Controller(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Mouse> mouse, std::shared_ptr<GraphicsEngine> graphics, std::shared_ptr<Player> player, std::shared_ptr<World> world);
  ~Controller();

  void MovePlayer(double dt);

private:
  [[nodiscard]]
  MoveDir MovementDirection() const;
  [[nodiscard]]
  MoveDir RotationDirection() const;

  [[nodiscard]]
  XMVECTOR GetPlayerTranslation() const;
  [[nodiscard]]
  XMVECTOR GetPlayerRotation() const;

  std::shared_ptr<Keyboard> m_keyboard;
  std::shared_ptr<Mouse> m_mouse;
  std::shared_ptr<Player> m_player;
  std::shared_ptr<GraphicsEngine> m_graphics;
  std::shared_ptr<World> m_world;

  bool m_mouseControl;
};

