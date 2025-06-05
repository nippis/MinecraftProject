#pragma once

#include <Windows.h>
#include <bitset>

constexpr unsigned int KEY_LEFT = 'A';
constexpr unsigned int KEY_FORW = 'W';
constexpr unsigned int KEY_RIGHT = 'D';
constexpr unsigned int KEY_BACK = 'S';

constexpr unsigned int KEY_YAW_LEFT = VK_LEFT;
constexpr unsigned int KEY_PITCH_UP = VK_UP;
constexpr unsigned int KEY_YAW_RIGHT = VK_RIGHT;
constexpr unsigned int KEY_PITCH_DOWN = VK_DOWN;

constexpr unsigned int KEY_JUMP = VK_SPACE;

#define KEY_MOUSE_CONTROL 'M'
#define KEY_KEYB_CONTROL 'K'

class Keyboard
{
public:
  Keyboard();

  void SetState(UINT message, WPARAM keycode);
  bool IsPressed(WPARAM keycode) const;
  bool JumpInQueue();

private:
  std::bitset<0xFF> m_keyStates;
  bool m_jumpInQueue;
};

