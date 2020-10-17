#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <memory>
#include <vector>
#include <wrl.h>


template<class T>
class VertexBuffer
{
public:
  VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext);
  virtual ~VertexBuffer();

  ID3D11Buffer *Buffer();

private:
  HRESULT Initialize(std::vector<T> vertices);

  UINT m_stride;
  UINT m_offset;

  Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
  Microsoft::WRL::ComPtr<ID3D11Device> m_device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
};

