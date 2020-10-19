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

  if ((bBox1->Xmax <= bBox1->Xmax && bBox1->Xmin >= bBox2->Xmin) &&
    (bBox1->Zmax <= bBox1->Ymax && bBox1->Zmin >= bBox2->Ymin))
  {
    if (bBox1->Ymax <= bBox2->Zmax)
      return true;
    else
      return false;
  }
  return false;
}
