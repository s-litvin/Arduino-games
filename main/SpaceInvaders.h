#ifndef SpaceInvaders_h
#define SpaceInvaders_h

#include <Arduino.h>
#include "Particle.h"


class SpaceInvaders : public Gameplayer
{
    Renderer * _lcd;

    Particle * objects[5];
    Vector * wind;
    Vector * gravity;
    Vector * air;
    
    public:
      SpaceInvaders(Renderer *lcd)
      {
        _lcd = lcd;
        for (byte i = 0; i < 5; i++) {
          objects[i] = new Particle(random(80), random(40));
          objects[i]->mass = i * 5 + 1;
        }
        wind = new Vector(0, 0);
        gravity = new Vector(0, 0.1);
      };

      void update_inputs()
      {
        int pressedA = digitalRead(9);
        int pressedB = digitalRead(4);

        if (pressedA == 0) {
          wind->x = 0.1;
        } else {
          wind->x = 0;
        }

      }
      
      void update_objects()
      {

        // Vector center = Vector(42, 24);   

        for (byte i = 0; i < 5; i++) {
          // objects[i]->setAccelerationTo(&center, 0.08);

          // air friction ///

          if (objects[i]->velocity->getMag() != 0) {
            Vector tmpVector = Vector(objects[i]->velocity->x, objects[i]->velocity->y);
            tmpVector.mult(-1);
            tmpVector.normalize();
            if (digitalRead(4) == 0) {
              tmpVector.mult(0.3);
            } else {
              tmpVector.mult(0.03);
            }
            objects[i]->applyForce(&tmpVector);
          }
          //////////////////

          // gravity ///
          Vector tmpVector = Vector(gravity->x, gravity->y);   
          tmpVector.y *= objects[i]->mass;
          objects[i]->applyForce(&tmpVector); // gravity
          /////////////

          // wind ///
          objects[i]->applyForce(wind);
          ///////////

          objects[i]->acceleration->div(objects[i]->mass);
        
          objects[i]->velocity->add(objects[i]->acceleration);
          objects[i]->velocity->limit(2);
          objects[i]->location->add(objects[i]->velocity);

          objects[i]->acceleration->mult(0);

          objects[i]->checkBorders();

          // _lcd->printMemory();
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
