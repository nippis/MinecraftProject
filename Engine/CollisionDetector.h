#pragma once

#include <memory>
#include "Engine/Entity.h"

class CollisionDetector
{
public:
  CollisionDetector();

  XMVECTOR ResolveX(BoundingBox& entity1, BoundingBox& entity2);
  XMVECTOR ResolveZ(BoundingBox& entity1, BoundingBox& entity2);

  bool Collide(BoundingBox& entity1, BoundingBox& entity2) const;
};

