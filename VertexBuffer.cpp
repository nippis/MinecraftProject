#include "VertexBuffer.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")



VertexBuffer::VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, std::vector<VERTEX> vertices)
{
  Initialize(device, vertices);
}


Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer::GetBuffer()
{
  return m_vertexBuffer.Get();
}


HRESULT VertexBuffer::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, std::vector<VERTEX> vertices)
{
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(VERTEX) * vertices.size();
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA vinitData;
  vinitData.pSysMem = vertices.data();

  HRESULT hr = device->CreateBuffer(&bd, &vinitData, &m_vertexBuffer);

  return hr;
}
