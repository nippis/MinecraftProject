#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
}

CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::CollideY(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
{
  std::shared_ptr<BoundingBox> bBox1 = entity1->GetBoundingBox();
  std::shared_ptr<BoundingBox> bBox2 = entity2->GetBoundingBox();

  if (bBox1->Ymax >= bBox2->Ymin || bBox1->Ymin <= bBox2->Ymax)
    return true;
  else
    return false;
}
