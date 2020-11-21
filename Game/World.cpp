#include "World.h"

World::World()
{
  m_blocks = std::vector<std::shared_ptr<Block>>();
  CreateTerrain();
}

std::vector<std::shared_ptr<Block>> World::GetBlocks()
{
  return m_blocks;
}

int World::CreateTerrain()
{
  int z = 0;
  for (int x = -WORLD_SIZE / 2; x < WORLD_SIZE / 2; x++)
  {
    for (int y = -WORLD_SIZE / 2; y < WORLD_SIZE / 2; y++)
    {
      z = 2 * XMScalarSin(x * XMScalarCos(x/4)/ 5) + 2 * XMScalarSin(y * XMScalarCos(x / 3) / 5);
      DirectX::XMVECTOR newCoords = { x, y, z, 0.0 };
      std::shared_ptr<Block> newBlock = std::make_shared<Dirt>(newCoords);
      m_blocks.push_back(newBlock);
     //z = 2 * XMScalarSin(x / 5) + 2 * XMScalarSin(y / 5) - 1.0f;
     //DirectX::XMVECTOR newCoords2 = { x, y, z, 0.0 };
     //std::shared_ptr<Block> newBlock2 = std::make_shared<Dirt>(newCoords2);
     //m_blocks.push_back(newBlock2);
    }
  }
  return m_blocks.size();
}
