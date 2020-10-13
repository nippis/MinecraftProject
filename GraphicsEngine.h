#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <vector>
#include <ctime>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum DIRECTION
{
  left = 39,
  up = 40,
  right = 41,
  down = 42
};

struct VERTEX 
{
  FLOAT X, Y, Z;
  D3DXCOLOR Color;
};

class GraphicsEngine
{
public:
  GraphicsEngine(HWND hWnd);
  ~GraphicsEngine();

  void RenderFrame();
  void UpdateVertexBuffer();

private:
  void InitGraphics();
  void InitPipeline();

  std::vector<VERTEX> m_vertices =
  {
      {-0.3f,  -0.2f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      {-0.25f,  0.0f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      {-0.15f,  0.0f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      {-0.1f,  -0.2f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      {-0.05f,  0.8f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.1f,  -0.2f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.15f,  0.0f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.25f,  0.0f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.3f,  -0.2f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)},
      { 0.05f,  0.8f, 0.5f, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)}
  };

  IDXGISwapChain *m_swapchain;
  ID3D11Device *m_device;
  ID3D11DeviceContext *m_deviceContext;
  ID3D11RenderTargetView *m_backbuffer;
  ID3D11InputLayout *m_inputLayout;
  ID3D11VertexShader *m_vertexShader;   
  ID3D11PixelShader *m_pixelShader;    
  ID3D11Buffer *m_vertexBuffer;    
  ID3D11Buffer *m_indexBuffer;
  ID3D11DepthStencilView* m_depthStencilView;
  ID3D11Texture2D* m_depthStencilBuffer;

};

