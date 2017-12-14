/*
  ESP32_SPIFFS_ShinonomeFNT.h - Arduino core for the ESP32 Library.
  Beta version 1.0
  This is micro SPIFFS card library for reading Shinonome font.  
  
The MIT License (MIT)

Copyright (c) 2017 Mgo-tec
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

Licence of Shinonome Font is Public Domain.
Maintenance development of Font is /efont/.
*/

#ifndef _ESP32_SPIFFS_SHINONOMEFNT_H_INCLUDED
#define _ESP32_SPIFFS_SHINONOMEFNT_H_INCLUDED

#include <Arduino.h>
#include "ESP32_SPIFFS_UTF8toSJIS.h"
#include "SPIFFS.h"

class ESP32_SPIFFS_ShinonomeFNT
{
public:
  ESP32_SPIFFS_ShinonomeFNT();

  void SPIFFS_Shinonome_Init3F(const char* UTF8SJIS_file, const char* Shino_Half_Font_file, const char* Shino_Zen_Font_file);
  void SPIFFS_Shinonome_Init2F(const char* Shino_Half_Font_file, const char* Shino_Zen_Font_file);
  void SPIFFS_Shinonome_Close3F();
  void SPIFFS_Shinonome_Close2F();
  uint16_t StrDirect_ShinoFNT_readALL(String str, uint8_t font_buf[][16]);
  uint16_t StrDirect_ShinoFNT_readALL2F(File UtoS, String str, uint8_t font_buf[][16]);
  uint16_t SjisShinonomeFNTread_ALL(String str, uint8_t* sj_code, uint8_t font_buf[][16]);
  uint8_t SjisToShinonome16FontRead(File f1, File f2, uint8_t Direction, int16_t Angle, uint8_t jisH, uint8_t jisL, uint8_t buf1[16], uint8_t buf2[16]);
  uint8_t SjisToShinonome16FontRead2(uint8_t jisH, uint8_t jisL, uint8_t buf1[16], uint8_t buf2[16]);
  void SjisToShinonome16FontRead_ALL(File f1, File f2, uint8_t Direction, int16_t Angle, uint8_t* Sjis, uint16_t sj_length, uint8_t font_buf[][16]);
  void Scroller_RtoL(uint8_t disp_char_max, uint8_t scl_buff[][16], uint8_t *sjis_txt, uint16_t Length, uint8_t* scl_cnt1, uint16_t* sj_cnt1);
  void SjisToShinonomeFNTadrs(uint8_t jisH, uint8_t jisL, uint32_t* fnt_adrs);
  void SPIFFS_Flash_ShinonomeFNTread_FHN(File ff, uint32_t addrs, uint8_t buf1[16], uint8_t buf2[16]);
  void SPIFFS_Flash_ShinonomeFNTread_Harf_FHN(File ff, uint32_t addrs, uint8_t buf[16]);
  uint8_t Sjis_inc_FntRead(uint8_t *sj, uint16_t length, uint16_t *sj_cnt, uint8_t buf[2][16]);
  uint8_t Sjis_inc_FntRead2(uint8_t *sj, uint16_t length, uint16_t *sj_cnt, uint8_t buf[2][16]);
  
private:
  uint32_t _SPIFFS_freq;
  File _SinoZ;
  File _SinoH;
  File _UtoS;
  ESP32_SPIFFS_UTF8toSJIS _u8ts;
  
  const char *_gF1;
  const char *_gF2;

  uint8_t _Sino_font_buf[16][16]; //東雲（しののめ）フォントバッファ
  uint8_t _SnnmDotOut[16][16];
  uint8_t _Next_buf[16][16];
  uint8_t _font_buf[2][16];
  uint8_t _Orign_buf[16];
  uint8_t _ZENorHalf = 0;
};

#endif