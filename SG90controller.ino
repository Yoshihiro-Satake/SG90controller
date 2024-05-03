#include <Servo.h>
#define SIG_PIN 6
Servo myservo;

unsigned long int preT;
unsigned long int dT = 20;
unsigned long int startTime;
float theta_i = 0.0;
float theta_d = 180.0;
int Tmax = 1000;

float threePoly(int t_millis, int Tmax_millis, float startAngle, float endAngle){
  float T = float(t_millis)/float(Tmax_millis);
  float a0 = 0.0;
  float a1 = 0.0;
  float a2 = 3.0*(endAngle - startAngle);
  float a3 = -2.0*(endAngle - startAngle);
  return a0 + a1*T + a2*T*T + a3*T*T*T;
}

void setup() {
  // put your setup code here, to run once:
  int pulse_min = 544;
  int pulse_max = 2400;

  myservo.attach(SIG_PIN);
  myservo.write(0);
  Serial.begin(9600);
  delay(2000);
  startTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long int t = millis();
  if(t - preT >= dT){
    preT = t;
    if(t - startTime > Tmax){
      t = Tmax + startTime;
      Serial.println("fin");
    }
    float targetAngle = threePoly(t-startTime, Tmax, theta_i, theta_d);
    myservo.write(targetAngle);
  }
}
