#include "Block.h"

Block::Block(BlockCoord location, DirectX::XMFLOAT4 color) :
  m_location(location), m_color(color)
{

}

Block::~Block()
{
}

bool Block::Break()
{
  return true;
}

BlockCoord Block::GetLocation()
{
  return m_location;
}

DirectX::XMFLOAT4 Block::GetColor()
{
  return m_color;
}
