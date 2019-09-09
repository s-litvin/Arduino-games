#ifndef SpaceInvaders_h
#define SpaceInvaders_h

#include <Arduino.h>
#include <Particle.h>

#define BUTTON 8
#define BUTTONA 9
#define BUTTONB 4


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
          objects[i] = new Particle(5 * i + 20, 10);
          objects[i]->mass = (i + 1) * 3;
        }
        wind = new Vector(0, 0);
        gravity = new Vector(0, 0.1);
      };

      void update_inputs()
      {
        if (digitalRead(BUTTONA) == 0) {
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

          //// gravity ///
          Vector tmpVector = Vector(gravity->x, gravity->y);   
          tmpVector.y *= objects[i]->mass;
          objects[i]->applyForce(&tmpVector); // gravity
          /////////////


          //// wind ///
          objects[i]->applyForce(wind);
          ///////////

          //// air friction ///
          if (objects[i]->velocity->getMag() != 0) {
            Vector tmpVector = Vector(objects[i]->velocity->x, objects[i]->velocity->y);
            tmpVector.mult(-1);
            // tmpVector.normalize();
            if (digitalRead(BUTTONB) == 0) {
              tmpVector.mult(5);
            } else {
              tmpVector.mult(0);
            }
            objects[i]->applyForce(&tmpVector);
          }
          //////////////////

          objects[i]->acceleration->div(objects[i]->mass);
          objects[i]->velocity->add(objects[i]->acceleration);


          objects[i]->velocity->limit(random(1, 7));
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
  
};

#endif
