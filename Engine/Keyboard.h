#pragma once

#include <Windows.h>
#include <unordered_map>

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

