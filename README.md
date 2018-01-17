# ESP32_SPIFFS_ShinonomeFNT
This is the Arduino core for the ESP32 library for reading Shinonome 16x16 Japanese font.  
  
Beta ver1.32  
  
これはShift_JISコードからフリーの東雲フォント(16x16)を ESP-WROOM-32( ESP32 )で読み込むためのライブラリです。  
SPIFFS File System からの読み込み専用です。  
UTF8toSjisライブラリをインクルードしているので、１行の関数のみでUTF-8文字列から16x16ドットの日本語漢字に変換できます。  
別途、ESP32_SPIFFS_UTF8toSJIS ライブラリが必要です。  
  
必要なフォントファイル、およびテーブルファイルは以下のとおりです。  
  
Utf8Sjis.tbl (UTF-8 Shift_JIS変換テーブル)  
shnmk16.bdf (全角東雲フォント)  
shnm8x16.bdf (半角東雲フォント, ファイル名の'r'をカットしたもの)  
  
  
【更新履歴】  
(1.32)  
軽微な修正をしました。  
  
(1.3)  
フォントアドレスの計算式を見直し、修正しました。  
Shift_JISコードから、全角と半角を判断するだけの関数を追加しました。  
そして、JISコードカウントを自動インクリメントする関数を追加しました。  
- Sjis_Zen_or_Han  
- Sjis_Zen_or_Han_inc  
  
(1.2)  
文字列を６列まで処理できるようにしました。  
その他、軽微な修正  
  
(1.1)  
東雲フォントをスクロールさせ、読み込みを自動インクリメントするようにしました。  
  
(1.0)  
ESP32 SPIFFS用リリース  
  
Licence:  
  
  MITライセンス　　
  Copyright (c) 2017 Mgo-tec  
  
  東雲フォントは/efont/さんが保守開発を行い、ライセンスはPublic Domainです。  
  
詳しくはブログ参照：  
https://www.mgo-tec.com  