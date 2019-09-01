#ifndef SpaceInvaders_h
#define SpaceInvaders_h

#include <Arduino.h>

class SpaceInvaders : public Gameplayer
{
    Renderer * _lcd;
    uint8_t _x = 1;
    uint8_t _p = 1;
    
    public:
      SpaceInvaders(Renderer *lcd)
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
        _lcd->drawImage(space_invaders84x48, sizeof(space_invaders84x48), _x, 0, 84, 48);
        _lcd->showDisplayBuffer();
      }

      static unsigned char * getPreviewImg()
      {
        return space_invaders84x48;
      }
  
};

#endif
