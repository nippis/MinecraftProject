#pragma once

#include <DirectXMath.h>
#include "Game/Entity.h"

class Block :
  public Entity
{
public:
  Block(DirectX::XMVECTOR location, DirectX::XMFLOAT4 color);
  virtual ~Block();

  virtual bool Break();

  DirectX::XMFLOAT4 GetColor();

protected:
  DirectX::XMFLOAT4 m_color;
};

