#pragma once

#include <Windows.h>
#include <unordered_map>

#define KEY_LEFT    VK_LEFT
#define KEY_FORW    VK_UP
#define KEY_RIGHT   VK_RIGHT
#define KEY_BACK    VK_DOWN

class Keyboard
{
public:
  Keyboard();
  ~Keyboard() = default;

  void SetState(UINT message, WPARAM keycode);
  bool IsPressed(WPARAM keycode);

private:
  std::unordered_map<WPARAM, bool> m_keyStates;
};

