#pragma once

#include "Block.h"

class Dirt:
  public Block
{
public:
  Dirt(DirectX::XMVECTOR location);

  bool Break();

};

