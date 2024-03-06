#include<M5Core2.h>
#include<timer.h>

#define num 5

int A = 0;
int B = 999;
int C = 0;
int A_switch = 0;
int B_switch = 999;
int u = 0;
const int A_pin = 25; // 割り込みピン
const int B_pin = 26;
const int Tact = 36;
int count = 0;
void pulse_counter();
int old_pos = 0;

int M_val = 175;
timer t;

void setup() {
  M5.begin();
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  pinMode(Tact,INPUT);
  attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  M5.Lcd.setTextSize(4);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  int now_pos = count;
  int change_flag = 0;
  int s = digitalRead(Tact);
  if(A_switch != 5 && s == LOW){
    A_switch = 5;
  }
  if(now_pos != old_pos && 10 < t.read_ms()){
    if(now_pos < old_pos){
      change_flag = 1;
      u++;
    }
    else{
      change_flag = -1;
      u--;
    }
  }

  if(A_switch == 0){
    int flag = 0;
    if(A_switch != B_switch){
      B_switch = A_switch;
      flag = 1;
    }

    if(change_flag == 1){
      int u_1 = u / 2;
      A = u_1 % num;
      if(A < 0){
        A += num;
      }
    }

    if(A == 0){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(80,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("Start");
      }
    }

    if(A == 1){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(70,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("setMotor");
      }
    }

    if(A == 2){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(70,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("checkBall");
      }
    }

    if(A == 3){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(70,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("checkLine");
      }
    }

    if(A == 4){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("setValiables");
      }
    }
    C = 0;
  }

  if(A_switch == 1){
    int flag = 0;
    if(A_switch != B_switch){
      B_switch = A_switch;
      flag = 1;
    }
    if(A == 0){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("Motor_val : ");
      }

      if(change_flag == 1){
        M_val += 5;
      }
      if(change_flag == -1){
        M_val -= 5;
      }
      
      M5.Lcd.setCursor(200,100);
      M5.Lcd.printf("%d",M_val);
    }
    if(A == 1){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,100);
        M5.Lcd.printf(" 20 ");
      }
    }
    if(A == 2){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,100);
        M5.Lcd.printf(" 30 ");
      }
    }
    if(A == 3){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,100);
        M5.Lcd.printf(" 40 ");
      }
    }
    if(A == 4){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,100);
        M5.Lcd.printf(" 50 ");
      }
    }
    C = 1;
  }

  if(A_switch == 5){
    if(A_switch != B_switch){
      B_switch = A_switch;
      M5.Lcd.fillScreen(BLACK);
    }
    if(s == 1){
      if(C == 0){
        A_switch = 1;
      }
      else{
        A_switch = 0;
      }
    }
  }

  old_pos = now_pos;
  Serial.println();
}

void pulse_counter() {
  if(digitalRead(A_pin) ^ digitalRead(B_pin)) {
    count--;
  } else {
    count++;
  }
}