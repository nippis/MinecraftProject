#include "World.h"
#include "Blocks/Dirt.h"
#include "Blocks/Stone.h"
#include "Blocks/Trunk.h"

World::World()
{
  m_blocks = std::vector<std::shared_ptr<Block>>();
  CreateTerrain();
}

std::vector<std::shared_ptr<Block>>& World::GetBlocks()
{
  return m_blocks;
}

std::shared_ptr<Block> World::GetBlock(int x, int y, int z) const
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
      y = z > 0 ? (x + 2 * z) / 2 / 7 % 2 : (x + z / 5) / 2 / 7 % 2;
      XMVECTOR newCoords = { x, y, z, 0.0 };
      if (y >= 0) m_blocks.push_back(std::make_shared<Dirt>(newCoords));
      else m_blocks.push_back(std::make_shared<Stone>(newCoords));
    }
  }
  CreateTree();
  return m_blocks.size();
}

int World::GetGroundLevel(int x, int z)
{
  float maxy = -100.0f;
  for (auto& block : m_blocks)
  {
    float y = XMVectorGetY(block->GetLocation());
    if (y > maxy)
      maxy = y;
  }
  return (int)ceilf(maxy);
}

void World::CreateTree()
{
  int x = 10;
  int z = 10;
  int y = GetGroundLevel(x, z);
  for (int i = 0; i < 5; i++)
  {
    XMVECTOR coords = { x, y + i, z, 0.0f };
    m_blocks.push_back(std::make_shared<Trunk>(coords));
  }
}
