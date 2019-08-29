#ifndef Gameplayer_h
#define Gameplayer_h

#include <Arduino.h>

class Gameplayer
{
    Renderer * _lcd;
    public:
      Gameplayer() {};

      virtual void initRenderer(Renderer *lcd) = 0;
            
      virtual void update_inputs() = 0;
      
      virtual void update_objects() = 0;
           
      virtual void handle_actions() = 0;
      
      virtual void rendering() = 0;
};

#endif
