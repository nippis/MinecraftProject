#pragma once

#include "Block.h"

class Leaf :
  public Block
{
public:
  Leaf(DirectX::XMVECTOR location);

  bool Break();

};

