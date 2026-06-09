#include "Trunk.h"

Trunk::Trunk(DirectX::XMVECTOR location) : Block(location, { 0.4f, 0.3f, 0.1f, 1.0f })
{}

bool Trunk::Break()
{
  return true;
}
