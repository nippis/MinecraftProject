#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Movement
{
public:
  Movement();
  Movement(XMVECTOR location, XMVECTOR rotation);
  ~Movement();

  void AddLocation(XMVECTOR locationAdd);
  void AddRotation(XMVECTOR rotationAdd);
  void SetLocation(XMVECTOR location);
  void SetRotation(XMVECTOR rotation);

  XMMATRIX GetMovement();
  XMVECTOR GetLocation();
  XMVECTOR GetRotation();


private:
  XMVECTOR m_location;
  XMVECTOR m_rotation;
};

