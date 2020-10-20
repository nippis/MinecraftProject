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
  int z = -8;
  for (int x = -WORLD_SIZE / 2; x < WORLD_SIZE / 2; x++)
  {
    z++;
    for (int y = -WORLD_SIZE / 2; y < WORLD_SIZE / 2; y++)
    {
      DirectX::XMVECTOR newCoords = { x, y, z, 0.0 };
      std::shared_ptr<Block> newBlock = std::make_shared<Dirt>(newCoords);
      m_blocks.push_back(newBlock);
    }
  }
  return m_blocks.size();
}
