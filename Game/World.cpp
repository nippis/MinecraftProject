#include <cmath>
#include <vector>
#include <ranges>

#include "World.h"
#include "Blocks/Dirt.h"
#include "Blocks/Stone.h"
#include "Blocks/Trunk.h"

namespace NOISE
{
  float Random(int x, int y)
  {
    int n = x + y * 57;
    n = (n << 13) ^ n;

    return 1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f;
  }

  float Smooth(float t)
  {
    return t * t * (3.0f - 2.0f * t);
  }

  float Lerp(float a, float b, float t)
  {
    return a + t * (b - a);
  }

  float Noise(float x, float y)
  {
    int x0 = static_cast<int>(std::floor(x));
    int y0 = static_cast<int>(std::floor(y));

    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float sx = Smooth(x - x0);
    float sy = Smooth(y - y0);

    float n00 = Random(x0, y0);
    float n10 = Random(x1, y0);
    float n01 = Random(x0, y1);
    float n11 = Random(x1, y1);

    float ix0 = Lerp(n00, n10, sx);
    float ix1 = Lerp(n01, n11, sx);

    return Lerp(ix0, ix1, sy);
  }

  float TerrainNoise(float x, float y)
  {
    float total = 0.0f;
    float amplitude = 1.0f;
    float frequency = 0.01f;

    constexpr int octaves = 5;

    for (int i = 0; i < octaves; ++i)
    {
      total += amplitude * Noise(x * frequency, y * frequency); 
      amplitude *= 0.5f;
      frequency *= 2.0f;
    }

    return total;
  }
}

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
      float h = NOISE::TerrainNoise(static_cast<float>(x), static_cast<float>(z));
      y = (int)floorf(h * 20.0f);
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
  float maxy = -1000.0f;
  for (auto& block : m_blocks | std::views::filter([&](auto block)
  {return XMVectorGetX(block->GetLocation()) == x && XMVectorGetZ(block->GetLocation()) == z;}))
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
