#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
}

XMVECTOR CollisionDetector::ResolveX(BoundingBox& entity1, BoundingBox& entity2)
{
  return XMVECTOR();
}

XMVECTOR CollisionDetector::ResolveZ(BoundingBox& entity1, BoundingBox& entity2)
{
    return XMVECTOR();
}

bool CollisionDetector::Collide(BoundingBox& entity1, BoundingBox& entity2) const
{
  return entity1.Intersects(entity2);
}
