#include <d3dcompiler.h>

#include "GraphicsEngine.h"
#include "Engine/ErrorLogger.h"


#pragma comment (lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")


GraphicsEngine::GraphicsEngine(HWND hWnd, int width, int height, std::shared_ptr<World> world, std::shared_ptr<Player> player) :
  m_width(width), m_height(height), m_player(player), m_world(world)
{

  HRESULT hr;
  //Describe our SwapChain Buffer
  DXGI_MODE_DESC bufferDesc;

  ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

  bufferDesc.Width = m_width;
  bufferDesc.Height = m_height;
  bufferDesc.RefreshRate.Numerator = 0;
  bufferDesc.RefreshRate.Denominator = 0;
  bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

  // Direct3D initialization
  DXGI_SWAP_CHAIN_DESC scd;
  ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

  scd.BufferDesc = bufferDesc;
  scd.SampleDesc.Count = 1;
  scd.SampleDesc.Quality = 0;
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scd.BufferCount = 1;
  scd.OutputWindow = hWnd;
  scd.Windowed = true;
  scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &m_swapchain, &m_device, NULL, &m_deviceContext);

  // Set the render target
  Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
  m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);

  m_device->CreateRenderTargetView(pBackBuffer.Get(), NULL, &m_backbuffer);

  //Describe our Depth/Stencil Buffer
  D3D11_TEXTURE2D_DESC depthStencilDesc;

  depthStencilDesc.Width = m_width;
  depthStencilDesc.Height = m_height;
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
  m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), NULL, &m_depthStencilView);

  //Set our Render Target
  m_deviceContext->OMSetRenderTargets(1, m_backbuffer.GetAddressOf(), m_depthStencilView.Get());

  D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
  ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

  depthStencilStateDesc.DepthEnable = true;
  depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

  m_device->CreateDepthStencilState(&depthStencilStateDesc, &m_depthStencilState);

  // Set the viewport
  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = (FLOAT)m_width;
  viewport.Height = (FLOAT)m_height;
  viewport.MinDepth = 0;
  viewport.MaxDepth = 1;

  m_deviceContext->RSSetViewports(1, &viewport);

  D3D11_RASTERIZER_DESC rasterizerDesc;
  ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

  rasterizerDesc.FillMode = D3D11_FILL_SOLID;
  rasterizerDesc.CullMode = D3D11_CULL_BACK;
  m_device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);

  D3D11_BUFFER_DESC lcbbd;
  ZeroMemory(&lcbbd, sizeof(D3D11_BUFFER_DESC));

  lcbbd.Usage = D3D11_USAGE_DEFAULT;
  lcbbd.ByteWidth = sizeof(LightCBuf);
  lcbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  lcbbd.CPUAccessFlags = 0;
  lcbbd.MiscFlags = 0;

  hr = m_device->CreateBuffer(&lcbbd, NULL, &m_LightCBuffer);

  // Constant buffer to pixel shader

  InitCamera();
  InitPipeline();
  InitGraphics();


}

void GraphicsEngine::InitCamera()
{
  // CAMERA STUFF ----------------
  D3D11_BUFFER_DESC cbbd;
  ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

  cbbd.Usage = D3D11_USAGE_DEFAULT;
  cbbd.ByteWidth = sizeof(cbPerObject);
  cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  cbbd.CPUAccessFlags = 0;
  cbbd.MiscFlags = 0;

  HRESULT hr = m_device->CreateBuffer(&cbbd, NULL, &m_cbPerObjectBuffer);
  if (FAILED(hr))
  {
    ErrorLogger::Log(hr, "Ei nyt toiminu t�� kamerabufferin teko");
  }

  //Set the View matrix
  m_camPosition = m_camPositionOrig;
  m_camTarget = m_camTargetOrig;
  m_camUp = m_camUpOrig;

  //Set the Projection matrix
  XMStoreFloat4x4(&m_camProjection, XMMatrixPerspectiveFovRH(0.4f * 3.14f, (float)m_width / m_height, 0.1f, 1000.0f));

  // -------------------------
}

void GraphicsEngine::RenderFrame(void)
{
  FLOAT rgba [4] = { 0.0f, 0.2f, 0.4f, 0.0f };
  m_deviceContext->ClearRenderTargetView(m_backbuffer.Get(), rgba);

  //Refresh the Depth/Stencil view
  m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  //Set the World/View/Projection matrix, then send it to constant buffer in effect file
  auto worldMatrix = XMMatrixIdentity();

  // Calculate the camera rotation relative to player coordinates
  XMStoreFloat3(&m_camTarget, m_player->GetDirection());
  XMStoreFloat3(&m_camUp, m_player->GetUp());

  
  // Calculate player position
  XMStoreFloat3(&m_camPosition, m_player->GetLocation() + XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
  XMStoreFloat4x4(&m_camView, XMMatrixLookToRH(XMLoadFloat3(&m_camPosition), XMLoadFloat3(&m_camTarget), XMLoadFloat3(&m_camUp)));
  XMStoreFloat4x4(&m_WVP, worldMatrix * XMLoadFloat4x4(&m_camView) * XMLoadFloat4x4(&m_camProjection));
  
  cbPerObj.WVP = XMMatrixTranspose(XMLoadFloat4x4(&m_WVP));
  cbPerObj.World = XMMatrixTranspose(worldMatrix);

  m_deviceContext->UpdateSubresource(m_cbPerObjectBuffer.Get(), 0, NULL, &cbPerObj, 0, 0);

  m_deviceContext->VSSetConstantBuffers(0, 1, m_cbPerObjectBuffer.GetAddressOf());

  // LIGHT
  lightCBuffer.LightPos = { 50.0f, 80.0f, 50.0f };

  m_deviceContext->UpdateSubresource(m_LightCBuffer.Get(), 0, NULL, &lightCBuffer, 0, 0);

  m_deviceContext->PSSetConstantBuffers(0, 1, m_LightCBuffer.GetAddressOf());
  // -------

  m_deviceContext->IASetInputLayout(m_VSinputLayout.Get());
  m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  m_deviceContext->RSSetState(m_rasterizerState.Get());
  m_deviceContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

  // set the shader objects
  m_deviceContext->VSSetShader(m_vertexShader.Get(), 0, 0);
  m_deviceContext->PSSetShader(m_pixelShader.Get(), 0, 0);

  // select which vertex buffer to display
  UINT stride = sizeof(VERTEX);
  UINT offset = 0;

  for (auto vertexBuffer : m_vertexBuffers)
  {
    m_deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetBuffer().GetAddressOf(), &stride, &offset);
    m_deviceContext->Draw(36, 0);
  }


  m_swapchain->Present(0, 0);
}

void GraphicsEngine::UpdateVertexBuffer(int direction)
{

}

// -------------------------
// this is the function that creates the shape to render
// -------------------------
void GraphicsEngine::InitGraphics()
{

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

  D3D11_BUFFER_DESC indexBufferDesc;
  ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

  indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  indexBufferDesc.ByteWidth = sizeof(DWORD) * indices.size();
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  D3D11_SUBRESOURCE_DATA iinitData;

  iinitData.pSysMem = indices.data();
  m_device->CreateBuffer(&indexBufferDesc, &iinitData, &m_indexBuffer);

  m_deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

  // TRIANGLE 1
  for (auto& block : m_world->GetBlocks())
  {
    m_vertexBuffers.push_back(VertexBuffer(m_device, block->GetLocation(), block->GetColor()));
  }
 
}


// -----------------------
// this function loads and prepares the shaders
// -----------------------
void GraphicsEngine::InitPipeline()
{
  // load and compile the two shaders
  ID3DBlob *VS, *PS;
  D3DCompileFromFile(L".\\Shaders\\VertexShader.hlsl", 0, 0, "main", "vs_4_0", 0, 0, &VS, 0);
  D3DCompileFromFile(L".\\Shaders\\PixelShader.hlsl", 0, 0, "main", "ps_4_0", 0, 0, &PS, 0);

  // encapsulate both shaders into shader objects
  m_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, m_vertexShader.GetAddressOf());
  m_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, m_pixelShader.GetAddressOf());

  // create the input layout object
  D3D11_INPUT_ELEMENT_DESC ied[] =
  {
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
  };

  m_device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_VSinputLayout);
  m_device->CreateInputLayout(ied, 2, PS->GetBufferPointer(), PS->GetBufferSize(), &m_PSinputLayout);
}