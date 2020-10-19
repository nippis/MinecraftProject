#pragma once

#include "Block.h"

class Dirt:
  public Block
{
public:
  Dirt(DirectX::XMVECTOR location);
  virtual ~Dirt();

  bool Break();

};

