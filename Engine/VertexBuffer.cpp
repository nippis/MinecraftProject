#include <DirectXMath.h>

#include "VertexBuffer.h"

#pragma comment (lib, "d3d11.lib")

using namespace DirectX;

VertexBuffer::VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, BlockCoord blockCoord, BlockColor color)
{
  Initialize(device, blockCoord, color);
}


Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer::GetBuffer()
{
  return m_vertexBuffer.Get();
}


HRESULT VertexBuffer::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, BlockCoord blockCoord, BlockColor color)
{
  std::vector<VERTEX> vertices =
  {
      {-0.5f + blockCoord.x, -0.5f + blockCoord.z, 0.0f + blockCoord.y, XMFLOAT4(0.5f, 0.3f, 0.0f, 1.0f)},
      {-0.5f + blockCoord.x,  0.5f + blockCoord.z, 0.0f + blockCoord.y, XMFLOAT4(0.0f, 0.8f, 0.0f, 1.0f)},
      { 0.5f + blockCoord.x,  0.5f + blockCoord.z, 0.0f + blockCoord.y, XMFLOAT4(0.0f, 0.7f, 0.0f, 1.0f)},
      { 0.5f + blockCoord.x, -0.5f + blockCoord.z, 0.0f + blockCoord.y, XMFLOAT4(0.5f, 0.3f, 0.0f, 1.0f)},
      {-0.5f + blockCoord.x, -0.5f + blockCoord.z, 1.0f + blockCoord.y, XMFLOAT4(0.5f, 0.3f, 0.0f, 1.0f)},
      {-0.5f + blockCoord.x,  0.5f + blockCoord.z, 1.0f + blockCoord.y, XMFLOAT4(0.0f, 0.6f, 0.0f, 1.0f)},
      { 0.5f + blockCoord.x,  0.5f + blockCoord.z, 1.0f + blockCoord.y, XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f)},
      { 0.5f + blockCoord.x, -0.5f + blockCoord.z, 1.0f + blockCoord.y, XMFLOAT4(0.5f, 0.3f, 0.0f, 1.0f)}
  };

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
