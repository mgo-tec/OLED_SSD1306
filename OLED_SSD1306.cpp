/*
  OLED_SSD1306.cpp - for ESP-WROOM-02 ( esp8266 ) or Arduino
  Beta version 1.0
  
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

#include "Arduino.h"
#include "OLED_SSD1306.h"

OLED_SSD1306::OLED_SSD1306(){}

//*************************SetUp**************************************
void OLED_SSD1306::setup_OLED_SSD1306(uint8_t Addres){
  uint8_t i,j,k;
  Wire.beginTransmission(Addres);
  Wire.write(0xAE); //display off
  Wire.write(0xA4); //RAM reset
  Wire.write(0xA5); //Entire display ON
  Wire.write(0x00); //set lower column address
  Wire.write(0x10); //set higher column address
  Wire.write(0x00); //set display start line
  Wire.write(0x2E); //Deactivate scroll
  Wire.write(0x21); //set Column Address
  Wire.write(0x00 | 0); //Column Start Address
  Wire.write(B01111111); //Column Stop Address
  Wire.write(0x22); //Set Page Address
  Wire.write(0x00); //start page address
  Wire.write(0x07); //stop page address
  Wire.write(0xB0 | 0); //set page start address
  Wire.write(0x81); //contrast control
  Wire.write(0x7f); //contrast 127
  Wire.write(0xA6); //normal / reverse A7=reverse
  Wire.write(0xC0); //Com scan direction
  Wire.write(0x8d); //set charge pump enable
  Wire.write(0x14); //charge pump ON
  Wire.write(0xAF); //display ON
  Wire.endTransmission();
  //Clear Display
  for(i=0; i<8; i++){
    Wire.beginTransmission(Addres);
    Wire.write(0x00); //set display start line
    Wire.write(0xB0 | i); //set page start address
    Wire.write(0x21);//set column addres
    Wire.write(0x00 | 0);//start column addres
    Wire.write(B01111111);//stop column addres
    Wire.endTransmission();
    //horizontal line
    for(j=0; j<16; j++){//column = 8bit X 16
      Wire.beginTransmission(Addres);
      Wire.write(0x40); //Set Display Start Line
      for(k=0; k<8; k++){
        Wire.write(0x00);
      }
      Wire.endTransmission();
    }
  }
}
//***************************************************************
void OLED_SSD1306::OLED_1x1_Display_Out_8x16(uint8_t Addres, uint8_t* Dot1, uint8_t* Dot2, uint8_t* Dot3, uint8_t* Dot4)
{
  uint8_t i;

  Wire.beginTransmission(Addres);
  Wire.write(0x00); //set display start line
  Wire.write(0xB0 | 7); //set page start address
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | 90);//start column addres
  Wire.write(B01111111);//Column Stop Address
  Wire.endTransmission();
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x40); //Set Display Start Line

  for(i=0; i<8; i++){
    Wire.write(Dot1[i]);
  }
  for(i=0; i<8; i++){
    Wire.write(Dot2[i]);
  }
  for(i=0; i<8; i++){
    Wire.write(Dot3[i]);
  }
  for(i=0; i<8; i++){
    Wire.write(Dot4[i]);
  }
  Wire.endTransmission();
}

//********************************************
void OLED_SSD1306::Dot_2X2_convert(uint8_t* DotB1, uint8_t __cnv1[16], uint8_t __cnv2[16])
{
  uint8_t i,j;
  for( i = 0; i < 8; i++ ) {
    for( j = 0; j < 4; j++ ) {
      bitWrite( __cnv1[i*2], j*2 , bitRead( DotB1[i], j ) );
      bitWrite( __cnv1[i*2], j*2+1 , bitRead( DotB1[i], j ) );
    }
    for( j = 4; j < 8; j++ ) {
      bitWrite( __cnv2[i*2], (j-4)*2 , bitRead( DotB1[i], j ) );
      bitWrite( __cnv2[i*2], (j-4)*2+1 , bitRead( DotB1[i], j ) );
    }
  }
  for( i = 0; i < 8; i++ ) {
    __cnv1[i*2+1]=__cnv1[i*2];
    __cnv2[i*2+1]=__cnv2[i*2];
  }
}

//**************************************************
void OLED_SSD1306::OLED_2X2_Display_Out_16x127(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1,uint8_t* DotB2, uint8_t* DotB3, uint8_t* DotB4, uint8_t* DotB5,uint8_t* DotB6, uint8_t* DotB7, uint8_t* DotB8)
{//------------------------x(0-127),y(0-6)
  uint8_t i;
  uint8_t __cnv1[2][16],__cnv2[2][16],__cnv3[2][16],__cnv4[2][16],__cnv5[2][16],__cnv6[2][16],__cnv7[2][16],__cnv8[2][16];

  Dot_2X2_convert(DotB1, __cnv1[0], __cnv1[1]);
  Dot_2X2_convert(DotB2, __cnv2[0], __cnv2[1]);
  Dot_2X2_convert(DotB3, __cnv3[0], __cnv3[1]);
  Dot_2X2_convert(DotB4, __cnv4[0], __cnv4[1]);
  Dot_2X2_convert(DotB5, __cnv5[0], __cnv5[1]);
  Dot_2X2_convert(DotB6, __cnv6[0], __cnv6[1]);
  Dot_2X2_convert(DotB7, __cnv7[0], __cnv7[1]);
  Dot_2X2_convert(DotB8, __cnv8[0], __cnv8[1]);
      
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x00);
  Wire.write(0xB0 | y);
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//stop column addres
  Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv1[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv2[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv3[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv4[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv5[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv6[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv7[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv8[0][i]);
    }
    Wire.endTransmission();
  y++;
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x00);
  Wire.write(0xB0 | y);
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//stop column addres
  Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv1[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv2[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv3[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv4[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv5[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv6[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv7[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv8[1][i]);
    }
    Wire.endTransmission();

}

//**************************************************
void OLED_SSD1306::OLED_2X2_Display_Out_16x64(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1,uint8_t* DotB2, uint8_t* DotB3, uint8_t* DotB4)
{//------------------------x(0-127),y(0-6)
  uint8_t i;
  uint8_t __cnv1[2][16],__cnv2[2][16],__cnv3[2][16],__cnv4[2][16];

  Dot_2X2_convert(DotB1, __cnv1[0], __cnv1[1]);
  Dot_2X2_convert(DotB2, __cnv2[0], __cnv2[1]);
  Dot_2X2_convert(DotB3, __cnv3[0], __cnv3[1]);
  Dot_2X2_convert(DotB4, __cnv4[0], __cnv4[1]);
      
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x00);
  Wire.write(0xB0 | y);
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//stop column addres
  Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv1[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv2[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv3[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv4[0][i]);
    }
    Wire.endTransmission();
  y++;
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x00);
  Wire.write(0xB0 | y);
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//stop column addres
  Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv1[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv2[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(__cnv3[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(__cnv4[1][i]);
    }
    Wire.endTransmission();
}