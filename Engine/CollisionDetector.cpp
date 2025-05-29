#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
}

DirectX::XMVECTOR CollisionDetector::GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
  if (!Collide(entity1, entity2))
    return XMVectorZero();
  DirectX::XMVECTOR distance = XMVectorAbs(entity1->GetLocation() - entity2->GetLocation());
  if ((XMVectorGetZ(distance) > XMVectorGetX(distance)) && (XMVectorGetZ(distance) > XMVectorGetY(distance)))
    return Z_POS;
  else if (XMVectorGetY(distance) > XMVectorGetX(distance))
    return Y_POS;
  return X_POS;
}

DirectX::XMVECTOR CollisionDetector::GetUnblockedDirection(DirectX::XMVECTOR dir, DirectX::XMVECTOR blockerNormal)
{
  return (dir + XMVector4Reflect(dir, blockerNormal)) / 2.0f;
}

bool CollisionDetector::Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
  return entity1->GetBoundingBox().Intersects(entity2->GetBoundingBox());
}
