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
int goal_color = 0;
int far = 0;
int ang = 0;
int get_val = 100;
int get = 1;
int line_flag[24];
int avaliable[5];
int val_flag = 0;
timer t;

void setup() {
  M5.begin();
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  pinMode(Tact,INPUT);
  attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  M5.Lcd.setTextSize(3);
  Serial.begin(9600);
  M5.Lcd.setCursor(100,100);
  M5.Lcd.printf("waiting...");
  delay(1000);
}

void loop() {
  int now_pos = count;
  int change_flag = 0;
  int s = digitalRead(Tact);
  if(s == LOW){
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
        M5.Lcd.printf("goal_color: ");
        M5.Lcd.setCursor(210,100);
        if(goal_color == 0){
          M5.Lcd.printf("Blue");
        }
        else{
          M5.Lcd.printf("Yellow");
        }
      }

      M5.Lcd.setCursor(210,100);
      if(change_flag != 0){
        if(goal_color == 0){
          goal_color = 1;
          M5.Lcd.printf("Yellow");
        }
        else{
          goal_color = 0;
          M5.Lcd.printf("Blue  ");
        }
      }
    }
    if(A == 1){
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
    if(A == 2){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.printf("ang : ");
        M5.Lcd.setCursor(0,80);
        M5.Lcd.printf("far : ");
        M5.Lcd.setCursor(0,130);
        M5.Lcd.printf("get_val : ");
        M5.Lcd.setCursor(0,180);
        M5.Lcd.printf("get : ");
      }

      M5.Lcd.setCursor(100,30);
      M5.Lcd.printf("%d",ang);
      M5.Lcd.setCursor(100,80);
      M5.Lcd.printf("%d",far);
      M5.Lcd.setCursor(160,130);
      M5.Lcd.printf("%d",get_val);
      M5.Lcd.setCursor(100,180);
      M5.Lcd.printf("%d",get);
    }
    if(A == 3){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.printf(" ang : ");
        M5.Lcd.setCursor(0,80);
        M5.Lcd.printf(" on_ : ");
      }
      M5.Lcd.setCursor(100,30);
      M5.Lcd.printf("%d",ang);
      M5.Lcd.setCursor(100,80);
      M5.Lcd.setTextSize(3);
      for(int i = 0; i < 12;i++){
        M5.Lcd.printf("%d",line_flag[i]);
      }
      M5.Lcd.printf("\n");
      M5.Lcd.setCursor(100,120);
      for(int i = 12; i < 24;i++){
        M5.Lcd.printf("%d",line_flag[i]);
      }
    }
    if(A == 4){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.print("avaliable_1 :");
        M5.Lcd.setCursor(0,80);
        M5.Lcd.print("avaliable_2 :");
        M5.Lcd.setCursor(0,130);
        M5.Lcd.print("avaliable_3 :");
        M5.Lcd.setCursor(0,180);
        M5.Lcd.print("avaliable_4 :");
      }

      if(change_flag != 0){
        int u_1 = u / 2;
        int u_2 = u_1 % 4;
        if(u_2 < 0){
          u_2 += 4;
        }
        val_flag = u_2;
      }
      
      for(int i = 0; i < 4; i++){
        if(val_flag != i){
          M5.Lcd.setCursor(240,30+50*i);
          M5.Lcd.printf("  ");
        }
      }
      M5.Lcd.setCursor(240,30+50*val_flag);
      M5.Lcd.printf("<");
    }
    C = 1;
  }

  if(A_switch == 2){
    int flag = 0;
    if(A_switch != B_switch){
      B_switch = A_switch;
      M5.Lcd.fillScreen(BLACK);
      flag = 1;
    }
    if(A == 0){
      if(flag == 1){
        M5.Lcd.setCursor(0,120);
        M5.Lcd.printf("waiting...");
      }
    }

    if(A == 4){
      if(flag == 1){
        M5.Lcd.setCursor(0,100);
        M5.Lcd.printf("avaliable_%d :",val_flag+1);
      }
      if(change_flag != 0){
        if(change_flag == 1){
          avaliable[val_flag] += 1;
        }
        else if(change_flag == -1){
          avaliable[val_flag] -= 1;
        }
        M5.Lcd.setCursor(240,100);
        M5.Lcd.printf("  ");
        M5.Lcd.setCursor(240,100);
        M5.Lcd.printf("%d",avaliable[val_flag]);
      }
    }
    C = 2;
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

      if(C == 2 && (A == 0 || A == 4)){
        A_switch = 0;
      }

      if(C == 1 && (A == 0 || A == 4)){
        A_switch = 2;
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