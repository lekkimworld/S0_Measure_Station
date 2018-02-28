#define BLINK_TIME_MS 100
#define IRQ_PIN_S0_1 18
#define IRQ_PIN_S0_2 19
#define IRQ_PIN_S0_3 20
#define IRQ_PIN_S0_4 21
#define IRQ_PIN_S0_5 2
#define LED_PIN_S0_1 8
#define LED_PIN_S0_2 9
#define LED_PIN_S0_3 10
#define LED_PIN_S0_4 11
#define LED_PIN_S0_5 12

typedef struct S0Sensor {
  uint8_t pin_led;
  uint8_t pin_irq;
  volatile unsigned long pulseCount = 0L;
  unsigned long pulseBlink = 0L;
  unsigned long ledTime = 0L;
  unsigned int pulsesPerKwh = 1000;
};

// define variables for each sensor
S0Sensor s1;
S0Sensor s2;
S0Sensor s3;
S0Sensor s4;
S0Sensor s5;

void setup() {
  // configure serial
  //Serial.begin(9600);

  // configure sensors
  configureSensors();
  
}

void loop() {
  // check each sensor if pulseBlink is different than pulseCount we blink the corresponding LED
  if (s1.pulseCount != s1.pulseBlink) startLedBlink(&s1);
  if (s2.pulseCount != s2.pulseBlink) startLedBlink(&s2);
  if (s3.pulseCount != s3.pulseBlink) startLedBlink(&s3);
  if (s4.pulseCount != s4.pulseBlink) startLedBlink(&s4);
  if (s5.pulseCount != s5.pulseBlink) startLedBlink(&s5);


  // check each sensor and turn of LED if it has been on for long enough
  stopLedBlink(&s1); stopLedBlink(&s2); stopLedBlink(&s3); stopLedBlink(&s4); stopLedBlink(&s5);
}



void startLedBlink(S0Sensor *s) {
  digitalWrite(s->pin_led, HIGH);
  s->ledTime = millis();
  s->pulseBlink = s->pulseCount;
}
void stopLedBlink(S0Sensor *s) {
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - s->ledTime) > BLINK_TIME_MS) {
    digitalWrite(s->pin_led, LOW);
  }
}

void isr_S0_1() {
  s1.pulseCount++;
}
void isr_S0_2() {
  s2.pulseCount++;
}
void isr_S0_3() {
  s3.pulseCount++;
}
void isr_S0_4() {
  s4.pulseCount++;
}
void isr_S0_5() {
  s5.pulseCount++;
}

void configureSensors() {
  s1.pin_led = LED_PIN_S0_1;
  s1.pin_irq = IRQ_PIN_S0_1; 
  pinMode(s1.pin_irq, INPUT);
  pinMode(s1.pin_led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(s1.pin_irq), isr_S0_1, FALLING);
  digitalWrite(s1.pin_led, LOW);
  
  s2.pin_led = LED_PIN_S0_2;
  s2.pin_irq = IRQ_PIN_S0_2;
  pinMode(s2.pin_irq, INPUT);
  pinMode(s2.pin_led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(s2.pin_irq), isr_S0_2, FALLING);
  digitalWrite(s2.pin_led, LOW);

  s3.pin_led = LED_PIN_S0_3;
  s3.pin_irq = IRQ_PIN_S0_3;
  pinMode(s3.pin_irq, INPUT);
  pinMode(s3.pin_led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(s3.pin_irq), isr_S0_3, FALLING);
  digitalWrite(s3.pin_led, LOW);

  s4.pin_led = LED_PIN_S0_4;
  s4.pin_irq = IRQ_PIN_S0_4; 
  pinMode(s4.pin_irq, INPUT);
  pinMode(s4.pin_led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(s4.pin_irq), isr_S0_4, FALLING);
  digitalWrite(s4.pin_led, LOW);

  s5.pin_led = LED_PIN_S0_5;
  s5.pin_irq = IRQ_PIN_S0_5; 
  pinMode(s5.pin_irq, INPUT);
  pinMode(s5.pin_led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(s5.pin_irq), isr_S0_5, FALLING);
  digitalWrite(s5.pin_led, LOW);
}


