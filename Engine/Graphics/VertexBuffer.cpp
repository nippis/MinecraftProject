#include <DirectXMath.h>

#include "VertexBuffer.h"

#pragma comment (lib, "d3d11.lib")

using namespace DirectX;

VertexBuffer::VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device> device, DirectX::XMVECTOR blockCoord, DirectX::XMFLOAT4 color)
{
  Initialize(device, blockCoord, color);
}


Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer::GetBuffer()
{
  return m_vertexBuffer.Get();
}


HRESULT VertexBuffer::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, DirectX::XMVECTOR blockCoord, DirectX::XMFLOAT4 color)
{
  using namespace DirectX;
  std::vector<VERTEX> vertices =
  {
      {-0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetZ(blockCoord), 0.0f + XMVectorGetY(blockCoord), color},
      {-0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetZ(blockCoord), 0.0f + XMVectorGetY(blockCoord), color},
      { 0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetZ(blockCoord), 0.0f + XMVectorGetY(blockCoord), color},
      { 0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetZ(blockCoord), 0.0f + XMVectorGetY(blockCoord), color},
      {-0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetZ(blockCoord), 1.0f + XMVectorGetY(blockCoord), color},
      {-0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetZ(blockCoord), 1.0f + XMVectorGetY(blockCoord), color},
      { 0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetZ(blockCoord), 1.0f + XMVectorGetY(blockCoord), color},
      { 0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetZ(blockCoord), 1.0f + XMVectorGetY(blockCoord), color}
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
