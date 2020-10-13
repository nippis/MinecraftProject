#include "GraphicsEngine.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

GraphicsEngine::GraphicsEngine(HWND hWnd)
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

  D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &m_swapchain, &m_device, NULL, &m_deviceContext);

  // Set the render target
  ID3D11Texture2D *pBackBuffer;
  m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

  m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_backbuffer);
  pBackBuffer->Release();

  m_deviceContext->OMSetRenderTargets(1, &m_backbuffer, NULL);

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
  m_device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
  m_device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

  //Set our Render Target
  m_deviceContext->OMSetRenderTargets(1, &m_backbuffer, m_depthStencilView);

  // Set the viewport
  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = SCREEN_WIDTH;
  viewport.Height = SCREEN_HEIGHT;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;

  m_deviceContext->RSSetViewports(1, &viewport);

  m_deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  InitPipeline();
  InitGraphics();


}

GraphicsEngine::~GraphicsEngine()
{
  m_inputLayout->Release();
  m_vertexShader->Release();
  m_pixelShader->Release();
  m_vertexBuffer->Release();
  m_swapchain->Release();
  m_backbuffer->Release();
  m_device->Release();
  m_deviceContext->Release();
  m_depthStencilView->Release();
  m_depthStencilBuffer->Release();
}


void GraphicsEngine::RenderFrame(void)
{
  m_deviceContext->ClearRenderTargetView(m_backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

  // select which vertex buffer to display
  UINT stride = sizeof(VERTEX);
  UINT offset = 0;
  m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

  //Refresh the Depth/Stencil view
  m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  m_deviceContext->DrawIndexed(18, 0, 0);

  m_swapchain->Present(0, 0);
}

void GraphicsEngine::UpdateVertexBuffer()
{
  D3D11_MAPPED_SUBRESOURCE vertexBufferData;
  
  m_deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vertexBufferData);
  memcpy(vertexBufferData.pData, m_vertices.data(), m_vertices.size() * sizeof(VERTEX));
  m_deviceContext->Unmap(m_vertexBuffer, 0);
}

// -------------------------
// this is the function that creates the shape to render
// -------------------------
void GraphicsEngine::InitGraphics()
{

  std::vector<DWORD> indices = {
        0, 1, 2,
        0, 2, 3,
        3, 4, 5,
        5, 6, 7,
        5, 7, 8,
        4, 9, 5
  };

  D3D11_BUFFER_DESC indexBufferDesc;
  ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

  indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  indexBufferDesc.ByteWidth = sizeof(DWORD) * indices.size();
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA iinitData;

  iinitData.pSysMem = indices.data();
  m_device->CreateBuffer(&indexBufferDesc, &iinitData, &m_indexBuffer);

  m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  // create the vertex buffer
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));

  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.ByteWidth = sizeof(VERTEX) * m_vertices.size();
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA vinitData;
  vinitData.pSysMem = m_vertices.data();

  m_device->CreateBuffer(&bd, &vinitData, &m_vertexBuffer);


}


// -----------------------
// this function loads and prepares the shaders
// -----------------------
void GraphicsEngine::InitPipeline()
{
  // load and compile the two shaders
  ID3D10Blob *VS, *PS;
  D3DX11CompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_4_0", 0, 0, 0, &VS, 0, 0);
  D3DX11CompileFromFile(L"PixelShader.hlsl", 0, 0, "main", "ps_4_0", 0, 0, 0, &PS, 0, 0);

  // encapsulate both shaders into shader objects
  m_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_vertexShader);
  m_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pixelShader);

  // set the shader objects
  m_deviceContext->VSSetShader(m_vertexShader, 0, 0);
  m_deviceContext->PSSetShader(m_pixelShader, 0, 0);

  // create the input layout object
  D3D11_INPUT_ELEMENT_DESC ied[] =
  {
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
  };

  m_device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_inputLayout);
  m_deviceContext->IASetInputLayout(m_inputLayout);
}