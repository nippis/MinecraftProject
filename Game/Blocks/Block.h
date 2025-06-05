#pragma once

#include <DirectXMath.h>
#include "Engine/Entity.h"

class Block :
  public Entity
{
public:
  Block(DirectX::XMVECTOR location, DirectX::XMFLOAT4 color);

  virtual bool Break();
  DirectX::XMFLOAT4 GetColor() const;

protected:
  DirectX::XMFLOAT4 m_color;
};

