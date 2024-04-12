#include "Engine.h"
#include <windows.h>
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Game *Engine::game = nullptr;     // jogo em execução
Window *Engine::window = nullptr; // janela do jogo

// -------------------------------------------------------------------------------

Engine::Engine()
{
    window = new Window();
}

// -------------------------------------------------------------------------------

Engine::~Engine()
{
    delete game;
    delete window;
}

// -----------------------------------------------------------------------------

int Engine::Start(Game *level)
{
    game = level;

    // cria janela do jogo
    window->Create();

    // retorna resultado da execução do jogo
    return Loop();
}

// -------------------------------------------------------------------------------

int Engine::Loop()
{
    MSG msg = {0}; // mensagem do Windows
    HDC hdc;       // contexto do dispositivo
    RECT rect;     // área cliente da tela

    // captura contexto do dispositivo
    hdc = GetDC(window->Id());

    // pega tamanho da área cliente
    GetClientRect(window->Id(), &rect);

    // inicialização do jogo
    game->Init();

    // laço principal do jogo
    do
    {
        // trata todos os eventos antes de atualizar o jogo
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // atualização do jogo
            game->Update();

            // limpa a área cliente
            FillRect(hdc, &rect, CreateSolidBrush(window->Color()));

            // desenha o jogo
            game->Draw();

            Sleep(16); // controle de FPS (quebra galho)
        }

    } while (msg.message != WM_QUIT);

    // finalização do jogo
    game->Finalize();

    // libera contexto do dispositivo
    ReleaseDC(window->Id(), hdc);

    // encerra aplicação
    return int(msg.wParam);
}

// -----------------------------------------------------------------------------
