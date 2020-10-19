#pragma once

#include <vector>
#include <memory>

#include "Blocks/Dirt.h"

const int WORLD_SIZE = 16;

class World
{
public:
  World();
  ~World() = default;

  std::shared_ptr<std::vector<std::shared_ptr<Block>>> GetBlocks();

private:
  int CreateTerrain();

  std::shared_ptr<std::vector<std::shared_ptr<Block>>> m_blocks;
};

