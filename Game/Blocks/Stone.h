#pragma once

#include "Block.h"

class Stone :
  public Block
{
public:
  Stone(DirectX::XMVECTOR location);
  virtual ~Stone();

  bool Break();
};

