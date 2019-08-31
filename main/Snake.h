#ifndef Snake_h
#define Snake_h

#include <Arduino.h>

class Snake : public Gameplayer
{      
    Renderer * _lcd;

    byte snake[252];
    
    public:
      Snake(Renderer *lcd)
      {
        _lcd = lcd;

        // fill snake
        for (byte i = 0; i < 251; i++) {
          if (i <= 5) {
            snake[i] =  5 - i;
          } else {
            snake[i] = 255;  // 255 - cell is empty
          }
        }

      };
        
      void update_inputs()
      {
      }
      
      void update_objects()
      {
        // fill snake
        for (int i = 251; i >= 0; i--) {
          if (snake[i] != 255) {
            if (i > 0) {
              snake[i] =  snake[i - 1];
            } else {
              if (snake[i] != 251) {
                snake[i] = snake[i] + 1;
              } else {
                snake[i] = 0;
              }
              
            }
          }
        }
      }
      
      void handle_actions()
      {
      }
      
      void rendering()
      {
        _lcd->fillDisplayBuffer();
        
        for (byte i = 0; i < 251; i++) {
          if (snake[i] != 255) {
            _lcd->drawImage(
              circle_hollow4x4, sizeof(circle_hollow4x4), 
              getXPositionFromCellNumber(snake[i]), 
              getYPositionFromCellNumber(snake[i]), 
              4, 4);   
          }
        }
        
        _lcd->showDisplayBuffer();
      }

      int getXPositionFromCellNumber(byte cell_number)
      {
        return (cell_number % 21) * 4;
      }

      int getYPositionFromCellNumber(byte cell_number)
      {
        return (cell_number / 21) * 4;
      }
  
};

#endif
