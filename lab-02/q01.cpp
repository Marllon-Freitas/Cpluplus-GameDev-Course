/*
Considerando o código fornecido no projeto ProgWindows, construa uma janela em tela cheia
  a. Altere o estilo da janela para WS_POPUP, tamanho da janela igual ao tamanho da tela.
  b. Modifique a janela para que ela tenha um tamanho fixo de 960x540.
  c. Modifique a janela para eliminar os botões de maximizar e minimizar
  d. Modifique a janela de tal forma que ela fique centralizada.
  e. Modifique a janela de tal forma que ela possua uma área cliente igual a 960x540.
  f. Personalize o ícone e o cursor da sua aplicação através das seguintes mudanças
*/

// inclui tipos básicos e funções da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include "Resources.h" // identificadores de recursos

// protótipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
  HWND hwnd;         // identificador da janela
  MSG msg;           // mensagem
  WNDCLASS wndclass; // classe da janela

  // Definindo uma classe de janela chamada "BasicWindow"
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = WinProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
  wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
  wndclass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = "BasicWindow";

  // Registrando a classe "BasicWindow"
  if (!RegisterClass(&wndclass))
  {
    MessageBox(NULL, "Erro na criação da janela!", "Aplicação", MB_ICONERROR);
    return 0;
  }

  // tamanho da janela igual ao tamanho da tela
  int windowWidth = 960;
  int windowHeight = 540;

  // usado para centralizar a janela na tela
  int windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
  int windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;

  // Criando uma janela baseada na classe "BasicWindow"
  hwnd = CreateWindowEx(NULL,                       // estilo estendido
                        "BasicWindow",              // classe da janela
                        "Aplicação",                // título da janela
                        WS_OVERLAPPED | WS_SYSMENU, // estilo da janela
                        windowPosX,                 // posição x inicial
                        windowPosY,                 // posição y inicial
                        windowWidth,                // largura inicial
                        windowHeight,               // altura inicial
                        NULL,                       // identificador da janela pai
                        NULL,                       // identificador do menu
                        hInstance,                  // identificador da aplicação
                        NULL);                      // parâmetros de criação

  // o retângulo com o tamanho da área cliente desejada
  RECT winRect = {0, 0, windowWidth, windowHeight};

  // ajuste do tamanho da janela
  AdjustWindowRectEx(&winRect,
                     GetWindowStyle(hwnd),
                     GetMenu(hwnd) != NULL,
                     GetWindowExStyle(hwnd));

  // usado para centralizar janela na tela
  windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
  windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);

  // redimensiona janela com uma chamada a MoveWindow
  MoveWindow(
      hwnd,                         // identificador da janela
      windowPosX,                   // posição x
      windowPosY,                   // posição y
      winRect.right - winRect.left, // largura
      winRect.bottom - winRect.top, // altura
      TRUE);                        // repintar

  // Mostra e atualiza a janela
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  // Tratamento de mensagens destinadas a janela da aplicação
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // fim do programa
  return int(msg.wParam);
}

//-------------------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------