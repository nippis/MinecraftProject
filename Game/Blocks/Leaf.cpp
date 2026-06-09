#include "Leaf.h"

Leaf::Leaf(DirectX::XMVECTOR location) : Block(location, { 0.5f, 0.9f, 0.6f, 1.0f })
{}

bool Leaf::Break()
{
  return true;
}
