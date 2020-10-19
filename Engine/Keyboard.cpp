#include "Keyboard.h"

Keyboard::Keyboard()
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
