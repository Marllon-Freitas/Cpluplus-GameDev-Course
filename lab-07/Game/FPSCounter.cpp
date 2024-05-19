/**********************************************************************************
// FPSCounter
//
// Descrição:   Ilustra utilização da classe Timer e Game para controlar
//              a taxa de atualização e desenho de quadros em um jogo.
//
**********************************************************************************/

#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include "Timer.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class FPSCounter : public Game
{
private:

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

// ------------------------------------------------------------------------------

void FPSCounter::Init()
{
}

// ------------------------------------------------------------------------------

void FPSCounter::Update()
{
	if (window->KeyDown(VK_ESCAPE))
		window->Close();
}

// ------------------------------------------------------------------------------

void FPSCounter::Draw()
{
}

// ------------------------------------------------------------------------------

void FPSCounter::Finalize()
{
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Timer timer;
	timer.Start();

	// cria engine
	Engine* engine = new Engine();

	// configura a janela
	engine->window->Mode(WINDOWED);
	engine->window->Size(960, 540);
	engine->window->Color(240, 240, 140);
	engine->window->Title("FPSCounter");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	float timePassed = timer.Elapsed();
	stringstream textTimer;
	textTimer << " ---> Time passed: " << timePassed;

	OutputDebugString(textTimer.str().c_str());

	// configura dispositivo gráfico
	// engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new FPSCounter());

	// destrói a engine  
	delete engine;
	return status;
}

// ----------------------------------------------------------------------------
