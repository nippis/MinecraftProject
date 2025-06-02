#include "Game.h"

LRESULT CALLBACK MessageProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
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
  
  Game::Instance(hWnd).run();

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
      Game::Instance().getKeyboard()->SetState(message, wParam);
    } break;
    case WM_KEYUP:
    {
      Game::Instance().getKeyboard()->SetState(message, wParam);
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