#pragma once

#include "Game/Entity.h"

class CollisionDetector
{
public:
  CollisionDetector();
  ~CollisionDetector();

  DirectX::XMVECTOR GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);
  DirectX::XMVECTOR GetUnblockedDirection(DirectX::XMVECTOR dir, DirectX::XMVECTOR blockerNormal);

  bool Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);
};

