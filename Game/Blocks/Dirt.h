#pragma once

#include "Block.h"

class Dirt:
  public Block
{
public:
  Dirt(BlockCoord location);
  virtual ~Dirt();

  bool Break();

};

