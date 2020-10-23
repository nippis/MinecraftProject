#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
}

CollisionDetector::~CollisionDetector()
{
}

DirectX::XMVECTOR CollisionDetector::GetCollidingNormal(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
  DirectX::XMVECTOR distance = XMVectorAbs(entity1->GetLocation() - entity2->GetLocation());
  DirectX::XMVECTOR collidingNormal = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
  if (XMVectorGetY(distance) > XMVectorGetX(distance))
    collidingNormal = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  if ((XMVectorGetZ(distance) > XMVectorGetX(distance)) && (XMVectorGetZ(distance) > XMVectorGetY(distance)))
    collidingNormal = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
  return collidingNormal;
}

DirectX::XMVECTOR CollisionDetector::GetUnblockedDirection(DirectX::XMVECTOR dir, DirectX::XMVECTOR blockerNormal)
{
  return (dir + XMVector4Reflect(dir, blockerNormal)) / 2.0f;
}

bool CollisionDetector::Collide(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
  std::shared_ptr<BoundingBox> bBox1 = entity1->GetBoundingBox();
  std::shared_ptr<BoundingBox> bBox2 = entity2->GetBoundingBox();
  if (bBox1->Ymax >= bBox2->Ymin && bBox1->Ymin <= bBox2->Ymax)
  {
    if (bBox1->Xmax >= bBox2->Xmin && bBox1->Xmin <= bBox2->Xmax)
    {
      if (bBox1->Zmax >= bBox2->Zmin && bBox1->Zmin <= bBox2->Zmax)
        return true;
    }
  }


  return false;
}
