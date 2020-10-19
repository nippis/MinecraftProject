#include "Stone.h"

Stone::Stone(BlockCoord location) : Block(location, { 0.3f, 0.3f, 0.3f, 1.0f})
{
}

Stone::~Stone()
{
}

bool Stone::Break()
{
  return false;
}
