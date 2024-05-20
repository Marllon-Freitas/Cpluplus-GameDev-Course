/**********************************************************************************
// Engine (Arquivo de Cabeçalho)
//
// Descrição:   A função da Engine é rodar jogos criados a partir da classe
//              abstrata Game. Todo jogo deve ser uma classe derivada de Game
//              e portanto deve implementar as funções membro Init, Update, Draw
//              e Finalize, que serão chamadas pelo motor em um laço de tempo real.
//              Para usar a classe Engine, o programador deve criar uma instância
//              e chamar o método Start(), passando um objeto derivado de Game.
//
**********************************************************************************/

#ifndef _PROGJOGOS_ENGINE_H_
#define _PROGJOGOS_ENGINE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"                       // implementação do jogo
#include "Window.h"                     // janela do jogo
#include "Graphics.h"                   // hardware gráfico
#include "Timer.h"                      // medidor de tempo

// ---------------------------------------------------------------------------------

class Engine
{
private:
    static Timer timer;                 // medidor de tempo
    static bool paused;                 // estado do jogo

    float FrameTime();                  // calcula o tempo do quadro
    int   Loop();                       // inicia execução do jogo

public:
    static Game     * game;             // jogo a ser executado
    static Window   * window;           // janela do jogo
    static Graphics * graphics;         // dispositivo gráfico
    static float      frameTime;		// tempo do quadro atual

    Engine();                           // construtor
    ~Engine();                          // destrutor

    int Start(Game* level);             // inicia a execução do jogo
    
    static void Pause();				// pausa o jogo
    static void Resume();				// reinicia o jogo
};

// ---------------------------------------------------------------------------------

#endif