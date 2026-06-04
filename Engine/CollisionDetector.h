#pragma once

#include <memory>
#include "Engine/Entity.h"

class World;

class CollisionDetector
{
public:
  CollisionDetector(std::shared_ptr<World> world);

  XMVECTOR ResolveX(BoundingBox entity);
  XMVECTOR ResolveZ(BoundingBox entity);

  bool Collide(const BoundingBox& entity1, const BoundingBox& entity2) const;

private:
  std::shared_ptr<World> m_world;
};

