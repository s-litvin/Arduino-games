#include "Renderer.h";
#include "Gameplayer.h"
#include "Snake.h";
#include "SpaceInvaders.h";
#include "LibertyBell.h";

Renderer lcd = Renderer();
Gameplayer * game;


void setup()
{
  lcd.init();

  switch(1) {
    case 1:
      game = new Snake(&lcd);
      break;
    case 2:
      game = new SpaceInvaders(&lcd);
      break;
    case 3:
      game = new LibertyBell(&lcd);
      break;
  }
}

void loop()
{ 

    game->update_inputs(); 
    game->update_objects(); 
    game->handle_actions(); 
    game->rendering(); 

    delay(800);

}

