#include "World.h"

World::World()
{
  m_blocks = std::vector<std::shared_ptr<Block>>();
  CreateTerrain();
}

std::vector<std::shared_ptr<Block>>& World::GetBlocks()
{
  return m_blocks;
}

std::shared_ptr<Block> World::GetBlock(int x, int y, int z)
{
    uint32_t CR = 0;
    XMVECTOR floatCoords = { static_cast<float>(x), static_cast<float>(y) ,static_cast<float>(z), 0.0 };
    for (auto& block : m_blocks)
    {
        if (XMVector3Equal(block->GetLocation(), floatCoords))
            return block;
    }
    return nullptr;
}

void World::BreakBlock(std::shared_ptr<Block> block)
{
    m_blocks.erase(std::find(m_blocks.begin(), m_blocks.end(), block));
}

int World::CreateTerrain()
{
  int y = 0;
  for (int x = -WORLD_SIZE / 2; x < WORLD_SIZE / 2; x++)
  {
    for (int z = -WORLD_SIZE / 2; z < WORLD_SIZE / 2; z++)
    {
      XMVECTOR newCoords = { x, y, z, 0.0 };
      auto block = std::make_shared<Dirt>(newCoords);
      m_blocks.push_back(block);
    }
  }
  return m_blocks.size();
}
