#ifndef LibertyBell_h
#define LibertyBell_h

#include <Arduino.h>

class LibertyBell : public Gameplayer
{      
    Renderer * _lcd;
    uint8_t _x = 1;
    uint8_t _p = 1;
    
    public:
      LibertyBell(Renderer *lcd)
      {
        _lcd = lcd;
      };
      
      void update_inputs()
      {
      }
      
      void update_objects()
      {
        if (_x >= 84 || _x <= 0) {
          _p *= -1;
        }

        _x += 10 * _p;
      }
      
      void handle_actions()
      {
      }
      
      void rendering()
      {
        _lcd->fillDisplayBuffer();
        _lcd->drawImage(test_Bitmap, sizeof(test_Bitmap), _x, 0, 47, 39);
        _lcd->showDisplayBuffer();
      }
  
};

#endif
