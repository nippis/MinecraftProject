#pragma once

#include "Block.h"

class Stone :
  public Block
{
public:
  Stone(DirectX::XMVECTOR location);

  bool Break();
};

