#include "CollisionDetector.h"

CollisionDetector::CollisionDetector(std::shared_ptr<World> world) :
  m_world(world)
{
}

XMVECTOR CollisionDetector::ResolveX(BoundingBox entity)
{
  return XMLoadFloat3(&entity.Center);
}

XMVECTOR CollisionDetector::ResolveZ(BoundingBox entity)
{
    return XMLoadFloat3(&entity.Center);
}

bool CollisionDetector::Collide(const BoundingBox& entity1, const BoundingBox& entity2) const
{
  return entity1.Intersects(entity2);
}
