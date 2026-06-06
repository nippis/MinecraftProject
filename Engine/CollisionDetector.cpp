#include "CollisionDetector.h"

static bool Collides(DirectX::BoundingBox bb1, DirectX::BoundingBox bb2)
{
  bb1.Extents.x -= 0.0001;
  bb1.Extents.y -= 0.0001;
  bb1.Extents.z -= 0.0001;
  bb2.Extents.x -= 0.0001;
  bb2.Extents.y -= 0.0001;
  bb2.Extents.z -= 0.0001;
  return bb1.Intersects(bb2);
}

float CollisionDetector::ResolveX(DirectX::BoundingBox bb1, const DirectX::BoundingBox& bb2)
{
  if (!Collides(bb1, bb2))
    return 0.0f;
  using namespace DirectX;
  float testloc = bb1.Center.x;
  float xmin1 = testloc - bb1.Extents.x;
  float xmin2 = bb2.Center.x - bb2.Extents.x;
  float xmax1 = testloc + bb1.Extents.x;
  float xmax2 = bb2.Center.x + bb2.Extents.x;
  float overlapX = fmin(xmax1, xmax2) - fmax(xmin1, xmin2);

  return overlapX;
}

float CollisionDetector::ResolveZ(DirectX::BoundingBox bb1, const DirectX::BoundingBox& bb2)
{
  if (!Collides(bb1, bb2))
    return 0.0f;
  using namespace DirectX;
  float testloc = bb1.Center.z;
  float zmin1 = testloc - bb1.Extents.z;
  float zmin2 = bb2.Center.z - bb2.Extents.z;
  float zmax1 = testloc + bb1.Extents.z;
  float zmax2 = bb2.Center.z + bb2.Extents.z;
  float overlapZ = fmin(zmax1, zmax2) - fmax(zmin1, zmin2);

  return overlapZ;
}