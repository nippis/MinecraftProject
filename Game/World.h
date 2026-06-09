#pragma once

#include <vector>
#include <memory>

const int WORLD_SIZE = 64;

class Block;

class World
{
public:
  World();

  [[nodiscard]]
  std::vector<std::shared_ptr<Block>>& GetBlocks();
  [[nodiscard]]
  std::shared_ptr<Block> GetBlock(int x, int y, int z) const;
  void BreakBlock(std::shared_ptr<Block> block);

private:
  int CreateTerrain();

  float GetGroundLevel(int x, int z);

  void CreateTree(float x, float z);

  std::vector<std::shared_ptr<Block>> m_blocks;
};

