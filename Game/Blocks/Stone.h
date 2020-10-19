#pragma once

#include "Block.h"

class Stone :
  public Block
{
public:
  Stone(BlockCoord location);
  virtual ~Stone();

  bool Break();
};

