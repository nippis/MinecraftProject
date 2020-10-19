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

      BlockCoord newCoords = { x, y, z };
      std::shared_ptr<Dirt> newBlock = std::make_shared<Dirt>(newCoords);
      m_blocks->push_back(newBlock);
    }
  }

  return m_blocks->size();
}
