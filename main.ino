#include "Renderer.h";
#include "Gameplayer.h"
#include "Snake.h";
#include "SpaceInvaders.h";

Renderer lcd = Renderer();
Gameplayer * game;

Snake snakeGame = Snake();
SpaceInvaders invadersGame = SpaceInvaders();

void setup()
{
  lcd.init();

  if (true) { // game switching
    game = &snakeGame;
  } else {
    game = &invadersGame;
  }
  
  game->initRenderer(&lcd);
}

void loop()
{ 

    game->update_inputs(); 
    game->update_objects(); 
    game->handle_actions(); 
    game->rendering(); 

}




