#pragma once

#include <memory>
#include <DirectXMath.h>
#include <DirectXCollision.h>

struct CollisionDetector
{
  [[nodiscard]]
  static float ResolveX(DirectX::BoundingBox bb1, const DirectX::BoundingBox& bb2);
  [[nodiscard]]
  static float ResolveZ(DirectX::BoundingBox bb1, const DirectX::BoundingBox& bb2);
};

