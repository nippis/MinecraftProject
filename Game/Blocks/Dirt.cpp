#include "Dirt.h"

Dirt::Dirt(BlockCoord location) : Block(location, {0.1f, 0.6f, 0.1f, 1.0f})
{
}

Dirt::~Dirt()
{
}

bool Dirt::Break()
{
  return true;
}
