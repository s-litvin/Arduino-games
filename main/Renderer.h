#ifndef Renderer_h
#define Renderer_h

#define RST 7
#define CE  6
#define DC  5
#define DIN  4
#define CLK  3

#include <Arduino.h>
#include "font.h";
#include "images.h";

class Renderer 
{
 
    public:
    
      byte display_buffer[6][84];
      
      Renderer() 
      {
        pinMode(RST, OUTPUT);
        pinMode(CE, OUTPUT);
        pinMode(DC, OUTPUT);
        pinMode(DIN, OUTPUT);
        pinMode(CLK, OUTPUT);
        digitalWrite(RST, LOW);
        digitalWrite(RST, HIGH);
      };

      void init()
      {
        LcdWriteCmd(0x21);  // LCD extended commands
        LcdWriteCmd(0xbf);  // set LCD Vop (contrast)
        LcdWriteCmd(0x04);  // set temp coefficent
        LcdWriteCmd(0x14);  // LCD bias mode 1:40
        LcdWriteCmd(0x20);  // LCD basic commands
        LcdWriteCmd(0x0c);  // LCD normal video

        for(int i=0; i<504; i++) LcdWriteData(0x00); // clear LCD

        fillDisplayBuffer();

        drawImage(main_logo84x48, sizeof(main_logo84x48), 0, 0, 84, 48);
        showDisplayBuffer();
        delay(3500);

        fillDisplayBuffer();
        showDisplayBuffer();
        delay(500);
      }
       
      void drawImage(const uint8_t *image, int imageSize, byte posX, byte posY, byte sizeX, byte sizeY, byte shiftBits = 0, bool showImmediately = false)
      {  
        int bitmapSize = imageSize;
        unsigned int bloc_number = 0;
        int current_bit = 7;
        unsigned char memory_block = pgm_read_word_near(image + bloc_number);
        unsigned char tmp_block = memory_block;

        for(int x = posX; x < (posX + sizeX);  x++) {
          for(int y = posY; y < (posY + sizeY);  y++) {
            if (bloc_number < bitmapSize) {
              if (current_bit < 0) {
                current_bit = 7;
                bloc_number++; 
                memory_block = pgm_read_word_near(image + bloc_number);
                tmp_block = memory_block;
              }

              putToBuffer((tmp_block >> (current_bit - shiftBits) ) & 1, x, y, showImmediately);
              current_bit--;
            }
          }
          bloc_number++;
          current_bit = 7;
          memory_block = pgm_read_word_near(image + bloc_number);
          tmp_block = memory_block;
        }
      }

      byte getPixelFromBuffer(char posX, char posY)
      {
        uint8_t column = map(posY, 0, 48, 0, 6);
        return 1 & (display_buffer[column][posX] >> (posY - column * 8));
      }
      
      void fillDisplayBuffer(uint8_t value = 0, bool fillWithRandom = false)
      {
        for (uint8_t i=0; i < 6; i++) {
          for (uint8_t j=0; j < 84; j++) {
            if (fillWithRandom) {
              display_buffer[i][j] = random(255);
            } else {
              display_buffer[i][j] = value;
            }
          }  
        }
      }
      
      void putToBuffer(char value, char posX, char posY, bool showImmediately = false)
      {
        uint8_t column = map(posY, 0, 48, 0, 6);
        byte shift = value << (posY - column * 8);

        byte clear_position = -1 ^ shift;
        display_buffer[column][posX] &= clear_position;
        display_buffer[column][posX] |= shift;   
      
        if (showImmediately) {
          cursorToXY(posX, column);
          LcdWriteData(display_buffer[column][posX]);
        }
      }
      
      void showDisplayBuffer()
      {
          for (uint8_t i=0; i < 6; i++) {
            cursorToXY(0, i);
            for (uint8_t j=0; j < 84; j++) {
              LcdWriteData(display_buffer[i][j]);
            }  
          }     
      }
      
      void LcdWriteCmd(byte cmd)
      {
        digitalWrite(DC, LOW); //DC pin is low for commands
        transmitData(cmd);
      }
      
      void LcdWriteData(byte data)
      {
        digitalWrite(DC, HIGH); //DC pin is high for data
        transmitData(data);
      }
      
      void transmitData(byte data)
      {
        digitalWrite(CE, LOW);
        shiftOut(DIN, CLK, MSBFIRST, data); //transmit serial data
        digitalWrite(CE, HIGH);
      }
      
      void LcdWriteString(char *characters)
      {
        while(*characters) LcdWriteCharacter(*characters++);
      }
      
      void LcdWriteCharacter(char character)
      {
        for(char i=0; i<5; i++) {
          LcdWriteData(pgm_read_byte(&(ASCII[character - 0x20][i])));
        }
        LcdWriteData(0x00);
      }
      
      void cursorToXY(int x, int y)
      {
        LcdWriteCmd(0x80 | x);  // Column.
        LcdWriteCmd(0x40 | y);  // Row.
      }

};

#endif
