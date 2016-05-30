/*
  OLED_SSD1306.cpp - for ESP-WROOM-02 ( esp8266 ) or Arduino
  Beta version 1.5
  
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
  Wire.write(0xD3); //Set Display Offset
  Wire.write(0x00);
  Wire.write(0x40); //set Display Start Line
  Wire.write(0xA0); //Segment Re-map A1が左右反転
  Wire.write(0xC0); //Set COM Output Scan Direction
  Wire.write(0xDA); //Set COM Pins Hardware Configuration
  Wire.write(B00010010); //Disable COM Left/Right remap/Alternative COM pin configuration(RESET)
  Wire.write(0x20); //Set Memory Addressing Mode
  Wire.write(B00000010); //Page Addressing Mode (RESET)
  Wire.write(0x22); //Set Page Address
  Wire.write(0x00); //start page address
  Wire.write(0x07); //stop page address
  Wire.write(0x81); // contrast control
  Wire.write(0x7F); //contrast127
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
//*************************SetUp**************************************
void OLED_SSD1306::Ini_OLED_SSD1306(uint8_t Addres, uint8_t Contrast){
  uint8_t i,j,k;
  Wire.beginTransmission(Addres);
  Wire.write(0xAE); //display off
  Wire.write(0xA4); //RAM reset
  Wire.write(0xA5); //Entire display ON
  Wire.write(0xD3); //Set Display Offset
  Wire.write(0x00);
  Wire.write(0x40); //set Display Start Line
  Wire.write(0xA0); //Segment Re-map A1が左右反転
  Wire.write(0xC0); //Set COM Output Scan Direction
  Wire.write(0xDA); //Set COM Pins Hardware Configuration
  Wire.write(B00010010); //Disable COM Left/Right remap/Alternative COM pin configuration(RESET)
  Wire.write(0x20); //Set Memory Addressing Mode
  Wire.write(B00000010); //Page Addressing Mode (RESET)
  Wire.write(0x22); //Set Page Address
  Wire.write(0x00); //start page address
  Wire.write(0x07); //stop page address
  Wire.write(0x81); // contrast control
  Wire.write(Contrast); //contrast 0-255
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
void OLED_SSD1306::Dot_2X2_convert(uint8_t* DotB1, uint8_t cnv1[16], uint8_t cnv2[16])
{
  uint8_t i,j;
  for( i = 0; i < 8; i++ ) {
    for( j = 0; j < 4; j++ ) {
      bitWrite( cnv1[i*2], j*2 , bitRead( DotB1[i], j ) );
      bitWrite( cnv1[i*2], j*2+1 , bitRead( DotB1[i], j ) );
    }
    for( j = 4; j < 8; j++ ) {
      bitWrite( cnv2[i*2], (j-4)*2 , bitRead( DotB1[i], j ) );
      bitWrite( cnv2[i*2], (j-4)*2+1 , bitRead( DotB1[i], j ) );
    }
  }
  for( i = 0; i < 8; i++ ) {
    cnv1[i*2+1]=cnv1[i*2];
    cnv2[i*2+1]=cnv2[i*2];
  }
}

//**************************************************
void OLED_SSD1306::OLED_2X2_Display_Out_16x127(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1,uint8_t* DotB2, uint8_t* DotB3, uint8_t* DotB4, uint8_t* DotB5,uint8_t* DotB6, uint8_t* DotB7, uint8_t* DotB8)
{//------------------------x(0-127),y(0-6)
  uint8_t i;
  uint8_t cnv1[2][16],cnv2[2][16],cnv3[2][16],cnv4[2][16],cnv5[2][16],cnv6[2][16],cnv7[2][16],cnv8[2][16];

  Dot_2X2_convert(DotB1, cnv1[0], cnv1[1]);
  Dot_2X2_convert(DotB2, cnv2[0], cnv2[1]);
  Dot_2X2_convert(DotB3, cnv3[0], cnv3[1]);
  Dot_2X2_convert(DotB4, cnv4[0], cnv4[1]);
  Dot_2X2_convert(DotB5, cnv5[0], cnv5[1]);
  Dot_2X2_convert(DotB6, cnv6[0], cnv6[1]);
  Dot_2X2_convert(DotB7, cnv7[0], cnv7[1]);
  Dot_2X2_convert(DotB8, cnv8[0], cnv8[1]);
      
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
      Wire.write(cnv1[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv2[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv3[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv4[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv5[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv6[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv7[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv8[0][i]);
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
      Wire.write(cnv1[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv2[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv3[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv4[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv5[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv6[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv7[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv8[1][i]);
    }
    Wire.endTransmission();

}

//**************************************************
void OLED_SSD1306::OLED_2X2_Display_Out_16x64(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1,uint8_t* DotB2, uint8_t* DotB3, uint8_t* DotB4)
{//------------------------x(0-127),y(0-6)
  uint8_t i;
  uint8_t cnv1[2][16],cnv2[2][16],cnv3[2][16],cnv4[2][16];

  Dot_2X2_convert(DotB1, cnv1[0], cnv1[1]);
  Dot_2X2_convert(DotB2, cnv2[0], cnv2[1]);
  Dot_2X2_convert(DotB3, cnv3[0], cnv3[1]);
  Dot_2X2_convert(DotB4, cnv4[0], cnv4[1]);
      
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
      Wire.write(cnv1[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv2[0][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv3[0][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv4[0][i]);
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
      Wire.write(cnv1[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv2[1][i]);
    }
    Wire.endTransmission();
    Wire.beginTransmission(Addres); // might be different for your display
    Wire.write(0x40);
    for(i=0;i<16;i++){
      Wire.write(cnv3[1][i]);
    }
    for(i=0;i<16;i++){
      Wire.write(cnv4[1][i]);
    }
    Wire.endTransmission();
}
//***************************************************************
void OLED_SSD1306::OLED_16x16_Display_Out(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1, uint8_t* DotB2)
{
  uint8_t i;

  y++;
  Wire.beginTransmission(Addres);
  Wire.write(0x00);
  Wire.write(0xB0 | y);  
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//Column Stop Address
  Wire.endTransmission();
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x40); //Set Display Start Line
    for(i=0; i<16; i++){
      Wire.write(DotB1[i]);
    }
  Wire.endTransmission();
  y--;
  Wire.beginTransmission(Addres);
  Wire.write(0x00);
  Wire.write(0xB0 | y);
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//Column Stop Address
  Wire.endTransmission();
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x40); //Set Display Start Line
    for(i=0; i<16; i++){
      Wire.write(DotB2[i]);
    }
  Wire.endTransmission();
}
//***************************************************************
void OLED_SSD1306::OLED_8x16_Display_Out(uint8_t Addres, uint8_t x, uint8_t y, uint8_t* DotB1, uint8_t* DotB2)
{
  uint8_t i;

  y++;
  Wire.beginTransmission(Addres);
  Wire.write(0x00);
  Wire.write(0xB0 | y);  
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//Column Stop Address
  Wire.endTransmission();
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x40); //Set Display Start Line
    for(i=0; i<8; i++){
      Wire.write(DotB1[i]);
    }
  Wire.endTransmission();
  y--;
  Wire.beginTransmission(Addres);
  Wire.write(0x00);
  Wire.write(0xB0 | y);
  Wire.write(0x21);//set column addres
  Wire.write(0x00 | x);//start column addres
  Wire.write(B01111111);//Column Stop Address
  Wire.endTransmission();
  Wire.beginTransmission(Addres); // might be different for your display
  Wire.write(0x40); //Set Display Start Line
    for(i=0; i<8; i++){
      Wire.write(DotB2[i]);
    }
  Wire.endTransmission();
}

//********************************************
void OLED_SSD1306::Dot_16X16_Rotation(int16_t Rotation, uint8_t* DotB1, uint8_t* DotB2, uint8_t cnv1[16], uint8_t cnv2[16])
{
  uint8_t i,j;
  for(j=0; j<8; j++){
    for(i=0; i<8; i++){
      bitWrite( cnv1[i], 7-j , bitRead( DotB2[j], i ) );
      bitWrite( cnv2[i], 7-j , bitRead( DotB2[j+8], i ) );
    }
  }
  for(j=0; j<8; j++){
    for(i=0; i<8; i++){
      bitWrite( cnv1[i+8], 7-j , bitRead( DotB1[j], i ) );
      bitWrite( cnv2[i+8], 7-j , bitRead( DotB1[j+8], i ) );
    }
  }
}
//********************************************
void OLED_SSD1306::Dot_8X16_Rotation(int16_t Rotation, uint8_t* DotB1, uint8_t cnv1[16], uint8_t cnv2[16])
{
  uint8_t i,j;
  
  switch(Rotation){
    case 90:
      for(j=0; j<8; j++){
        for(i=0; i<8; i++){
          bitWrite( cnv1[i], 7-j , bitRead( DotB1[j], i ) );
          bitWrite( cnv2[i], 7-j , bitRead( DotB1[j+8], i ) );
        }
      }
      break;
    case -90:
      for(j=0; j<8; j++){
        for(i=0; i<8; i++){
          bitWrite( cnv2[7-i], j , bitRead( DotB1[j], i ) );
          bitWrite( cnv1[7-i], j , bitRead( DotB1[j+8], i ) );
        }
      }
      break;
      
  }
}
//*************************Dot Scroll Replace**************************************
void OLED_SSD1306::Scroller_16x16Dot_Replace(uint8_t drection, uint8_t* next_buff1, uint8_t* next_buff2, uint8_t* scl_buff1, uint8_t* scl_buff2, uint8_t* Orign_buff1, uint8_t* Orign_buff2)
{
  uint8_t i;

  for(i=0 ; i<16 ; i++){
    bitWrite( next_buff1[i],7, bitRead( scl_buff1[i],7));
    scl_buff1[i] = scl_buff1[i]<<1;
    bitWrite( scl_buff1[i],0, bitRead( scl_buff2[i],7));
    scl_buff2[i] = scl_buff2[i]<<1;
    bitWrite( scl_buff2[i],0, bitRead( Orign_buff1[i],7));
    Orign_buff1[i] = Orign_buff1[i]<<1;
    bitWrite( Orign_buff1[i],0, bitRead( Orign_buff2[i],7));
    Orign_buff2[i] = Orign_buff2[i]<<1;
  }
}
//*************************Dot Scroll Replace**************************************
void OLED_SSD1306::Scroller_8x16Dot_Replace(uint8_t drection, uint8_t* next_buff1, uint8_t* scl_buff1,uint8_t* Orign_buff1)
{
  uint8_t i;

  for(i=0 ; i<16 ; i++){
    bitWrite( next_buff1[i],7, bitRead( scl_buff1[i],7));
    scl_buff1[i] = scl_buff1[i]<<1;
    bitWrite( scl_buff1[i],0, bitRead( Orign_buff1[i],7));
    Orign_buff1[i] = Orign_buff1[i]<<1;
  }
}
//*************************Black_White_Reversal**************************************
void OLED_SSD1306::OLED16x16_White_Reversal(boolean rev, uint8_t* buf1, uint8_t* buf2, uint8_t* buf_cnv1, uint8_t* buf_cnv2)
{
  if(rev == true){
    for(int i = 0; i < 16; i++){
       buf_cnv1[i] = ~buf1[i];
       buf_cnv2[i] = ~buf2[i];
    }
  }
}
//*************************Black_White_Reversal**************************************
void OLED_SSD1306::OLED8x16_White_Reversal(boolean rev, uint8_t* buf1, uint8_t* buf_cnv1)
{
  if(rev == true){
    for(int i = 0; i < 16; i++){
       buf_cnv1[i] = ~buf1[i];
    }
  }
}