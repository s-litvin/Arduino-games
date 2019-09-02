#ifndef Gameplayer_h
#define Gameplayer_h

#include <Arduino.h>

class Gameplayer
{
    Renderer * _lcd;
    public:
      Gameplayer() {};
            
      virtual void update_inputs() = 0;
      
      virtual void update_objects() = 0;
           
      virtual void handle_actions() = 0;
      
      virtual void rendering() = 0;

      virtual unsigned int getDelayBetweenFrames() = 0;

      static unsigned char * getPreviewImg(){};
      
};

#endif
