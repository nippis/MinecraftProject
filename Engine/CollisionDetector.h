#pragma once

#include <memory>
#include "Engine/Entity.h"

class CollisionDetector
{
public:
  CollisionDetector();
  virtual ~CollisionDetector() = default;

  DirectX::XMVECTOR GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const;
  DirectX::XMVECTOR GetUnblockedDirection(DirectX::XMVECTOR dir, DirectX::XMVECTOR blockerNormal) const;

  bool Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const;
};

