#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <vector>
#include <ctime>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

IDXGISwapChain *swapchain;
ID3D11Device *dev;
ID3D11DeviceContext *devcon;
ID3D11RenderTargetView *backbuffer;
ID3D11InputLayout *pLayout;            // the pointer to the input layout
ID3D11VertexShader *pVS;               // the pointer to the vertex shader
ID3D11PixelShader *pPS;                // the pointer to the pixel shader
ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer
ID3D11Buffer *squareIndexBuffer;
ID3D11Buffer *squareVertBuffer;
ID3D11DepthStencilView* depthStencilView;
ID3D11Texture2D* depthStencilBuffer;

struct VERTEX {
  FLOAT X, Y, Z;
  D3DXCOLOR Color;
};

void InitD3D(HWND hWnd);
void RenderFrame(void);
void CleanD3D(void);
void InitGraphics(void);
void InitPipeline(void);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  HWND hWnd;
  WNDCLASSEX wc;

  ZeroMemory(&wc, sizeof(WNDCLASSEX));

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszClassName = L"WindowClass1";

  RegisterClassEx(&wc);

  RECT wr = { 0, 0, 500, 400 };
  AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

  hWnd = CreateWindowEx(NULL, L"WindowClass1", L"MinecraftProject", WS_OVERLAPPEDWINDOW, 300, 300, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, nCmdShow);

  InitD3D(hWnd);

  MSG msg;
  while (true)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      if (msg.message == WM_QUIT)
        break;
    }
    else
    {
      RenderFrame();
    }
  }

  CleanD3D();
  return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      return 0;
    } break;
    case WM_KEYDOWN:
    {
      if (wParam == VK_SPACE)
      {
      }
    } break;
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

void InitD3D(HWND hWnd)
{
  // Direct3D initialization
  DXGI_SWAP_CHAIN_DESC scd;
  ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

  scd.BufferCount = 1;
  scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  scd.BufferDesc.Width = SCREEN_WIDTH;
  scd.BufferDesc.Height = SCREEN_HEIGHT;
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scd.OutputWindow = hWnd;
  scd.SampleDesc.Count = 4;
  scd.Windowed = true;

  D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &swapchain, &dev, NULL, &devcon);

  // Set the render target
  ID3D11Texture2D *pBackBuffer;
  swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

  dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
  pBackBuffer->Release();

  devcon->OMSetRenderTargets(1, &backbuffer, NULL);

  //Describe our Depth/Stencil Buffer
  D3D11_TEXTURE2D_DESC depthStencilDesc;

  depthStencilDesc.Width = SCREEN_WIDTH;
  depthStencilDesc.Height = SCREEN_HEIGHT;
  depthStencilDesc.MipLevels = 1;
  depthStencilDesc.ArraySize = 1;
  depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilDesc.SampleDesc.Count = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
  depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
  depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthStencilDesc.CPUAccessFlags = 0;
  depthStencilDesc.MiscFlags = 0;

  //Create the Depth/Stencil View
  dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
  dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

  //Set our Render Target
  devcon->OMSetRenderTargets(1, &backbuffer, depthStencilView);

  // Set the viewport
  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = SCREEN_WIDTH;
  viewport.Height = SCREEN_HEIGHT;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;

  devcon->RSSetViewports(1, &viewport);

  devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  InitPipeline();
  InitGraphics();

  
}

void CleanD3D()
{
  pLayout->Release();
  pVS->Release();
  pPS->Release();
  pVBuffer->Release();
  swapchain->Release();
  backbuffer->Release();
  dev->Release();
  devcon->Release();
  depthStencilView->Release();
  depthStencilBuffer->Release();
}


static float index = 0.0f;

void RenderFrame(void)
{

  // clear the back buffer to a deep blue
  devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

  // select which vertex buffer to display
  UINT stride = sizeof(VERTEX);
  UINT offset = 0;
  devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);


  // select which primtive type we are using


  //Refresh the Depth/Stencil view
  devcon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  // draw the vertex buffer to the back buffer
  devcon->DrawIndexed(12, 0, 0);

  // switch the back buffer and the front buffer
  swapchain->Present(0, 0);
}

// -------------------------
// this is the function that creates the shape to render
// -------------------------
void InitGraphics()
{
  // create a triangle using the VERTEX struct
  std::vector<VERTEX> Vertices =
  {
      {-0.2f, -0.2f, 0.5f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
      {-0.2f,  0.2f, 0.5f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
      { 0.2f,  0.2f, 0.5f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
      { 0.2f, -0.2f, 0.5f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
      { 0.0f, -0.4f, 0.5f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
      { 0.4f, -0.4f, 0.5f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)}
  };


  std::vector<DWORD> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        3, 5 ,4
  };

  D3D11_BUFFER_DESC indexBufferDesc;
  ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(DWORD) * indices.size();
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA iinitData;

  iinitData.pSysMem = indices.data();
  dev->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);

  devcon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

  // create the vertex buffer
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = sizeof(VERTEX) * Vertices.size();
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = 0;
  bd.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA vertexBufferData;

  ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
  vertexBufferData.pSysMem = Vertices.data();
  dev->CreateBuffer(&bd, &vertexBufferData, &pVBuffer);

}


// -----------------------
// this function loads and prepares the shaders
// -----------------------
void InitPipeline()
{
  // load and compile the two shaders
  ID3D10Blob *VS, *PS;
  D3DX11CompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_4_0", 0, 0, 0, &VS, 0, 0);
  D3DX11CompileFromFile(L"PixelShader.hlsl", 0, 0, "main", "ps_4_0", 0, 0, 0, &PS, 0, 0);

  // encapsulate both shaders into shader objects
  dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
  dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

  // set the shader objects
  devcon->VSSetShader(pVS, 0, 0);
  devcon->PSSetShader(pPS, 0, 0);

  // create the input layout object
  D3D11_INPUT_ELEMENT_DESC ied[] =
  {
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
  };

  dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
  devcon->IASetInputLayout(pLayout);
}