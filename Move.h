#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Move
{
public:
  Move();
  Move(XMVECTOR location, XMVECTOR rotation);
  ~Move();



private:
  XMVECTOR m_location;
  XMVECTOR m_rotation;
};

