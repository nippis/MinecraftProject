#pragma once

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "Constants.h"

using namespace DirectX;

class Entity
{
public:
  Entity(XMVECTOR location, float height, float width, float depth);

  virtual void SetLocation(const XMVECTOR& location);
  virtual void SetDirection(const XMVECTOR& forward);
  virtual void SetUp(const XMVECTOR& up);

  [[nodiscard]]
  const BoundingBox& GetBoundingBox() const { return m_bBox; }
  [[nodiscard]]
  virtual XMVECTOR GetLocation() const { return XMLoadFloat3(&m_location); }
  [[nodiscard]]
  virtual XMVECTOR GetDirection() const { return XMLoadFloat3(&m_forward); }
  [[nodiscard]]
  virtual XMVECTOR GetUp() const { return XMLoadFloat3(&m_up); }
  [[nodiscard]]
  virtual XMVECTOR GetForwardXZ() const;
  [[nodiscard]]
  virtual XMVECTOR GetRightXZ() const;

protected:
  BoundingBox m_bBox;
  XMFLOAT3 m_location;
  XMFLOAT3 m_forward;
  XMFLOAT3 m_up;
  float m_height;
  float m_width;
  float m_depth;
};

