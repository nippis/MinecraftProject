#include "VertexBuffer.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")


template<class T>
VertexBuffer<T>::VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext) :
  m_device(device), m_deviceContext(deviceContext)
{
}

template<class T>
VertexBuffer<T>::~VertexBuffer()
{
}

template<class T>
ID3D11Buffer * VertexBuffer<T>::Buffer()
{
  return m_vertexBuffer.get();
}

template<class T>
HRESULT VertexBuffer<T>::Initialize(std::vector<T> vertices)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(T) * vertices.size();
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA vinitData;
  vinitData.pSysMem = vertices.data();

  HRESULT hr = m_device->CreateBuffer(&bd, &vinitData, m_vertexBuffer.get());

  return hr;
}
