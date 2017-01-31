/*
  OLED_SSD1306.h - for ESP-WROOM-02 ( esp8266 ) or Arduino
  Beta version 1.6

The MIT License (MIT)

Copyright (c) 2016 Mgo-tec
Blog URL ---> https://www.mgo-tec.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef OLED_SSD1306_h_
#define OLED_SSD1306_h_
#include "Arduino.h"
#include "Wire.h"

class OLED_SSD1306
{
public:
  OLED_SSD1306();
  void setup_OLED_SSD1306(uint8_t Addres);
  void Ini_OLED_SSD1306(uint8_t Addres, uint8_t Contrast);
  void OLED_1x1_Display_Out_8x16(uint8_t Addres, uint8_t* Dot1, uint8_t* Dot2, uint8_t* Dot3, uint8_t* Dot4);
  void Dot_2X2_convert(uint8_t* DotB1, uint8_t cnv1[16], uint8_t cnv2[16]);
  void OLED_2X2_Display_Out_16x127(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1,uint8_t* DotB2, uint8_t* DotB3, uint8_t* DotB4, uint8_t* DotB5,uint8_t* DotB6, uint8_t* DotB7, uint8_t* DotB8);
  void OLED_2X2_Display_Out_16x64(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1,uint8_t* DotB2, uint8_t* DotB3, uint8_t* DotB4);
  void OLED_16x16_Display_Out(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1, uint8_t* DotB2);
  void OLED_8x16_Display_Out(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1, uint8_t* DotB2);
  void Dot_16X16_Rotation(int16_t Rotation, uint8_t* DotB1, uint8_t* DotB2, uint8_t cnv1[16], uint8_t cnv2[16]);
  void Dot_8X16_Rotation(int16_t Rotation, uint8_t* DotB1, uint8_t cnv1[16], uint8_t cnv2[16]);
  void Scroller_16x16Dot_Replace(uint8_t drection, uint8_t* next_buff1, uint8_t* next_buff2, uint8_t* scl_buff1, uint8_t* scl_buff2, uint8_t* Orign_buff1, uint8_t* Orign_buff2);
  void Scroller_8x16Dot_Replace(uint8_t drection, uint8_t* next_buff1, uint8_t* scl_buff1,uint8_t* Orign_buff1);
  void OLED16x16_White_Reversal(boolean rev, uint8_t* buf1, uint8_t* buf2, uint8_t* buf_cnv1, uint8_t* buf_cnv2);
  void OLED8x16_White_Reversal(boolean rev, uint8_t* buf1, uint8_t* buf_cnv1);
  
private:
};

#endif