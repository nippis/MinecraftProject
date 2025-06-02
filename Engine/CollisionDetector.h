#pragma once

#include "Game/Entity.h"

constexpr DirectX::XMVECTOR X_POS{ 1.0, 0.0, 0.0, 0.0 };
constexpr DirectX::XMVECTOR Y_POS{ 0.0, 1.0, 0.0, 0.0 };
constexpr DirectX::XMVECTOR Z_POS{ 0.0, 0.0, 1.0, 0.0 };

class CollisionDetector
{
public:
  CollisionDetector();
  virtual ~CollisionDetector() = default;

  DirectX::XMVECTOR GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const;
  DirectX::XMVECTOR GetUnblockedDirection(DirectX::XMVECTOR dir, DirectX::XMVECTOR blockerNormal) const;

  bool Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const;
};

