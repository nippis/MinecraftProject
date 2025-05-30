#include "Game.h"

LRESULT CALLBACK MessageProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

static std::shared_ptr<Keyboard> KEYBOARD = std::make_shared<Keyboard>();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  WNDCLASSEX wc = { 0 };
  wc.cbSize = sizeof(wc);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = MessageProcessor;
  wc.hInstance = hInstance;
  wc.lpszClassName = L"WindowClass1";
  RegisterClassEx(&wc);

  RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
  AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

  HWND hWnd = CreateWindowEx(NULL, L"WindowClass1", L"MinecraftProject", WS_OVERLAPPEDWINDOW, 300, 300, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

  ShowWindow(hWnd, nCmdShow);

  auto game = std::make_shared<Game>(hWnd, KEYBOARD);
  
  MSG msg;
  game->run(&msg);

  return 0;
}

LRESULT CALLBACK MessageProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
      KEYBOARD->SetState(message, wParam);
    } break;
    case WM_KEYUP:
    {
      KEYBOARD->SetState(message, wParam);
    } break;
    case WM_MOUSEMOVE:
    {
      // Handle mouse movement if necessary
    } break;
    default:
    {
      // Handle other messages if necessary
    } break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}