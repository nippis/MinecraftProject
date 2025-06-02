#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
}

XMVECTOR CollisionDetector::GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const
{
  if (!Collide(entity1, entity2))
    return XMVectorZero();
  XMVECTOR distance = XMVectorAbs(entity1->GetLocation() - entity2->GetLocation());
  if ((XMVectorGetZ(distance) > XMVectorGetX(distance)) && (XMVectorGetZ(distance) > XMVectorGetY(distance)))
    return Z_POS;
  else if (XMVectorGetY(distance) > XMVectorGetX(distance))
    return Y_POS;
  return X_POS;
}

XMVECTOR CollisionDetector::GetUnblockedDirection(XMVECTOR dir, XMVECTOR blockerNormal) const
{
  return (dir + XMVector4Reflect(dir, blockerNormal)) / 2.0f;
}

bool CollisionDetector::Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) const
{
  return entity1->GetBoundingBox().Intersects(entity2->GetBoundingBox());
}
