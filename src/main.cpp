#include <M5Core2.h>

int count = 0;

void setup() {
  M5.begin();
}

void loop() {
  M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
  M5.Lcd.setCursor(0, 0);  // 文字列の書き出し位置
  M5.Lcd.setTextSize(5);  // 文字サイズを設定

  M5.Lcd.printf("Count: %d\n", count);  // LCDに表示
  count++;

  delay(1000);
}