#include "Renderer.h";
#include "Gameplayer.h"
#include "Snake.h";
#include "SpaceInvaders.h";
#include "LibertyBell.h";

#define BUTTON 8
#define BUTTONA 9
#define BUTTONB 4

Renderer lcd = Renderer();
Gameplayer * game;


void setup()
{

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUTTONA, INPUT_PULLUP);
  pinMode(BUTTONB, INPUT_PULLUP);

  lcd.init();

  byte choice = 0;
  char page = 1;

  while (choice == 0) {
    lcd.cursorToXY(1, 2);
    for (byte i = 0; i < 7; i++) lcd.LcdWriteString(" "); // clear LCD
    lcd.cursorToXY(1, 2);
    delay(200);
    switch(page) {
      case 1:
        lcd.LcdWriteString("Snake");
        // lcd.drawImage(Snake::getPreviewImg(), 504, 0, 0, 84, 48);
        break;
      case 2:
        lcd.LcdWriteString("Rocket");
        // lcd.drawImage(SpaceInvaders::getPreviewImg(), 504, 0, 0, 84, 48);
        break;
      case 3:
        lcd.LcdWriteString("Slot");
        // lcd.drawImage(LibertyBell::getPreviewImg(), 504, 0, 0, 84, 48);
        break;
    }
    // lcd.showDisplayBuffer();

    char direction = 0;
    char not_pressed = 1;
    while (direction == 0 && not_pressed == 1) {
      direction = -1 * map(analogRead(A0), 0, 1024, -1, 2);
      not_pressed = digitalRead(BUTTON) && digitalRead(BUTTONA) && digitalRead(BUTTONB);
    }

    page = page + direction;

    if (page > 3) {
      page = 1;
    } else if (page == 0) {
      page = 3;
    }

    if (!not_pressed) {
      choice = page;
    }
  }

  switch(page) {
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

    delay(game->getDelayBetweenFrames());

}

