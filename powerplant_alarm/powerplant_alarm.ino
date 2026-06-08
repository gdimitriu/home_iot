#include <avr/sleep.h>
#define SENSOR_LEFT_PIN 2
#define SENSOR_RIGHT_PIN 3
#define BUZZER_PIN 4
#define DEBUG 1
void wakeUp() {
#ifdef DEBUG
  Serial.println("wakeup");
#endif  
  sleep_disable();
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void going_to_Sleep()
{
#ifdef DEBUG
  Serial.println("going to sleep");
#endif
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  sleep_cpu();
}

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("starting");
#endif
  pinMode(SENSOR_LEFT_PIN, INPUT);
  pinMode(SENSOR_RIGHT_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  attachInterrupt(digitalPinToInterrupt(SENSOR_LEFT_PIN), wakeUp, RISING );
  //attachInterrupt(digitalPinToInterrupt(SENSOR_RIGHT_PIN), wakeUp, RISING );
}
void loop() {
  if (digitalRead(SENSOR_LEFT_PIN) == LOW)
  {
#ifdef DEBUG
        
    going_to_Sleep();
  }
}
