#include<M5Core2.h>
#include<timer.h>
#include<ball.h>
#include<line.h>
#include<Cam.h>

#define num 8
#define reseive_lenth 7
#define reseive_avaliable 4
#define send_lenth 7

BALL ball;
LINE line;
Cam cam_front(4);

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
uint8_t send[send_lenth] = {38,0,0,0,0,0,37};
int send_flag = 0;

int M_val = 175;
int goal_color = 0;
int ball_ang = 0;
int ball_far = 0;
int ball_get = 0;
int ball_get_val = 0;
int line_ang = 0;
int cam_size = 0;
int cam_ang = 0;
int cam_on = 0;
int line_flag[24];
int avaliable[5];
int val_flag = 0;
int robot_dir = 0;
int enter_flag = 0;
timer t;

void setup() {
  M5.begin();
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);
  pinMode(Tact,INPUT);
  attachInterrupt(digitalPinToInterrupt(A_pin), pulse_counter, CHANGE);
  M5.Lcd.setTextSize(3);
  Serial.begin(9600);
  Serial2.begin(9600);
  M5.Lcd.setCursor(100,100);
  M5.Lcd.printf("waiting...");
  delay(1000);
}

void loop() {
  int now_pos = count;
  int change_flag = 0;
  send_flag = 0;
  int s = digitalRead(Tact);
  ball.getBallposition();
  line.getLINE_Vec();
  cam_front.getCamdata();

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

      send[1] = 3;
      send[2] = 0;
      send_flag = 1;
    }

    if(change_flag == 1){
      int u_1 = u;
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
    if(A == 5){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("checkCam");
      }
    }
    if(A == 6){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("Test");
      }
    }
    if(A == 7){
      if(A != B || flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60,100);
        M5.Lcd.setTextSize(3);
        M5.Lcd.printf("enterData");
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
          M5.Lcd.printf("Yellow");
        }
        else{
          M5.Lcd.printf("Blue");
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
      send[1] = 2;
      send[2] = goal_color;
      send_flag = 1;
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

      send[1] = 1;
      send[2] = M_val;
      send_flag = 1;

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

        send[1] = 4;
        send[2] = 0;
        send_flag = 1;
      }

      M5.Lcd.setCursor(100,30);
      M5.Lcd.printf("%d",ball.ang);
      M5.Lcd.setCursor(100,80);
      M5.Lcd.printf("%d",ball.far);
      M5.Lcd.setCursor(160,130);
      M5.Lcd.printf("%d",ball.get_1);
      M5.Lcd.setCursor(100,180);
      M5.Lcd.printf("%d",ball.get_2);
    }
    if(A == 3){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.printf(" ang : ");
        M5.Lcd.setCursor(0,80);
        M5.Lcd.printf(" on_ : ");

        send[1] = 5;
        send[2] = 0;
        send_flag = 1;
      }
      M5.Lcd.setCursor(100,30);
      M5.Lcd.printf("%d",line.ang);
      M5.Lcd.setCursor(100,80);
      M5.Lcd.setTextSize(3);
      for(int i = 0; i < 12;i++){
        M5.Lcd.printf("%d",line.data_on[i]);
      }
      M5.Lcd.printf("\n");
      M5.Lcd.setCursor(100,120);
      for(int i = 12; i < 27;i++){
        M5.Lcd.printf("%d",line.data_on[i]);
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

    if(A == 5){
      if(flag == 1){
        B = A;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,30);
        M5.Lcd.printf("ang : ");
        M5.Lcd.setCursor(0,80);
        M5.Lcd.printf("size : ");
        M5.Lcd.setCursor(0,130);
        M5.Lcd.printf("on : ");
        M5.Lcd.setCursor(0,180);
        M5.Lcd.printf("senter : ");

        send[1] = 6;
        send[2] = 0;
        send_flag = 1;

      }

      M5.Lcd.setCursor(100,30);
      M5.Lcd.printf("%d",cam_front.ang);
      M5.Lcd.setCursor(100,80);
      M5.Lcd.printf("%d",cam_front.Size);
      M5.Lcd.setCursor(100,130);
      M5.Lcd.printf("%d",cam_front.on);
      M5.Lcd.setCursor(160,180);
      M5.Lcd.printf("%d",cam_front.senter);
    }

    if(A == 6){
      if(flag == 1){
        B = A;
      }
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
        M5.Lcd.setCursor(0,60);
        M5.Lcd.printf("goal_color : %s",goal_color == 0 ? "Y" : "B");
        M5.Lcd.setCursor(0,100);
        M5.Lcd.printf("Motor_val : %d",M_val);
        M5.Lcd.setCursor(0,140);
        M5.Lcd.printf("AC_dir : %d",robot_dir);
        if(enter_flag == 1){
          send[1] = 3;
          send[2] = 1;
          send_flag = 1;
        }
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

      send[1] = 0;
      for(int i = 2; i < 6; i++){
        send[i] = avaliable[i-2];
      }
      send_flag = 1;
    }
    C = 2;
  }


  if(A_switch == 3){
    int flag = 0;
    if(A_switch != B_switch){
      B_switch = A_switch;
      flag = 1;
      M5.Lcd.fillScreen(BLACK);
    }
    if(A == 0){
      if(flag == 1){
        M5.Lcd.setCursor(0,20);
        M5.Lcd.printf("running...");
        if(enter_flag == 1){
          send[1] = 3;
          send[2] = 2;
          send_flag = 1;
        }
      }
    }
    C = 3;
  }


  enter_flag = 0;

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

      if(C == 0){
        enter_flag = 1;
      }

      if(C == 2 && (A == 0 || A == 4)){
        A_switch = 0;
      }

      if(C == 1 && (A == 0 || A == 4)){
        A_switch = 2;
      }

      if(C == 1 & A == 0){
        enter_flag = 1;
      }

      if(C == 2 && A == 0){
        enter_flag = 1;
        A_switch = 3;
      }

      if(C == 3 && A == 0){
        A_switch = 0;
        enter_flag = 1;
      }
    }
  }

  old_pos = now_pos;
  Serial.println();

  if(send_flag == 1){
    Serial2.write(send,send_lenth);
  }
}

void pulse_counter() {
  if(digitalRead(A_pin) ^ digitalRead(B_pin)) {
    count--;
  } else {
    count++;
  }
}


void serialEvent2(){
  uint8_t read[reseive_lenth];
  if(Serial2.available() < reseive_lenth){
    return;
  }
  read[0] = Serial2.read();
  if(read[0] != 38){
    return;
  }
  for(int i = 1; i < reseive_lenth; i++){
    read[i] = Serial2.read();
  }

  if(read[0] == 38 && read[reseive_lenth-1] == 37){
    if(read[1] == 0){
      for(int i = 0; i < reseive_avaliable; i++){
        avaliable[i] = read[i+2];
      }
      for(int i = 0; i < reseive_avaliable; i++){
        Serial.print(" ");
        Serial.print(avaliable[i]);
      }
    }
    if(read[1] == 1){
      M_val = read[2];
    }
    if(read[1] == 2){
      goal_color = read[2];
    }
    if(read[1] == 4){
      ball.x_pos = read[2];
      ball.y_pos = read[3];
      ball.get_1 = read[4];
      ball.get_2 = read[5];
    }
    if(read[1] == 5){
      line.data_byte[0] = read[2];
      line.data_byte[1] = read[3];
      line.data_byte[2] = read[4];
      line.data_byte[3] = read[5];
    }
    if(read[1] == 6){
      cam_front.data_byte[0] = read[2];
      cam_front.data_byte[1] = read[3];
      cam_front.data_byte[2] = read[4];
      cam_front.data_byte[3] = read[5];
    }
  }
  Serial.println();
}