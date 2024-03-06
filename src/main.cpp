#include <M5Core2.h>
#include<Encoder.h>

#define Tact 36 //押してるとき0
int count = 0;
int A = 0;
int B = 999;
int C = 0;

Encoder encoder(26,25);

void setup() {
  Serial.begin(9600);
  M5.begin(true,true,true,true);
  pinMode(Tact,INPUT);
  M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
  M5.Lcd.setCursor(0, 100);     // カーソルの位置
  M5.Lcd.setTextSize(5);
  M5.Lcd.printf("waiting...");
  delay(1000);
}

void loop() {
  if(digitalRead(Tact) == 0){
    if(A <= 5){
      A += 5;
    }
    else{
      A = 0;
    }
    M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
    delay(100);
  }

  if(A == 0){
    if(A != B){
      M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
      M5.Lcd.setCursor(0, 100);     // カーソルの位置
      M5.Lcd.printf("check ball");
      B = A;
    }

  }
  
  if(A == 5){
    if(A != B){
      M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
      M5.Lcd.setCursor(0, 100);     // カーソルの位置
      M5.Lcd.printf("check line");
      B = A;
    } 
  }

  if(A == 10){
    if(A != B){
      M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
      M5.Lcd.setCursor(0, 100);     // カーソルの位置
      M5.Lcd.printf("set Motor");
      B = A;
    }
  }
  delay(100);
}