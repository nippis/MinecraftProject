#pragma once

#include <DirectXMath.h>
#include "Game/Entity.h"

class Block :
  public Entity
{
protected:
  Block(DirectX::XMVECTOR location, DirectX::XMFLOAT4 color);

public:
  virtual ~Block();

  virtual bool Break();

  DirectX::XMFLOAT4 GetColor();

private:
  DirectX::XMFLOAT4 m_color;
};

