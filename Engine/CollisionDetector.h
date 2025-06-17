#pragma once

#include <memory>
#include "Engine/Entity.h"

class CollisionDetector
{
public:
  CollisionDetector();

  XMVECTOR GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const;
  XMVECTOR GetUnblockedDirection(XMVECTOR dir, XMVECTOR blockerNormal) const;

  bool Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const;
};

