#include <Ticker.h>
Ticker blinker1;
Ticker blinker2;
Ticker freqChangeTimer;
Ticker restTimer;

#define BLINK_PIN_1 D1
#define BLINK_PIN_2 D4

#define CHANGE_INTERVAL_MS 3000
#define BLANK_INTERVAL_MS 500

int pin1_state = 0;
int pin2_state = 0;

float pin1_freq_Hz = 4;
float pin2_freq_Hz = 100;

float pin1_min_freq_Hz = 4;
float pin1_max_freq_Hz = 100;
float pin1_freq_change = 4;

float pin2_min_freq_Hz = 4;
float pin2_max_freq_Hz = 100;
float pin2_freq_change = -4;

void setup() {
  Serial.begin(115200);
  pinMode(BLINK_PIN_1, OUTPUT);
  pinMode(BLINK_PIN_2, OUTPUT);
  digitalWrite(BLINK_PIN_1, pin1_state);
  digitalWrite(BLINK_PIN_2, pin2_state);
}

void clear_blink() {
  if (blinker1.active()) {
    blinker1.detach();
  }

  if (blinker2.active()) {
    blinker2.detach();
  }
  pin1_state = 0;
  pin2_state = 0;
  digitalWrite(BLINK_PIN_1, pin1_state);
  digitalWrite(BLINK_PIN_2, pin2_state);
}

void clear_all() {
  if (restTimer.active()) {
    restTimer.detach();
  }
  if (freqChangeTimer.active()) {
    freqChangeTimer.detach();
  }
  clear_blink();
}


void toggle_1() {
  pin1_state = !pin1_state;
  digitalWrite(BLINK_PIN_1, pin1_state);
}

void toggle_2() {
  pin2_state = !pin2_state;
  digitalWrite(BLINK_PIN_2, pin2_state);
}

void change_freq() {
  freqChangeTimer.detach();
  Serial.println("change_freq");
  clear_blink();
  pin1_freq_Hz += pin1_freq_change;
  if (pin1_freq_Hz > pin1_max_freq_Hz) {
    pin1_freq_Hz = pin1_min_freq_Hz;
  }
  if (pin1_freq_Hz < pin1_min_freq_Hz) {
    pin1_freq_Hz = pin1_max_freq_Hz;
  }

  pin2_freq_Hz += pin2_freq_change;
  if (pin2_freq_Hz > pin2_max_freq_Hz) {
    pin2_freq_Hz = pin2_min_freq_Hz;
  }
  if (pin2_freq_Hz < pin2_min_freq_Hz) {
    pin2_freq_Hz = pin2_max_freq_Hz;
  }

  restTimer.attach_ms_scheduled(BLANK_INTERVAL_MS, continue_task);
}

void continue_task() {
  restTimer.detach();
  Serial.print("continue_task ");
  Serial.print("f1: ");
  Serial.print(pin1_freq_Hz);
  Serial.print("Hz f2: ");
  Serial.print(pin2_freq_Hz);
  Serial.println("Hz");
  blinker1.attach_ms(500 / pin1_freq_Hz, toggle_1);
  blinker2.attach_ms(500 / pin2_freq_Hz, toggle_2);
  freqChangeTimer.attach_ms_scheduled(CHANGE_INTERVAL_MS, change_freq);
}

void start_task() {
  clear_all();
  pin1_freq_Hz = 4;
  pin2_freq_Hz = 100;
  Serial.print("start_task ");
  Serial.print("f1: ");
  Serial.print(pin1_freq_Hz);
  Serial.print("Hz f2: ");
  Serial.print(pin2_freq_Hz);
  Serial.println("Hz");
  blinker1.attach_ms(500 / pin1_freq_Hz, toggle_1);
  blinker2.attach_ms(500 / pin2_freq_Hz, toggle_2);
  freqChangeTimer.attach_ms_scheduled(CHANGE_INTERVAL_MS, change_freq);
}


void loop() {
  if (Serial.available()) {
    int c = Serial.read();
    switch(c) {

      case '1':
        Serial.println("start");
        start_task();
        break;

      case '0':
        Serial.println("End");
        clear_all();
        break;

      default:
        break;
    }  
  }
}
