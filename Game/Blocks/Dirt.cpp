#include "Dirt.h"

Dirt::Dirt(BlockCoord location) : Block(location, {0.1f, 0.8f, 0.1f})
{
}

Dirt::~Dirt()
{
}

bool Dirt::Break()
{
  return true;
}
