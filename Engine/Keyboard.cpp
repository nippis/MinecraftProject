#include "Keyboard.h"

Keyboard::Keyboard() : m_jumpInQueue(false){}

void Keyboard::SetState(UINT message, WPARAM keycode)
{
  if (message == WM_KEYDOWN)
  {
    m_keyStates.set(keycode);
    if (keycode == KEY_JUMP)
      m_jumpInQueue = true;
  }
  else if (message == WM_KEYUP)
  {
    m_keyStates.reset(keycode);
  }
}

bool Keyboard::IsPressed(WPARAM keycode) const
{
  return m_keyStates.test(keycode);
}

bool Keyboard::JumpInQueue()
{
  if (m_jumpInQueue || IsPressed(KEY_JUMP))
  {
    m_jumpInQueue = false;
    return true;
  }
  return false;
}
