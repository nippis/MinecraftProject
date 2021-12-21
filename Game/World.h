#pragma once

#include <vector>
#include <memory>

#include "Blocks/Dirt.h"
#include "Blocks/Stone.h"

const int WORLD_SIZE = 16;

class World
{
public:
  World();
  ~World() = default;

  std::vector<std::shared_ptr<Block>> GetBlocks();
  std::shared_ptr<Block> GetBlock(int x, int y, int z);
  void BreakBlock(std::shared_ptr<Block> block);

private:
  int CreateTerrain();

  std::vector<std::shared_ptr<Block>> m_blocks;
};

