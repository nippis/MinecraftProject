#pragma once

#include <DirectXMath.h>

#include "Constants.h"

using namespace DirectX;

class Transform
{
public:
  Transform();
  Transform(XMVECTOR location);

  virtual void AddLocation(const XMVECTOR& locationAdd);
  virtual void AddRotation(const XMVECTOR& rotationAdd);
  virtual void SetLocation(const XMVECTOR& location);
  virtual void SetForward(const XMVECTOR& forward);
  virtual void SetUp(const XMVECTOR& up);

  virtual XMVECTOR GetLocation() const;
  virtual XMVECTOR GetDirection() const;
  virtual XMVECTOR GetForwardXZ() const;
  virtual XMVECTOR GetUp() const;
  virtual XMVECTOR GetRightXZ() const;

private:
  XMFLOAT3 m_location;
  XMFLOAT3 m_forward;
  XMFLOAT3 m_up;
};

