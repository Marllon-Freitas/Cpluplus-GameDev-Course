/*
Considerando a arquitetura de um jogo apresentada na aula, utilize as
funções GameInit, GameUpdate, GameDraw e GameFinalize para
plotar pixels em posições aleatórias da janela.

Para isso utilize a função SetPixel da biblioteca do Windows:
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor);

O dispositivo pode ser obtido com GetDC e liberado com ReleaseDC:
HDC hdc = GetDC(hwnd);
// utiliza dispositivo gráfico aqui
ReleaseDC(hwnd, hdc);

Uma cor do tipo COLORREF pode ser obtida com a macro RGB:
COLORREF color = RGB(255,255,255);
As cores R(Red), G(Green) e B(Blue) variam de 0 a 255.
Uma cor RGB(0,0,0) é a cor preta e RGB(255,255,255) é a cor branca.

A geração de números aleatórios pode ser feita com random:
#include <iostream>
#include <random>
using namespace std;
int main()
{
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> dist(0, 99);
  for (int i = 0; i < 10; ++i)
    cout << dist(mt) << " ";
  cout << endl;
  return 0;
}
*/

#include <windows.h>   // inclui funções do windows
#include <windowsx.h>  // inclui funções extras do windows
#include "Resources.h" // definições dos recursos utilizados
#include <random>      // inclui funções de números aleatórios
using namespace std;

// protótipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

// -----------------------------------------------------------------------
// constantes, variáveis e funções globais

int windowWidth = 960;   // largura da janela
int windowHeight = 540;  // altura da janela
bool fullScreen = false; // tela cheia ou modo janela

bool vkKeys[256] = {0}; // estado das teclas do teclado
HWND hwnd;              // identificador da janela
HDC hdc;                // contexto de dispositivo gráfico
int x, y;               // coordenadas dos pixels
COLORREF color;         // cor dos pixels

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> randWidth(0, windowWidth);
uniform_int_distribution<int> randHeight(0, windowHeight);

// valores aleatórios para R, G e B
uniform_int_distribution<int> randColor(0, 255);

// -----------------------------------------------------------------------
// funções do jogo

// inicializa o jogo alocando recursos
void GameInit()
{
  hdc = GetDC(hwnd);
  x = randWidth(mt);
  y = randHeight(mt);
  color = RGB(randColor(mt), randColor(mt), randColor(mt));
}

// atualiza a lógica do jogo
void GameUpdate()
{
  // sai com o pressionamento da tecla ESC
  if (vkKeys[VK_ESCAPE])
    PostMessage(hwnd, WM_DESTROY, 0, 0);

  x = randWidth(mt);
  y = randHeight(mt);

  color = RGB(randColor(mt), randColor(mt), randColor(mt));
}

// desenha o próximo quadro do jogo
void GameDraw()
{
  SetPixel(hdc, x, y, color);
}

// finaliza o jogo desalocando recursos
void GameFinalize()
{
  ReleaseDC(hwnd, hdc);
}

// -----------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
  MSG msg;
  WNDCLASS wndclass;

  // definindo uma classe de janela chamada "GameWindow"
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = WinProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
  wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
  wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = "GameWindow";

  // registrando "GameWindow"
  if (!RegisterClass(&wndclass))
  {
    MessageBox(NULL, "Erro na criação da janela!", "Game", MB_ICONERROR);
    return 0;
  }

  int windowStyle = WS_OVERLAPPED | WS_SYSMENU;

  // tela cheia ou janela
  if (fullScreen)
  {
    windowWidth = GetSystemMetrics(SM_CXSCREEN);
    windowHeight = GetSystemMetrics(SM_CYSCREEN);
    windowStyle = WS_POPUP;
  }

  // criando uma janela baseada na classe "GameWindow"
  // é necessário usar CreateWindowEx para usar AdjustWindowRectEx
  hwnd = CreateWindowEx(
      NULL,          // estilos extras
      "GameWindow",  // nome da "window class"
      "Game",        // título da janela
      windowStyle,   // estilo da janela
      CW_USEDEFAULT, // posição x inicial
      CW_USEDEFAULT, // posição y inicial
      windowWidth,   // largura da janela
      windowHeight,  // altura da janela
      NULL,          // identificador do objeto pai
      NULL,          // identificador do menu
      hInstance,     // identificador da aplicação
      NULL);         // parâmetros de criação

  if (!fullScreen)
  {
    // retângulo com o tamanho da área cliente desejada
    RECT winRect = {0, 0, windowWidth, windowHeight};

    // ajuste do tamanho da janela
    AdjustWindowRectEx(&winRect,
                       GetWindowStyle(hwnd),
                       GetMenu(hwnd) != NULL,
                       GetWindowExStyle(hwnd));

    // atualiza posição da janela
    int windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
    int windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);

    // redimensiona janela com uma chamada a MoveWindow
    MoveWindow(
        hwnd,                         // identificador da janela
        windowPosX,                   // posição x
        windowPosY,                   // posição y
        winRect.right - winRect.left, // largura
        winRect.bottom - winRect.top, // altura
        TRUE);                        // repintar
  }

  // mostra e atualiza a janela
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  GameInit();

  // loop principal do jogo
  do
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      GameUpdate();
      GameDraw();
    }
  } while (msg.message != WM_QUIT);

  GameFinalize();

  // fim do programa
  return int(msg.wParam);
}

// -----------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    // processa teclas pressionadas
  case WM_KEYDOWN:
    vkKeys[wParam] = true;
    return 0;

    // processa teclas liberadas
  case WM_KEYUP:
    vkKeys[wParam] = false;
    return 0;

    // janela foi fechada
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hwnd, message, wParam, lParam);
}

// -----------------------------------------------------------------------