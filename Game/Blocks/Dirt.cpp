#include "Dirt.h"

Dirt::Dirt(DirectX::XMVECTOR location) : Block(location, {0.1f, XMVectorGetX(location)/16*0.6f, XMVectorGetY(location) / 16 * 0.6f, 1.0f})
{
}

Dirt::~Dirt()
{
}

bool Dirt::Break()
{
  return true;
}
