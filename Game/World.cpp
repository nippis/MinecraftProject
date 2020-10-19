#include "World.h"

World::World()
{
  m_blocks = std::make_shared<std::vector<std::shared_ptr<Block>>>();
  CreateTerrain();
}

std::shared_ptr<std::vector<std::shared_ptr<Block>>> World::GetBlocks()
{
  return m_blocks;
}

int World::CreateTerrain()
{
  for (int x = -WORLD_SIZE / 2; x < WORLD_SIZE / 2; x++)
  {
    for (int y = -WORLD_SIZE / 2; y < WORLD_SIZE / 2; y++)
    {
      int z = 0;

      DirectX::XMVECTOR newCoords = { x, y, z, 0.0};
      std::shared_ptr<Block> newBlock = std::make_shared<Dirt>(newCoords);
      m_blocks->push_back(newBlock);
    }
  }

  for (int x = -WORLD_SIZE / 2; x < WORLD_SIZE / 2; x++)
  {
    for (int y = -WORLD_SIZE / 2; y < WORLD_SIZE / 2; y++)
    {
      int z = -1;

      DirectX::XMVECTOR newCoords = { x, y, z, 0.0 };
      std::shared_ptr<Block> newBlock2 = std::make_shared<Stone>(newCoords);
      m_blocks->push_back(newBlock2);
    }
  }

  return m_blocks->size();
}
