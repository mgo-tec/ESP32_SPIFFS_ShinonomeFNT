/*
  ESP32_SPIFFS_ShinonomeFNT.cpp - Arduino core for the ESP32 Library.
  Beta version 1.32
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

#include "ESP32_SPIFFS_ShinonomeFNT.h"

ESP32_SPIFFS_ShinonomeFNT::ESP32_SPIFFS_ShinonomeFNT(){}

//*********東雲フォントライブラリ初期化3ファイル*************************************************************
void ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Shinonome_Init3F(const char* UTF8SJIS_file, const char* Shino_Half_Font_file, const char* Shino_Zen_Font_file){
  SPIFFS.begin();
  //SPIFFS.begin(true);

  Serial.println("card initialized.");
  _UtoS = SPIFFS.open(UTF8SJIS_file, FILE_READ);
  if (!_UtoS) {
    Serial.print(UTF8SJIS_file);
    Serial.println(" File not found");
    return;
  }else{
    Serial.print(UTF8SJIS_file);
    Serial.println(" File read OK!");
  }
  _SinoH = SPIFFS.open(Shino_Half_Font_file, FILE_READ);
  if (!_SinoH) {
    Serial.print(Shino_Half_Font_file);
    Serial.print(" File not found");
    return;
  }else{
    Serial.print(Shino_Half_Font_file);
    Serial.println(" File read OK!");
  }
  _SinoZ = SPIFFS.open(Shino_Zen_Font_file, FILE_READ);
  if (!_SinoZ) {
    Serial.print(Shino_Zen_Font_file);
    Serial.print(" File not found");
    return;
  }else{
    Serial.print(Shino_Zen_Font_file);
    Serial.println(" File read OK!");
  }
}
//********東雲フォントライブラリ初期化　２ファイル*************************************************************
void ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Shinonome_Init2F(const char* Shino_Half_Font_file, const char* Shino_Zen_Font_file){
  SPIFFS.begin();
  //SPIFFS.begin(true);

  _SinoH = SPIFFS.open(Shino_Half_Font_file, FILE_READ);
  if (!_SinoH) {
    Serial.print(Shino_Half_Font_file);
    Serial.print(" File not found");
    return;
  }else{
    Serial.print(Shino_Half_Font_file);
    Serial.println(" File read OK!");
  }
  _SinoZ = SPIFFS.open(Shino_Zen_Font_file, FILE_READ);
  if (!_SinoZ) {
    Serial.print(Shino_Zen_Font_file);
    Serial.print(" File not found");
    return;
  }else{
    Serial.print(Shino_Zen_Font_file);
    Serial.println(" File read OK!");
  }
}
//**************３ファイル　フォントファイルクローズ********************
void ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Shinonome_Close3F(){
  delay(1);
  _UtoS.close();
  delay(1);
  _SinoH.close();
  delay(1);
  _SinoZ.close();
  delay(1);
  Serial.println("--------------3 files closed");
  SPIFFS.end();
  Serial.println("--------------SPIFFS.end");
}
//*************２ファイル　フォントファイルクローズ********************
void ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Shinonome_Close2F(){
  delay(1);
  _SinoH.close();
  delay(1);
  _SinoZ.close();
  delay(1);
  Serial.println("--------------2 files closed");
  SPIFFS.end();
  Serial.println("--------------SPIFFS.end");
}
//*******************東雲フォント全変換*************************
uint16_t ESP32_SPIFFS_ShinonomeFNT::StrDirect_ShinoFNT_readALL(String str, uint8_t font_buf[][16]){
  uint8_t sj_txt[str.length()];
  uint16_t sj_length;

  _u8ts.UTF8_to_SJIS_str_cnv(_UtoS, str, sj_txt, &sj_length);
  ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead_ALL(_SinoZ, _SinoH, 0, 0, sj_txt, sj_length, font_buf);
  return sj_length;
}
//*******************東雲フォント全変換、フォント回転*************************
uint16_t ESP32_SPIFFS_ShinonomeFNT::StrDirect_ShinoFNT_readALL(int16_t Rotation, String str, uint8_t font_buf[][16]){
  //※90度回転する場合、半角１文字は半角スペースを入れて２バイト文字とする。
  int i = 0, ii = 0;

  uint8_t sj_txt[str.length()];
  uint16_t sj_length;

  _u8ts.UTF8_to_SJIS_str_cnv(_UtoS, str, sj_txt, &sj_length);
  while(i<sj_length){
    uint8_t fnt[2][16] = {};
    i = i + ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead(_SinoZ, _SinoH, sj_txt[i], sj_txt[i+1], fnt[0], fnt[1]);
    ESP32_SPIFFS_ShinonomeFNT::Fnt16x16_Rotation(Rotation, fnt, font_buf+ii);
    ii = ii + 2;
  }
  return sj_length;
}
//*******************東雲フォント全変換 UTF8toShis変換ファイルハンドル外部読み込み*************************
uint16_t ESP32_SPIFFS_ShinonomeFNT::StrDirect_ShinoFNT_readALL2F(File UtoS, String str, uint8_t font_buf[][16]){
  uint8_t sj_txt[str.length()];
  uint16_t sj_length;

  _u8ts.UTF8_to_SJIS_str_cnv(UtoS, str, sj_txt, &sj_length);
  ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead_ALL(_SinoZ, _SinoH, 0, 0, sj_txt, sj_length, font_buf);
  return sj_length;
}
//*******************UTF8 -> Shift_JISコード変換のみ*************************
uint16_t ESP32_SPIFFS_ShinonomeFNT::UTF8toSJIS_convert(String str, uint8_t* sj_code){
  uint16_t sj_length;

  _u8ts.UTF8_to_SJIS_str_cnv(_UtoS, str, sj_code, &sj_length);
  return sj_length;
}
//*******************東雲フォント全変換（Shift_JISコード返りあり）*************************
uint16_t ESP32_SPIFFS_ShinonomeFNT::SjisShinonomeFNTread_ALL(String str, uint8_t* sj_code, uint8_t font_buf[][16]){
  uint16_t sj_length;

  _u8ts.UTF8_to_SJIS_str_cnv(_UtoS, str, sj_code, &sj_length);
  ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead_ALL(_SinoZ, _SinoH, 0, 0, sj_code, sj_length, font_buf);
  return sj_length;
}
//*******************東雲フォント１文字変換*************************************************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead(File f1, File f2, uint8_t jisH, uint8_t jisL, uint8_t buf1[16], uint8_t buf2[16]){
  uint16_t fnt_adrs_half = 0x1346; //space
  uint32_t fnt_adrs_Zen = 0x467; //Space
  uint8_t cp;

  if(jisH < 0x20){
    jisH = 0x20; //制御コードは全てスペース
  }
  if((jisH>=0x20 && jisH<=0x7E) || (jisH>=0xA1 && jisH<=0xDF)){
    if(jisH<=0x63) fnt_adrs_half = 0x0386 + jisH*0x7E; //fnt_adrs_half = 0x1346+(jisH-0x20)*126;
    else if(jisH<=0x7E) fnt_adrs_half = 0x0323 + jisH*0x7F; //fnt_adrs_half = 0x34BF+(jisH-0x64)*127;
    else if(jisH>=0xA1) fnt_adrs_half = jisH*0x81 - 0x0EFB; //fnt_adrs_half = 0x4226+(jisH-0xA1)*129;

    ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Flash_ShinonomeFNTread_Harf_FHN(f2, fnt_adrs_half, buf1);
    cp = 1;

    if((jisL>=0x20 && jisL<=0x7E) || (jisL>=0xA1 && jisL<=0xDF)){
      if(jisL<=0x63) fnt_adrs_half = 0x0386 + jisL*0x7E; //fnt_adrs_half = 0x1346+(jisL-0x20)*126;
      else if(jisL<=0x7E) fnt_adrs_half = 0x0323 + jisL*0x7F; //fnt_adrs_half = 0x34BF+(jisL-0x64)*127;
      else if(jisL>=0xA1) fnt_adrs_half = jisL*0x81 - 0x0EFB; //fnt_adrs_half = 0x4226+(jisL-0xA1)*129;

      ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Flash_ShinonomeFNTread_Harf_FHN(f2, fnt_adrs_half, buf2);
      cp = 2;
    }else{
      cp = 1;
    }
  }else{
    ESP32_SPIFFS_ShinonomeFNT::SjisToShinonomeFNTadrs(jisH, jisL, &fnt_adrs_Zen);
    ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Flash_ShinonomeFNTread_FHN(f1, fnt_adrs_Zen, buf1, buf2);
    cp = 2;
  }
  return cp;
}
//*************S-jisまとめて変換*****************************************
void ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead_ALL(File f1, File f2, uint8_t Direction, int16_t Rotation, uint8_t* Sjis, uint16_t sj_length, uint8_t font_buf[][16]){
  uint16_t i = 0;

  while(i < sj_length){
    if(i == sj_length-1){ //文字の最後の１つ前が奇数バイト数で、最後の文字が半角の場合の対処
      i = i + ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead(f1, f2, Sjis[i], Sjis[i], font_buf[i], font_buf[i]);
    }else{
      i = i + ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead(f1, f2, Sjis[i], Sjis[i+1], font_buf[i], font_buf[i+1]);
    }
    yield();
  }
}
//*******************Shift_JISコードから東雲フォントアドレス計算********************************************
void ESP32_SPIFFS_ShinonomeFNT::SjisToShinonomeFNTadrs(uint8_t jisH, uint8_t jisL, uint32_t* fnt_adrs) {    // S-JISコードから東雲フォントファイル上のバイト位置をポインタで返す。
  uint16_t jisCode;
  int32_t adj = 0;
  
  if( jisH != '\0'){  //'\0'ならば読み込まない。
    jisCode = ((uint16_t)jisH << 8 )|jisL;
    if(jisCode>=0x8140 && jisCode <=0x83D6){
      if     (jisCode<=0x817E) adj = 1127;  // スペース～×
      else if(jisCode<=0x81AC) adj = 963;  // ÷～〓
      else if(jisCode<=0x81BF) adj = -841;  // ∈～∩
      else if(jisCode<=0x81CE) adj = -2153;  // ∧～∃
      else if(jisCode<=0x81E8) adj = -3957;  // ∠～∬
      else if(jisCode<=0x81F7) adj = -5105;  // Å～¶
      else if(jisCode==0x81FC) adj = -5761;  // ◯
      else if(jisCode<=0x8258) adj = -19209;  // 一般記号
      else if(jisCode<=0x8279) adj = -20357;  // 数字、英語大文字
      else if(jisCode<=0x829A) adj = -21505;  // 英小文字、ひらがな
      else if(jisCode<=0x82F1) adj = -22161;  // 英小文字、ひらがな
      else if(jisCode<=0x837e) adj = -34953;  // カタカナ
      else if(jisCode<=0x8396) adj = -35117;  // カタカナ
      else if(jisCode<=0x83B6) adj = -36429;  // Α～Ω
      else if(jisCode>=0x83BF) adj = -37741;  // α～ω
      *fnt_adrs = jisCode * 0xA4 - 0x0052CD00 + adj; //*fnt_adrs = (jisCode-0x8140)*164 + adj;
    }else if(jisCode>=0x8440 && jisCode <=0x84BE){
      if(jisCode<=0x8460) adj = 70992;  // А～Я
      else if(jisCode<=0x847E) adj = 68517;  // а～н
      else if(jisCode<=0x8491) adj = 68352;  // о～я
      else if(jisCode>=0x849F) adj = 66207;  // 罫線
      *fnt_adrs = jisCode * 0xA5 - 0x00553D40 + adj; //*fnt_adrs = (jisCode-0x8440)*165 + adj;
    }else if(jisCode>=0x8740 && jisCode <=0x879E){ //JIS13区は無いので"？"マークにする
      *fnt_adrs = 0x987; //"？"文字
    }else if(jisCode>=0x889f && jisCode<=0x88FC){ //JIS第１水準 亜～蔭
      *fnt_adrs = jisCode * 0xA5 - 0x0056BA01; //*fnt_adrs = (jisCode-0x889F)*165+87162;
    }else if(jisCode>=0x8940 && jisCode<=0x9872){ //JIS第１水準 院～腕
      if(jisL <= 0x7E){
        //*fnt_adrs = (jisCode-0x889F)*165+87162 -(jisH-0x88)*11055-(jisH-0x88-1)*165;
        *fnt_adrs = jisCode*0xA5 - jisH*0x2BD4 - 0x3F70BC;
      }else if(jisL >= 0x80 ){
        //*fnt_adrs = (jisCode-0x889F)*165+87162-(jisH-0x88)*11055-(jisH-0x88)*165;
        *fnt_adrs = jisCode*0xA5 - jisH*0x2BD4 - 0x3F7161;
      }
    }else if(jisCode>=0x989F && jisCode<=0x9FFC){ //JIS第２水準 弌～滌
      if(jisL <= 0x7E){
        //*fnt_adrs = (jisCode-0x889F)*165+80067-(jisH-0x88)*11055-(jisH-0x88-1)*165;
        *fnt_adrs = jisCode*0xA5 - jisH*0x2BD4 - 0x3F8C73;
      }else if(jisL >= 0x80 ){
        //*fnt_adrs = (jisCode-0x889F)*165+80067-(jisH-0x88)*11055-(jisH-0x88)*165;
        *fnt_adrs = jisCode*0xA5 - jisH*0x2BD4 - 0x3F8D18;
      }
    }else if(jisCode>=0xE040 && jisCode <=0xEAA4){ //JIS第２水準 漾～熙
      if(jisL <= 0x7E){
        //*fnt_adrs = (jisCode-0x889F)*165-2634348-(jisH-0xC9)*11055-(jisH-0xC9)*165;
        *fnt_adrs = jisCode*0xA5 - jisH*0x2BD4 - 0x5DD773;
      }else if(jisL >= 0x80 ){
        //*fnt_adrs = (jisCode-0x889F)*165-2634348-(jisH-0xC9)*11055-(jisH-0xC9+1)*165;
        *fnt_adrs = jisCode*0xA5 - jisH*(0x2B2F+0xA5) - 0x5DD818;
      }
    }else{
      *fnt_adrs = 0x467;  // 対応文字コードがなければ 全角スペースを返す
    }
  }else {
    *fnt_adrs = 0x467;  // 対応文字コードがなければ 全角スペースを返す
  }
}
//*****************全角フォントファイル読み込み、ファイルハンドル渡し**************************************
void ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Flash_ShinonomeFNTread_FHN(File ff, uint32_t addrs, uint8_t buf1[16], uint8_t buf2[16]){
//  Dir dir = SPIFFS.openDir("/");//これは読み取り速度が遅くなるかもしれないのでコメントアウトしている
  uint8_t i;
  uint8_t j=0;
  uint8_t c1, c2, c3, c4;
  uint8_t c[85];
  if(ff){
    ff.seek(addrs);
    ff.read(c,80); //4byte+"." -->5byte*16=80byte
    for (i=0; i<16; i++){
      if(c[j]>=0x61) c1 = c[j]-0x57; //c1 = (c[j]-0x61)+10;
      else c1 = c[j]-0x30;
      j++;
      if(c[j]>=0x61) c2 = c[j]-0x57; //c2 = (c[j+1]-0x61)+10;
      else c2 = c[j]-0x30;
      j++;
      if(c[j]>=0x61) c3 = c[j]-0x57; //c3 = (c[j+2]-0x61)+10;
      else c3 = c[j]-0x30;
      j++;
      if(c[j]>=0x61) c4 = c[j]-0x57; //c4 = (c[j+3]-0x61)+10;
      else c4 = c[j]-0x30;

      buf1[i] = (c1<<4)|c2;
      buf2[i] = (c3<<4)|c4;
      j=j+2;
    }
  }else{
    Serial.println(F(" shinonome file has not been uploaded to the flash in SPIFFS file system"));
    delay(30000);
  }
}
//*****************半角フォントファイル読み込み、ファイルハンドル渡し**************************************
void ESP32_SPIFFS_ShinonomeFNT::SPIFFS_Flash_ShinonomeFNTread_Harf_FHN(File ff, uint32_t addrs, uint8_t buf[16]){
  uint8_t i;
  uint8_t j=0;
  uint8_t c1, c2;
  uint8_t c[50];

  if(ff){
    ff.seek(addrs);
    ff.read(c,48); //2byte+"." -->3byte*16=48byte
    for (i=0; i<16; i++){
      if(c[j]>=0x61) c1 = (c[j]-0x61)+10;
      else c1 = c[j]-0x30;
      if(c[j+1]>=0x61) c2 = (c[j+1]-0x61)+10;
      else c2 = c[j+1]-0x30;

      buf[i] = (c1<<4)|c2;
      j=j+3;
    }
  }else{
    Serial.println(F(" Shinonome file has not been uploaded to the flash in SPIFFS file system"));
    delay(30000);
  }
}
//********************************************************************************
void ESP32_SPIFFS_ShinonomeFNT::Scroll_Sjis_1_line(uint8_t disp_char, uint8_t num, uint8_t sj_txt[], uint16_t sj_length, uint8_t disp_buf[][16]){
  if(_fnt_read_ok[num] == true) {
    _Zen_or_Han[num] = ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(num, sj_txt, sj_length, _dummy_buf[num]);
  }
  _fnt_read_ok[num] = ESP32_SPIFFS_ShinonomeFNT::Scroller_Font8x16_DotReplace(16, num, _Zen_or_Han[num], _dummy_buf[num], disp_buf);
}

////////////////////////////////////////////////////
//*******************Shift_JISコード全角半角判別*************************************************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_Zen_or_Han(uint8_t jisH, uint8_t jisL){
  uint8_t cp;

  if(jisH < 0x20){
    jisH = 0x20; //制御コードは全てスペース
  }
  if((jisH>=0x20 && jisH<=0x7E) || (jisH>=0xA1 && jisH<=0xDF)){
    cp = 1;
    if((jisL>=0x20 && jisL<=0x7E) || (jisL>=0xA1 && jisL<=0xDF)){
     cp = 2;
    }else{
      cp = 1;
    }
  }else{
    cp = 2;
  }
  return cp;
}
//***************Shift_JIS 全角半角判別自動インクリメント************************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_Zen_or_Han_inc(uint8_t sj[], uint16_t length, uint16_t *sj_cnt){
  uint8_t cp;
  if(length == *sj_cnt){
    cp = 1;
  }else{
    cp = Sjis_Zen_or_Han(sj[*sj_cnt], sj[*sj_cnt+1]);
  }
  *sj_cnt = *sj_cnt + cp;
  if(*sj_cnt >= length) *sj_cnt = 0;
  return cp;
}
//***************フォント１文字変換自動インクリメント（複数行）文字カウント数返りあり*******************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(uint16_t *sjcnt, uint8_t num, uint8_t sj[], uint16_t length, uint8_t buf[2][16]){
  return ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(sj, length, sjcnt, buf);
}
//***************フォント１文字変換自動インクリメント（複数行）*******************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(uint8_t num, uint8_t sj[], uint16_t length, uint8_t buf[2][16]){
  return ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(sj, length, &_sj_cnt1[num], buf);
}
//***************フォント１文字変換自動インクリメント************************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(uint8_t sj[], uint16_t length, uint16_t *sj_cnt, uint8_t buf[2][16]){
  uint8_t cp;
  if(*sj_cnt+1 > length){
    ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead(_SinoZ, _SinoH, sj[*sj_cnt], sj[*sj_cnt], buf[0], buf[1]);
    cp = 1;
  }else{
    cp = ESP32_SPIFFS_ShinonomeFNT::SjisToShinonome16FontRead(_SinoZ, _SinoH, sj[*sj_cnt], sj[*sj_cnt+1], buf[0], buf[1]);
  }
  
  *sj_cnt = *sj_cnt + cp;
  if(*sj_cnt >= length) *sj_cnt = 0;

  return cp;
}
//*************フォントを９０度回転して取得する(SSD1306用) 文字カウント返し有り******************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead_Rot(uint16_t *sjcnt, int16_t Rotation, uint8_t Direction, uint8_t num, uint8_t sj[], uint16_t length, uint8_t bufff[2][16]){
  uint8_t fnt_buf[2][16] = {};
  uint8_t cp = ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead(sj, length, sjcnt, fnt_buf);

  ESP32_SPIFFS_ShinonomeFNT::Fnt16x16_Rotation(Rotation, fnt_buf, bufff);

  return cp;
}
//*************フォントを９０度回転して取得する(SSD1306用)*********************************
uint8_t ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead_Rot(int16_t Rotation, uint8_t Direction, uint8_t num, uint8_t sj[], uint16_t length, uint8_t bufff[2][16]){
  return ESP32_SPIFFS_ShinonomeFNT::Sjis_inc_FntRead_Rot(&_sj_cnt1[num], Rotation, Direction, num, sj, length, bufff);
}
//********************************************************************************
void ESP32_SPIFFS_ShinonomeFNT::Fnt16x16_Rotation(int16_t Rotation, uint8_t fnt_buf[2][16], uint8_t bufff[2][16]){
  int i, j, j_rev=0;
  uint8_t dummy = 0;

  switch(Rotation){
    case 90:
      break;
    case -90:
      for(j=0; j<8; j++){
        j_rev = 7 - j;
        bufff[1][j] = 0;
        for(i=0; i<8; i++){ 
          dummy = ( fnt_buf[0][i] >> j_rev ) & 0x01;
          if(dummy){
            bufff[1][j] = bufff[1][j] | (dummy << i);
          }
        }
      }
      for(j=0; j<8; j++){
        j_rev = 7 - j;
        bufff[0][j] = 0;
        for(i=0; i<8; i++){
          dummy = ( fnt_buf[0][i+8] >> j_rev ) & 0x01;
          if(dummy){
            bufff[0][j] = bufff[0][j] | (dummy << i);
          }
        }
      }
      for(j=8; j<16; j++){
        j_rev = 15 - j;
        bufff[1][j] = 0;
        for(i=0; i<8; i++){ 
          dummy = ( fnt_buf[1][i] >> j_rev ) & 0x01;
          if(dummy){
            bufff[1][j] = bufff[1][j] | (dummy << i);
          }
        }
      }
      for(j=8; j<16; j++){
        j_rev = 15 - j;
        bufff[0][j] = 0;
        for(i=0; i<8; i++){
          dummy = ( fnt_buf[1][i+8] >> j_rev ) & 0x01;
          if(dummy){
            bufff[0][j] = bufff[0][j] | (dummy << i);
          }
        }
      }
      break;
    default:
      break;
  }
}
//*********電光掲示板風スクロール関数 8x16ドット 16文字用********************
boolean ESP32_SPIFFS_ShinonomeFNT::Scroller_Font8x16_DotReplace(uint8_t disp_char, uint8_t num, uint8_t Zen_or_Han, uint8_t font_buf1[][16], uint8_t scl_buff1[][16]){
  int8_t i, j;
  boolean fnt_read_ok = false;
  uint8_t max_b = disp_char - 1;

  for(i=0; i<max_b; i++){
    for(j=0; j<16; j++){
      scl_buff1[i][j] = scl_buff1[i][j]<<1;
      scl_buff1[i][j] = ( scl_buff1[i][j] | (scl_buff1[i+1][j]>>7));
    }
  }

  uint8_t dummy = 0;

  for(i=0; i<16; i++){
    dummy = font_buf1[ _Zen_or_Han_cnt[num] ][i] << ( _scl_cnt1[num] );
    scl_buff1[max_b][i] = scl_buff1[max_b][i]<<1;
    scl_buff1[max_b][i] =  scl_buff1[max_b][i] | (dummy>>7);
  }
  _scl_cnt1[num]++;

  if(_scl_cnt1[num] == 8){
    _scl_cnt1[num] = 0;
    _Zen_or_Han_cnt[num]++;
    if(_Zen_or_Han_cnt[num] == Zen_or_Han){
      _Zen_or_Han_cnt[num] = 0;
      fnt_read_ok = true;
    }
  }

  return fnt_read_ok;
}
