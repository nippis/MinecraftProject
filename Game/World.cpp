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
    for (auto block : m_blocks)
    {
        XMVectorEqualR(&CR, block->GetLocation(), floatCoords);
        if (XMComparisonAllTrue(CR))
            return block;
    }
    return std::shared_ptr<Block>();
}

void World::BreakBlock(std::shared_ptr<Block> block)
{
    m_blocks.erase(std::find(m_blocks.begin(), m_blocks.end(), block));
}

int World::CreateTerrain()
{
  int z = 0;
  for (int x = -WORLD_SIZE / 2; x < WORLD_SIZE / 2; x++)
  {
    for (int y = -WORLD_SIZE / 2; y < WORLD_SIZE / 2; y++)
    {
      if ((x == -WORLD_SIZE / 2) || (x == WORLD_SIZE / 2 - 1) ||
          (y == -WORLD_SIZE / 2) || (y == WORLD_SIZE / 2 - 1) ||
          (x == 0 && y == 0) || (x == 1 && y == 0) ||
          (x == 0 && y == 1) || (x == 1 && y == 1) ||
          (x == 2 && y == 2))
        z = 1;
      else
          z = 0;
      DirectX::XMVECTOR newCoords = { x, y, z, 0.0 };
      std::shared_ptr<Block> newBlock = std::make_shared<Dirt>(newCoords);
      m_blocks.push_back(newBlock);
    }
  }
  return m_blocks.size();
}
