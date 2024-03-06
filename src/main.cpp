#include<M5Core2.h>
#include<timer.h>

int A = 0;
int B = 999;
const int A_pin = 25; // 割り込みピン
const int B_pin = 26;
int A__ = 0;
int A__old = 999;
int count = 0;
void pulse_counter();
int old_pos = 999;
timer t;

void setup() {
  M5.begin(true,true,true,false,kMBusModeInput,true);
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  // attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  Serial.begin(9600);
  M5.Lcd.setTextSize(5);
  M5.Lcd.printf(" please wait... ");
  delay(1000);
}

void loop() {
  int now_pos = count;
  A__ = digitalRead(A_pin);
  if(100 < t.read_ms()){
    if(A__ != A__old){
      pulse_counter();
    }
  }

  Serial.print(" pos : ");
  Serial.println(now_pos);
  if(now_pos != old_pos){
    if(old_pos < now_pos){
      if(A <= 5){
        A += 5;
      }
      else{
        A = 0;
      }
    }
    else{
      if(A == 0){
        A = 10;
      }
      else{
        A -= 5;
      }
    }
  }

  if(A == 0){
    if(A != B){
      M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
      M5.Lcd.setCursor(0, 100);     // カーソルの位置
      M5.Lcd.printf("1");
      B = A;
    }

  }
  
  if(A == 5){
    if(A != B){
      M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
      M5.Lcd.setCursor(0, 100);     // カーソルの位置
      M5.Lcd.printf("2");
      B = A;
    } 
  }

  if(A == 10){
    if(A != B){
      M5.Lcd.fillScreen(BLACK);  // 画面の塗りつぶし
      M5.Lcd.setCursor(0, 100);     // カーソルの位置
      M5.Lcd.printf("3");
      B = A;
    }
  }
  delay(100);
  old_pos = now_pos;
  A__old = A__;
}

void pulse_counter() {
  if(digitalRead(A_pin) ^ digitalRead(B_pin)) {
    count++;
  } else {
    count--;
  }
}