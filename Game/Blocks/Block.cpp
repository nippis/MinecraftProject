#include "Block.h"

Block::Block(DirectX::XMVECTOR location, DirectX::XMFLOAT4 color) :
  Entity(location),  m_color(color)
{

}

Block::~Block()
{
}

bool Block::Break()
{
  return true;
}

DirectX::XMFLOAT4 Block::GetColor()
{
  return m_color;
}
