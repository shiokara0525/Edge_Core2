#include<M5Core2.h>
const int A_pin = 25; // 割り込みピン
const int B_pin = 26;
int count = 0;
void pulse_counter();
 
void setup() {
  M5.begin();
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  Serial.begin(9600);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf(" please wait... ");
  delay(1000);
}
 
void loop() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,100);
  M5.Lcd.printf(" enc : %d",count);
  delay(1000);
}
 
void pulse_counter() {
  if(digitalRead(A_pin) ^ digitalRead(B_pin)) {
    count++;
  } else {
    count--;
  }
}