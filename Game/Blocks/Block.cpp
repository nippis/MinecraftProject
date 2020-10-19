#include "Block.h"

Block::Block(BlockCoord location, BlockColor color) :
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

BlockColor Block::GetColor()
{
  return m_color;
}
