# ESP32_SPIFFS_ShinonomeFNT
This is the Arduino core for the ESP32 library for reading Shinonome 16x16 Japanese font.  
  
Beta ver1.0  
  
これはShift_JISコードからフリーの東雲フォント(16x16)を ESP-WROOM-32( ESP32 )で読み込むためのライブラリです。  
SPIFFS File System からの読み込み専用です。  
UTF8toSjisライブラリをインクルードしているので、１行の関数のみでUTF-8文字列から16x16ドットの日本語漢字に変換できます。  
別途、ESP32_SPIFFS_UTF8toSJIS ライブラリが必要です。  
  
必要なフォントファイル、およびテーブルファイルは以下のとおりです。  
  
Utf8Sjis.tbl (UTF-8 Shift_JIS変換テーブル)  
shnmk16.bdf (全角東雲フォント)  
shnm8x16.bdf (半角東雲フォント, ファイル名の'r'をカットしたもの)  
  
【更新履歴】  
(1.0)  
New released  
  
(1.0)  
ESP32 SPIFFS用リリース  
  
Licence:  
  
  MITライセンス　　
  Copyright (c) 2017 Mgo-tec  
  
  東雲フォントは/efont/さんが保守開発を行い、ライセンスはPublic Domainです。  
  
詳しくはブログ参照：  
https://www.mgo-tec.com  