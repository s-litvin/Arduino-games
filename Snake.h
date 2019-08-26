#ifndef Snake_h
#define Snake_h

#include <Arduino.h>

class Snake : public Gameplayer
{
    Renderer * _lcd;
    public:
      Snake(){};

      void initRenderer(Renderer *lcd)
      {
        _lcd = lcd;
      }
        
      void update_inputs()
      {
      }
      
      void update_objects()
      {
      }
      
      void handle_actions()
      {
      }
      
      void rendering()
      {
        _lcd->drawImage(test_Bitmap, sizeof(test_Bitmap), 0, 0, 47, 39);
        _lcd->showDisplayBuffer();
      }
  
};

#endif
