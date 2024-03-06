#include<M5Core2.h>
#include<timer.h>

#define num 5

int A = 0;
int B = 999;
int u = 0;
int u_1 = 0;
const int A_pin = 25; // 割り込みピン
const int B_pin = 26;
int count = 0;
void pulse_counter();
int old_pos = 0;
timer t;

void setup() {
  M5.begin();
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  M5.Lcd.setTextSize(4);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  int now_pos = count;
  if(now_pos != old_pos && 100 < t.read_ms()){
    if(now_pos < old_pos){
      u++;
    }
    else{
      u--;
    }
    u_1 = u / 2;
    A = u_1 % num;
    if(A < 0){
      A += num;
    }
    t.reset();
    Serial.print(" pos : ");
    Serial.print(A);
    Serial.print(" u : ");
    Serial.println(u);
  }

  if(A == 0){
    if(A != B){
      B = A;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,100);
      M5.Lcd.printf(" 1 ");
    }
  }

  if(A == 1){
    if(A != B){
      B = A;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,100);
      M5.Lcd.printf(" 2 ");
    }
  }

  if(A == 2){
    if(A != B){
      B = A;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,100);
      M5.Lcd.printf(" 3 ");
    }
  }

  if(A == 3){
    if(A != B){
      B = A;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,100);
      M5.Lcd.printf(" 4 ");
    }
  }

  if(A == 4){
    if(A != B){
      B = A;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,100);
      M5.Lcd.printf(" 5 ");
    }
  }
  old_pos = now_pos;
}

void pulse_counter() {
  if(digitalRead(A_pin) ^ digitalRead(B_pin)) {
    count++;
  } else {
    count--;
  }
}