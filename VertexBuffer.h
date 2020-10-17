#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <memory>
#include <vector>
#include <wrl.h>



struct VERTEX
{
  FLOAT X, Y, Z;
  D3DXCOLOR Color;
};

class VertexBuffer
{
public:
  VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, std::vector<VERTEX> vertices);
  virtual ~VertexBuffer() = default;

  Microsoft::WRL::ComPtr<ID3D11Buffer> GetBuffer();

private:
  HRESULT Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, std::vector<VERTEX> vertices);

  UINT m_stride;
  UINT m_offset;

  Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
};

