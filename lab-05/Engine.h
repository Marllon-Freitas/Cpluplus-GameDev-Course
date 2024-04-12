#ifndef _PROGJOGOS_ENGINE_H_
#define _PROGJOGOS_ENGINE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"   // implementação do jogo
#include "Window.h" // janela do jogo

// ---------------------------------------------------------------------------------

class Engine
{
private:
  int Loop(); // inicia o laço de tempo real

public:
  static Game *game;     // jogo a ser executado
  static Window *window; // janela do jogo

  Engine();  // construtor
  ~Engine(); // destrutor

  int Start(Game *level); // inicia a execução do jogo
};

// ---------------------------------------------------------------------------------

#endif