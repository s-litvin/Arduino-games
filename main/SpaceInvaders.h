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

    Particle * objects[2];
    // Vector * wind;
    Vector * gravity;
    Vector * air;
    Vector * throast;

    public:
      SpaceInvaders(Renderer *lcd)
      {
        _lcd = lcd;

        for (byte i = 0; i < 2; i++) {
          objects[i] = new Particle((i + 1) * 10, 10);
          objects[i]->mass = (i + 1) * 10;
          
        }

        // wind = new Vector(0, 0);
        gravity = new Vector(0, 0.01);
        throast = new Vector(0, 0); 
      };

      void update_inputs()
      {
        
      }
      
      void update_objects()
      {

        // Vector center = Vector(42, 24);   

        for (byte i = 0; i < 2; i++) {
          // objects[i]->setAccelerationTo(&center, 0.08);

          //// gravity ///
          Vector tmpVector = Vector(gravity->x, gravity->y);   
          tmpVector.y *= objects[i]->mass;
          objects[i]->applyForce(&tmpVector); // gravity
          objects[i]->applyForce(gravity);
          /////////////

          //// air friction ///
          if (objects[i]->velocity->getMag() != 0) {
            tmpVector = Vector(objects[i]->velocity->x, objects[i]->velocity->y);
            tmpVector.normalize();
            tmpVector.mult(-0.01);
            objects[i]->applyForce(&tmpVector);
          }
          //////////////////

          ////// throast ///
          int degree = -1 * map(analogRead(A0), 0, 1024, -1, 2);
          if (degree > 0) {
            objects[i]->orientation->rotate(degree);
          }

          if (digitalRead(BUTTONA) == 0) {
            tmpVector = Vector(objects[i]->orientation->x, objects[i]->orientation->y);
            tmpVector.normalize();
            tmpVector.mult(0.3);
            objects[i]->applyForce(&tmpVector);
          }
          //////////////////

          objects[i]->acceleration->div(objects[i]->mass);

          objects[i]->velocity->add(objects[i]->acceleration);

          objects[i]->velocity->limit(1);

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
        for (byte i = 0; i < 2; i++) {

          
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
