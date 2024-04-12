/*
Usando as classes Window e Game desenvolvidas na aula, crie uma
aplicação para desenhar uma linha que se movimente e rebata nas
bordas da janela.

Para isso utilize as funções LineTo e MoveToEx da biblioteca do Windows:
BOOL LineTo(
    HDC hdc,  // contexto do dispositivo
    int endX, // posição final no eixo x
    int endY  // posição final no eixo y
);
BOOL MoveToEx(
    HDC hdc,   // contexto do dispositivo
    int X,     // posição no eixo x
    int Y,     // posição no eixo y
    LPPOINT lp // guarda última coordenada em um POINT
);

O contexto do dispositivo gráfico pode ser obtido com a função GetDC
e liberado com a função ReleaseDC:
HDC hdc = GetDC(hwnd);
// utilizar dispositivo aqui
ReleaseDC(hwnd, hdc);
*/

#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include <random> // inclui funções de números aleatórios
using namespace std;
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class WinGame : public Game
{
private:
  HDC hdc;
  int xIni, yIni, xFim, yFim;
  int velXIn, velXFim, velYIn, velYFim;

public:
  void Init();
  void Update();
  void Draw();
  void Finalize();
};

// ------------------------------------------------------------------------------

void WinGame::Init()
{
  hdc = GetDC(window->Id());
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(1, 50);
  uniform_int_distribution<int> vel(1, 20);

  HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
  HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

  velXIn = vel(gen);
  velXFim = vel(gen);
  velYIn = vel(gen);
  velYFim = vel(gen);

  xIni = dis(gen);
  yIni = dis(gen);
  xFim = dis(gen);
  yFim = dis(gen);
}

// ------------------------------------------------------------------------------

void WinGame::Update()
{
  if (window->KeyDown(VK_ESCAPE))
    window->Close();

  xIni += velXIn;
  yIni += velYIn;
  xFim += velXFim;
  yFim += velYFim;

  if (xIni < 0 || xIni > window->Width())
    velXIn = -velXIn;

  if (yIni < 0 || yIni > window->Height())
    velYIn = -velYIn;

  if (xFim < 0 || xFim > window->Width())
    velXFim = -velXFim;

  if (yFim < 0 || yFim > window->Height())
    velYFim = -velYFim;

  MoveToEx(hdc, xIni, yIni, NULL);
}

// ------------------------------------------------------------------------------

void WinGame::Draw()
{
  LineTo(hdc, xFim, yFim);
}

// ------------------------------------------------------------------------------

void WinGame::Finalize()
{
  ReleaseDC(window->Id(), hdc);
}

// ------------------------------------------------------------------------------
//                                  WinMain
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
  // cria motor e configura a janela
  Engine *engine = new Engine();
  engine->window->Mode(WINDOWED);
  engine->window->Size(960, 540);
  engine->window->Color(30, 30, 30);
  engine->window->Title("Window Game");
  engine->window->Icon(IDI_ICON);
  engine->window->Cursor(IDC_CURSOR);

  // cria e inicia o jogo
  engine->Start(new WinGame());
}

// ----------------------------------------------------------------------------
