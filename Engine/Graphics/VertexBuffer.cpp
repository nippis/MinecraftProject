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
  std::vector<DirectX::XMFLOAT3> normals =
  {
     { 0.0f,  0.0f, -1.0f },
     { 0.0f,  0.0f,  1.0f },
     { 0.0f, -1.0f,  0.0f },
     { 0.0f,  1.0f,  0.0f },
     {-1.0f,  0.0f,  0.0f },
     { 1.0f,  0.0f,  0.0f }
  };

  std::vector<VERTEX> vertices =
  {
      {-0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetY(blockCoord), 0.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      {-0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetY(blockCoord), 0.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      { 0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetY(blockCoord), 0.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      { 0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetY(blockCoord), 0.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      {-0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetY(blockCoord), 1.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      {-0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetY(blockCoord), 1.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      { 0.5f + XMVectorGetX(blockCoord),  0.5f + XMVectorGetY(blockCoord), 1.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)},
      { 0.5f + XMVectorGetX(blockCoord), -0.5f + XMVectorGetY(blockCoord), 1.0f + XMVectorGetZ(blockCoord), XMFLOAT3(0.0f, 0.0f, 0.0f)}
  };

  std::vector<DWORD> indices = {
      0, 1, 2,
      0, 2, 3,
      3, 2, 6,
      3, 6, 7,
      1, 5, 2,
      2, 5, 6,
      0, 4, 5,
      5, 1, 0,
      0, 3, 4,
      3, 7, 4,
      7, 6, 5,
      7, 5, 4
  };

  std::vector<VERTEX> allVertices = {};

  for (int i = 0; i < indices.size(); i++)
  {
    VERTEX vertex = vertices.at(indices.at(i));
    vertex.normal = normals.at(i / 6);
    allVertices.push_back(vertex);
  }

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(VERTEX) * allVertices.size();
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA vinitData;
  vinitData.pSysMem = allVertices.data();

  HRESULT hr = device->CreateBuffer(&bd, &vinitData, &m_vertexBuffer);

  return hr;
}
