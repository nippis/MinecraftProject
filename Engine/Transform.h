#pragma once

#include <DirectXMath.h>

#include "Constants.h"

using namespace DirectX;

class Transform
{
public:
  Transform();
  Transform(XMVECTOR location);
  ~Transform();

  void AddLocation(const XMVECTOR& locationAdd);
  void AddRotation(const XMVECTOR& rotationAdd);
  void SetLocation(const XMVECTOR& location);
  void SetForward(const XMVECTOR& forward);
  void SetUp(const XMVECTOR& up);

  XMVECTOR GetLocation() const;
  XMVECTOR GetDirection() const;
  XMVECTOR GetForwardXZ() const;
  XMVECTOR GetUp() const;
  XMVECTOR GetRightXZ() const;

private:
  XMFLOAT3 m_location;
  XMFLOAT3 m_forward;
  XMFLOAT3 m_up;
};

