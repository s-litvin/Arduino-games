#ifndef Vector_h
#define Vector_h

#include <Arduino.h>

class Vector
{   

    public:

      float x;
      float y;

      Vector(float _x, float _y)
      {
        x = _x;
        y = _y;
      };

      void add(Vector * v)
      {
        x += v->x;
        y += v->y;
      }
      
      void sub(Vector * v)
      {
        x -= v->x;
        y -= v->y;        
      }
      
      void mult(float value)
      {
        x *= value;
        y *= value;
      }
      
      void div(float value)
      {
        x /= value;
        y /= value;
      }

      void normalize()
      {
        x /= getMag();
        y /= getMag();
      }

      void limit(float value)
      {
        if (getMag() > value) {
          setMag(value);
        }
      }

      float getMag()
      {
        return sqrt(x * x + y * y);
      }

      void setMag(float value)
      {
        normalize();
        mult(value);
      }
};

#endif
