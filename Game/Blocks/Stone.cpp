#include "Stone.h"

Stone::Stone(DirectX::XMVECTOR location) : Block(location, { 0.3f, 0.3f, 0.3f, 1.0f})
{
}

Stone::~Stone()
{
}

bool Stone::Break()
{
  return false;
}
