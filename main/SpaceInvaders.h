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

    Particle * rocket;
    Vector * vars;

    public:
      SpaceInvaders(Renderer *lcd)
      {
        _lcd = lcd;
        rocket = new Particle(20, 10);
        rocket->mass = 150;
        vars = new Vector(0, 0); 
      };

      void update_inputs()
      {
        
      }
      
      void update_objects()
      {
        // Vector center = Vector(42, 24);   
        // rocket->setAccelerationTo(&center, 0.08);

        //// gravity ///
        vars->x = 0;
        vars->y = 0.04; 
        vars->mult(rocket->mass);
        rocket->applyForce(vars); // gravity
        /////////////

        //// air friction with drag ///
        if (rocket->velocity->getMag() != 0) {
          vars->x = rocket->velocity->x;
          vars->y = rocket->velocity->y;
          vars->normalize();
          vars->mult(-0.01 * rocket->velocity->getMag() * rocket->velocity->getMag());
          rocket->applyForce(vars);
        }
        //////////////////

        ////// throast ///
        int degree = map(analogRead(A0), 0, 1024, 2, -2);
        if (degree != 0) {
          rocket->orientation->rotate(2 * degree);
        }

        if (digitalRead(BUTTONA) == 0) {
          vars->x = rocket->orientation->x;
          vars->y = rocket->orientation->y;
          vars->normalize();
          vars->mult(9);
          rocket->applyForce(vars);
        }
        //////////////////

        //// mass 
        rocket->acceleration->div(rocket->mass);
        rocket->velocity->add(rocket->acceleration);


        //////// COLLISIONS ///////////
        if ((rocket->location->x + rocket->velocity->x) > (80)) {
          rocket->location->x = 0;
        } else if ((rocket->location->x + rocket->velocity->x) < 0) {
          rocket->location->x = 80;
        }

        if (
          (rocket->location->y + rocket->velocity->y) > 40 ||
          (rocket->location->y + rocket->velocity->y) <= 1
        ) {
        
          if (rocket->velocity->y > 0) { // if directed down
            rocket->velocity->y *= -0.49; // collisions grab energy   
          } else {
            rocket->velocity->y *= -1;
          }
          
          if (sqrt(rocket->velocity->y * rocket->velocity->y) < 0.08 && vars->y == 0) { // treshhold
            rocket->velocity->y = 0;
          }
          rocket->velocity->x -= rocket->velocity->x * 0.04; // ground friction
        }

        if (sqrt(rocket->velocity->x * rocket->velocity->x) < 0.01) { // treshhold
          rocket->velocity->x = 0;
        }

        
        ////////////////////////////

        rocket->velocity->limit(1);
        rocket->location->add(rocket->velocity);
        rocket->acceleration->mult(0);

        // rocket->checkBorders();
        // _lcd->printMemory();
        
      }

      
      void handle_actions()
      {
      }
      
      void rendering()
      {
        _lcd->fillDisplayBuffer();         

        _lcd->drawImage(
              rocket4x8, sizeof(rocket4x8), 
              rocket->location->x, 
              rocket->location->y, 
              4, 8, 0);

        for (int i = 0; i < 10; i++) {
          _lcd->putToBuffer(1, 45 + i, 46, false);
        }

        vars->x = rocket->orientation->x;
        vars->y = rocket->orientation->y;
        vars->mult(0.2);
        _lcd->putToBuffer(1, 42, 24, false);
        vars->mult(20);
        _lcd->putToBuffer(1, vars->x + 42, vars->y + 24, false);
        vars->mult(2);
        _lcd->putToBuffer(1, vars->x + 42, vars->y + 24, false);
        vars->mult(1.3);
        _lcd->putToBuffer(1, vars->x + 42, vars->y + 24, false);

        _lcd->showDisplayBuffer();
      }

      unsigned int getDelayBetweenFrames()
      {
        return 20;
      }
  
};

#endif
