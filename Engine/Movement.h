#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Movement
{
public:
  Movement();
  Movement(XMVECTOR location);
  ~Movement();

  void AddLocation(const XMVECTOR& locationAdd);
  void AddRotation(const XMVECTOR& rotationAdd);
  void SetLocation(const XMVECTOR& location);
  void SetRotation(const XMVECTOR& rotation);

  XMVECTOR GetLocationVec();
  const XMFLOAT3& GetLocation();
  XMVECTOR GetRotationVec();
  const XMFLOAT4& GetRotation();

private:
  XMFLOAT3 m_location;
  XMFLOAT4 m_rotation;
};

