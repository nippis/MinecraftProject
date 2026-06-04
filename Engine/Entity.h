#pragma once

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "Constants.h"

using namespace DirectX;

class Entity
{
public:
  Entity(XMVECTOR location, float height, float width, float depth);

  const BoundingBox& GetBoundingBox() const;

  virtual void SetLocation(const XMVECTOR& location);
  virtual void SetDirection(const XMVECTOR& forward);
  virtual void SetUp(const XMVECTOR& up);

  virtual XMVECTOR GetLocation() const;
  virtual XMVECTOR GetDirection() const;
  virtual XMVECTOR GetForwardXZ() const;
  virtual XMVECTOR GetUp() const;
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

