#include "Dirt.h"

Dirt::Dirt(DirectX::XMVECTOR location) : Block(location, {0.1f, 0.6f, 0.6f, 1.0f})
{
}

bool Dirt::Break()
{
  return true;
}
