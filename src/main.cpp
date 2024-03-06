#include<M5Core2.h>
#include<timer.h>
const int A_pin = 25; // 割り込みピン
const int B_pin = 26;
int count = 0;
void pulse_counter();
int old_pos = 0;

void setup() {
  M5.begin();
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.print(" pos : ");
  Serial.print(count);
}

void pulse_counter() {
  if(digitalRead(A_pin) ^ digitalRead(B_pin)) {
    count++;
  } else {
    count--;
  }
}