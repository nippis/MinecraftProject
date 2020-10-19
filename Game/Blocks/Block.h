#pragma once

#include <DirectXMath.h>

struct BlockCoord
{
  int x, y, z;
};

class Block
{
protected:
  Block(BlockCoord location, DirectX::XMFLOAT4 color);

public:
  virtual ~Block();

  virtual bool Break();

  BlockCoord GetLocation();
  DirectX::XMFLOAT4 GetColor();

private:
  BlockCoord m_location;
  DirectX::XMFLOAT4 m_color;
};

