#include "Stone.h"

Stone::Stone(DirectX::XMVECTOR location) : Block(location, { 0.3f, 0.3f, 0.3f, 1.0f})
{
}

bool Stone::Break()
{
  return false;
}
