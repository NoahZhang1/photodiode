#include <ESP8266TimerInterrupt.h>
#define SAMPLE_RATE_HZ 500
#define SAMPLE_INTERVAL_US (1000000 / SAMPLE_RATE_HZ)
#define USING_TIM_DIV1                true           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              false            // for longest timer but least accurate. Default

ESP8266Timer ITimer;
void print_sample();
const int analogInPin = A0;
unsigned int potentiometer;
unsigned long long timeMeasured;

void print_sample(){
  potentiometer = analogRead(A0);
  timeMeasured = micros();
  Serial.print(timeMeasured);
  Serial.print(',');
  Serial.println(potentiometer);
//  Serial.print(',');
//  Serial.print(timeMeasured);
//  Serial.print(',');
//  Serial.println("test");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(200);
  ITimer.attachInterruptInterval(SAMPLE_INTERVAL_US, print_sample);
//  timer1.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
