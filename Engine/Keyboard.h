#pragma once

#include <Windows.h>
#include <bitset>

#define KEY_LEFT    0x41 // A
#define KEY_FORW    0x57 // W
#define KEY_RIGHT   0x44 // D
#define KEY_BACK    0x53 // S

#define KEY_YAW_LEFT    VK_LEFT 
#define KEY_PITCH_UP    VK_UP
#define KEY_YAW_RIGHT   VK_RIGHT 
#define KEY_PITCH_DOWN  VK_DOWN 

#define KEY_JUMP    VK_SPACE

class Keyboard
{
public:
  Keyboard();
  ~Keyboard() = default;

  void SetState(UINT message, WPARAM keycode);
  bool IsPressed(WPARAM keycode) const;
  bool JumpInQueue();

private:
  std::bitset<0xFF> m_keyStates;
  bool m_jumpInQueue;
};

