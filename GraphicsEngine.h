#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <vector>
#include <ctime>
#include <xnamath.h>
#include <wrl.h>

#include "VertexBuffer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum DIRECTION
{
  left = 39,
  up = 40,
  right = 41,
  down = 42
};



struct cbPerObject
{
  XMMATRIX  WVP;
};

class GraphicsEngine
{
public:
  GraphicsEngine(HWND hWnd, int width, int height);
  ~GraphicsEngine() = default;

  void RenderFrame();
  void UpdateVertexBuffer(bool left);

private:
  void InitGraphics();
  void InitPipeline();
  
  std::vector<VERTEX> m_vertices =
  {
      {-0.2f, -0.2f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      {-0.2f,  0.2f, 0.5f, D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f)},
      { 0.2f,  0.2f, 0.5f, D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f)},
      { 0.2f, -0.2f, 0.5f, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)},
      {-0.2f, -0.2f, 0.9f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      {-0.2f,  0.2f, 0.9f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.2f,  0.2f, 0.9f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.2f, -0.2f, 0.9f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)}
  };

  int m_width;
  int m_height;

  XMMATRIX m_cube1World;

  XMMATRIX m_WVP;
  XMMATRIX m_World;
  XMMATRIX m_camView;
  XMMATRIX m_camProjection;
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
  Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
  Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;   
  Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;    
  std::shared_ptr<VertexBuffer> m_vertexBuffer;    
  Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
  Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
  Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
  Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
  Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
  Microsoft::WRL::ComPtr<ID3D11Buffer> m_cbPerObjectBuffer;

  cbPerObject cbPerObj;
};

