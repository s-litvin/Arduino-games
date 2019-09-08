#ifndef SpaceInvaders_h
#define SpaceInvaders_h

#include <Arduino.h>
#include "Particle.h"

class SpaceInvaders : public Gameplayer
{
    Renderer * _lcd;

    Particle * objects[5];
    
    public:
      SpaceInvaders(Renderer *lcd)
      {
        _lcd = lcd;
        for (byte i = 0; i < 5; i++) {
          objects[i] = new Particle(random(80), random(40));
        }
      };

      void update_inputs()
      {
      }
      
      void update_objects()
      {

        for (byte i = 0; i < 5; i++) {
          Vector center = Vector(42, 24);

          objects[i]->setAccelerationTo(&center, random(1, 50) / 100.0);
          // objects[i]->applyForce(&center);

          objects[i]->velocity->add(objects[i]->acceleration);
          objects[i]->velocity->limit(2);
          objects[i]->location->add(objects[i]->velocity);

          objects[i]->checkBorders();

        }
      }
      
      void handle_actions()
      {
      }
      
      void rendering()
      {

        _lcd->fillDisplayBuffer();
        for (byte i = 0; i < 5; i++) {
          _lcd->drawImage(
                foods4x4, sizeof(foods4x4), 
                objects[i]->location->x, 
                objects[i]->location->y, 
                4, 4, 0);
        }
        _lcd->showDisplayBuffer();
      }

      unsigned int getDelayBetweenFrames()
      {
        return 20;
      }

      static unsigned char * getPreviewImg()
      {
        return space_invaders84x48;
      }
  
};

#endif
