#define NUM_NOTES 21

#define DO 261
#define RE 293
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define T 250
#define BUTTON_PIN 5
#define PIN_TONE 9

#include <Servo.h>

Servo myservo;
void setup() {
  myservo.attach(8);
  myservo.write(90);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, 0);
  delay(50);
  myservo.detach();
}

// int frequency[] = {MI, LA, LA, MI, MI, DO, MI, MI, MI, MI, DO, RE, RE, RE, RE};
int frequency[] = {MI, LA, LA, MI, MI, DO, MI, MI, MI, MI, DO, RE, RE, RE, RE};
int duration[] = {
  T, T, T, T, T, T*3,
  T*2, T, T*2, T*3,
  50, T*2, T, T*2, T*3
};

int pos[] = {
  45, 65, 45, 135, 115, 135 
};

int ind = 0;
bool btn_state = 0;
uint8_t duration_serv = 250;
uint32_t timer_btn = 0;


void move_cow(){
  myservo.attach(8);
  digitalWrite(7, 1);
  delay(200);
  uint32_t timer = 0;
  uint32_t timer_serv = 0;  
  int ind_serv = 0;
  int bebra = 0;
  int bober = 2;
  while (bober >= 0){
    if (millis() - timer > bebra) {
      tone(PIN_TONE, frequency[ind], duration[ind]);
      bebra = duration[ind];
      ind = (ind + 1) % (sizeof(frequency)/sizeof(int));
      if (sizeof(frequency) / sizeof(int) - ind == 1){
      bober--;
    }
      timer = millis();
    }

    if (millis() - timer_serv > duration_serv){
      timer_serv = millis();
      myservo.write(pos[ind_serv]);
      ind_serv = (ind_serv + 1) % (sizeof(pos)/sizeof(int));
    }
    
    if (bober == 0 && ind == 6) {
      ind = 0;
      break; 
    }
  }
  while(millis() - timer < bebra) {};
  digitalWrite(7, 0);
  myservo.write(90);
  delay(50);
  myservo.detach();
}

void loop() {
  if (digitalRead(BUTTON_PIN)){
    move_cow();
  }
}
