#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <memory>
#include <vector>
#include <wrl.h>

#include "Game/Blocks/Block.h"



struct VERTEX
{
  FLOAT X, Y, Z;
  DirectX::XMFLOAT3 normal;
};

class VertexBuffer
{
public:
  VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, DirectX::XMVECTOR blockCoord, DirectX::XMFLOAT4 color);

  Microsoft::WRL::ComPtr<ID3D11Buffer> GetBuffer();

private:
  HRESULT Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, DirectX::XMVECTOR blockCoord, DirectX::XMFLOAT4 color);

  UINT m_stride;
  UINT m_offset;

  Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
};

