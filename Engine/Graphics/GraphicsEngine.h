#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <vector>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <wrl.h>

#include "VertexBuffer.h"
#include "./Engine/Player.h"
#include "Game/World.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

using namespace DirectX;

struct cbPerObject
{
  XMMATRIX  WVP;
  XMMATRIX World;
};

struct LightCBuf
{
  XMFLOAT3 LightPos;
  float padding;
};

class GraphicsEngine
{
public:
  GraphicsEngine(HWND hWnd, int width, int height, std::shared_ptr<World> world, std::shared_ptr<Player> player);

  void RenderFrame();
  void UpdateVertexBuffer(int direction);

private:
  void InitGraphics();
  void InitPipeline();
  void InitCamera();

  int m_width;
  int m_height;

  XMFLOAT4X4 m_cube1World;

  XMFLOAT4X4 m_WVP;
  XMFLOAT4X4 m_camView;
  XMFLOAT4X4 m_playerView;
  XMFLOAT4X4 m_camProjection;

  const XMFLOAT3 m_camPositionOrig{0.0f, 0.0f, 0.0f};
  const XMFLOAT3 m_camTargetOrig{0.0f, 0.0f, -1.0f};
  const XMFLOAT3 m_camUpOrig{0.0f, 1.0f, 0.0f};

  XMFLOAT3 m_camPosition;
  XMFLOAT3 m_camTarget;
  XMFLOAT3 m_camUp;

  XMFLOAT4X4 Rotation;
  XMFLOAT4X4 Scale;
  XMFLOAT4X4 Translation;

  float m_rot = 0.00f;

  Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain;
  Microsoft::WRL::ComPtr<ID3D11Device> m_device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_backbuffer;
  Microsoft::WRL::ComPtr<ID3D11InputLayout> m_VSinputLayout;
  Microsoft::WRL::ComPtr<ID3D11InputLayout> m_PSinputLayout;
  Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;   
  Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;    
  Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
  Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
  Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
  Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
  Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
  Microsoft::WRL::ComPtr<ID3D11Buffer> m_cbPerObjectBuffer;
  Microsoft::WRL::ComPtr<ID3D11Buffer> m_LightCBuffer;

  std::vector<VertexBuffer> m_vertexBuffers;

  cbPerObject cbPerObj;
  LightCBuf lightCBuffer;

  std::shared_ptr<Player> m_player;
  std::shared_ptr<World> m_world;
};

