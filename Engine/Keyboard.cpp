#include "Keyboard.h"

Keyboard::Keyboard() : m_jumpInQueue(false)
{
}

void Keyboard::SetState(UINT message, WPARAM keycode)
{
  if (message == WM_KEYDOWN)
  {
    if (m_keyStates.find(keycode) == m_keyStates.end())
      m_keyStates.insert({ keycode, true });
    else
      m_keyStates.at(keycode) = true;
    if (keycode == KEY_JUMP)
      m_jumpInQueue = true;
  }
  else if (message == WM_KEYUP)
  {
    m_keyStates.at(keycode) = false;
  }
}

bool Keyboard::IsPressed(WPARAM keycode)
{
  if (m_keyStates.find(keycode) == m_keyStates.end())
    return false;
  return m_keyStates.at(keycode);
}

bool Keyboard::JumpInQueue()
{
  if (m_jumpInQueue)
  {
    m_jumpInQueue = false;
    return true;
  }
  else 
  {
    return false;
  }
}
