#pragma once

#include "Block.h"

class Trunk :
  public Block
{
public:
  Trunk(DirectX::XMVECTOR location);

  bool Break();

};

