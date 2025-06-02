#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <vector>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <wrl.h>

#include "VertexBuffer.h"
#include "./Game/Player.h"
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
  ~GraphicsEngine() = default;

  void RenderFrame();
  void UpdateVertexBuffer(int direction);

private:
  void InitGraphics();
  void InitPipeline();
  void InitCamera();

  int m_width;
  int m_height;

  XMMATRIX m_cube1World;

  XMMATRIX m_WVP;
  XMMATRIX m_worldMatrix;
  XMMATRIX m_camView;
  XMMATRIX m_playerView;
  XMMATRIX m_camProjection;

  const XMVECTOR m_camPositionOrig = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
  const XMVECTOR m_camTargetOrig =   XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
  const XMVECTOR m_camUpOrig =       XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

  XMVECTOR m_camPosition;
  XMVECTOR m_camTarget;
  XMVECTOR m_camUp;

  XMMATRIX Rotation;
  XMMATRIX Scale;
  XMMATRIX Translation;

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

