#ifndef LibertyBell_h
#define LibertyBell_h

#include <Arduino.h>

class LibertyBell : public Gameplayer
{    
    #define BUTTON 8    

    Renderer * _lcd;
    uint8_t _x = 1;
    uint8_t _p = 1;

    byte symbols[6];
    byte rotations = 0;
    
    public:
      LibertyBell(Renderer *lcd)
      {
        _lcd = lcd;

        for (byte i = 0; i < 6; i++) {
          symbols[i] = random(1, 4);
        } 

        _lcd->fillDisplayBuffer(0xff);
        rendering();
        _lcd->showDisplayBuffer();
      };
      
      void update_inputs()
      {
        if (rotations == 0) {
          char direction = 0;
          while (digitalRead(BUTTON) && direction == 0) {
            direction = map(analogRead(A1), 0, 1024, -1, 2);
          }
          rotations = 10;
        }
      }
      
      void update_objects()
      {
        if (rotations > 0) {
          
          for (byte i = 0; i < 3; i++) {
            symbols[3 + i] = symbols[i];
          }
          
          for (byte i = 0; i < 3; i++) {
            symbols[i] = random(1, 4);
          }

          rotations--; 
        } 
      }
      
      void handle_actions()
      {
      }
      
      void rendering()
      {
        char positions[6][2] = {
          {4, 5}, {24, 5}, {44, 5},
          {4, 21}, {24, 21}, {44, 21}
        };
        for(char i = 0; i < 6; i++) {
          switch (symbols[i]) {
            case 1:
              _lcd->drawImage(cherry16x16, sizeof(cherry16x16), positions[i][0], positions[i][1], 16, 16, 0, true);
              break;
            case 2:
              _lcd->drawImage(seven16x16, sizeof(seven16x16), positions[i][0], positions[i][1], 16, 16, 0, true);
              break;
            case 3:
              _lcd->drawImage(peach16x16, sizeof(peach16x16), positions[i][0], positions[i][1], 16, 16, 0, true);
              break;
          }
        }
                
      }

      unsigned int getDelayBetweenFrames()
      {
        return 5;
      }
  
};

#endif
