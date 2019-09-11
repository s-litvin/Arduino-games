#ifndef Controls_h
#define Controls_h

#include <Arduino.h>

#define BUTTON 8
#define BUTTONA 9
#define BUTTONB 4

class Controls 
{
 
  public:
      
    Controls() 
    {
      pinMode(BUTTON, INPUT_PULLUP);
      pinMode(BUTTONA, INPUT_PULLUP);
      pinMode(BUTTONB, INPUT_PULLUP);
    };

    boolean isPressedA()
    {
      return digitalRead(BUTTONA) == 0;
    }

    boolean isPressedB()
    {
      return digitalRead(BUTTONB) == 0;
    }

    boolean isPressedCenter()
    {
      return digitalRead(BUTTON) == 0;
    }

    boolean isPressedLeft()
    {
      return map(analogRead(A0), 0, 1024, -1, 2) == -1;
    }

    boolean isPressedRight()
    {
      return map(analogRead(A0), 0, 1024, -1, 2) == 1;
    }

    boolean isPressedUp()
    {
      return map(analogRead(A1), 0, 1024, -1, 2) == 1;    
    }

    boolean isPressedDown()
    {
      return map(analogRead(A1), 0, 1024, -1, 2) == -1;    
    }

    char getDirectionX()
    {
      return map(analogRead(A0), 0, 1024, -1, 2);    
    }

    char getDirectionY()
    {
      return map(analogRead(A1), 0, 1024, -1, 2);
    }

};

#endif
