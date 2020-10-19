#pragma once

struct BlockCoord
{
  int x, y, z;
};

struct BlockColor
{
  float r, g, b;
};

class Block
{
protected:
  Block(BlockCoord location, BlockColor color);

public:
  virtual ~Block();

  virtual bool Break();

  BlockCoord GetLocation();
  BlockColor GetColor();

private:
  BlockCoord m_location;
  BlockColor m_color;
};

