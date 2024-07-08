#include <Arduino.h>

#define ENC1 2
#define ENC2 3

#define L1 4
#define L2 5

#define R1 7
#define R2 6

#define ARENA 32

#define MID1 A5
#define MID2 A6

int S1[] = {A4, A3, A2, A1, A0};
int S2[] = {A8, A9, A10, A11, A12};

int strips_count = 0;
bool is_line = false;

int enc1_counter = 0;
int enc2_counter = 0;

unsigned long previousMillis = 0; // Store the last time sensor was checked
const long intervalMillis = 500;

void enc1_isr() { enc1_counter++; }

void enc2_isr() { enc2_counter++; }

void forward(int pwm1, int pwm2 = 0)
{
  if (pwm2 == 0)
    pwm2 = pwm1;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1);
  analogWrite(L2, 0);
  analogWrite(R1, pwm2 + 3);
  analogWrite(R2, 0);
}

void backward(int pwm1, int pwm2 = 0)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, 0);
  analogWrite(L2, pwm1);
  analogWrite(R1, 0);
  analogWrite(R2, pwm2);
}

void halt()
{
  noInterrupts();
  analogWrite(L1, 0);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, 0);
  interrupts();
}

void right(int pwm1, int pwm2 = 0)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, 0);
  analogWrite(L2, pwm1);
  analogWrite(R1, pwm2);
  analogWrite(R2, 0);
}

void left(int pwm1, int pwm2 = 0)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1);
  analogWrite(L2, 0);
  analogWrite(R1, 0);
  analogWrite(R2, pwm2);
}

void swerveLeft(int pwm1, int pwm2 = 0)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1);
  analogWrite(L2, 0);
  analogWrite(R1, pwm2 - (pwm2 / 3));
  analogWrite(R2, 0);
}

void swerveRight(int pwm1, int pwm2 = 0)
{
  if (pwm2 == 0)
    pwm2 = pwm1 + 3;
  if (pwm1 == 255)
    pwm2 = 255;

  analogWrite(L1, pwm1 - (pwm1 / 3));
  analogWrite(L2, 0);
  analogWrite(R1, pwm2);
  analogWrite(R2, 0);
}

void left90(int pwm)
{
  enc1_counter = 0;
  while (enc1_counter < 235)
  {
    left(pwm);
    interrupts();
  }
  halt();
}

void right90(int pwm)
{
  enc1_counter = 0;
  while (enc1_counter < 240)
  {
    right(pwm);
    interrupts();
  }
  halt();
}

void readSensorValsDebugAnalog(int *sensors)
{
  for (int i = 0; i < 5; i++)
  {
    Serial.print(analogRead(sensors[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

void readSensorValsDebugDigital(int *sensors)
{
  int leftm1 = analogRead(sensors[0]) > 800 ? 1 : 0;
  int left1 = analogRead(sensors[1]) > 800 ? 1 : 0;
  int middle1 = analogRead(sensors[2]) > 800 ? 1 : 0;
  int right1 = analogRead(sensors[3]) > 800 ? 1 : 0;
  int rightm1 = analogRead(sensors[4]) > 800 ? 1 : 0;

  Serial.print(leftm1);
  Serial.print("  ");
  Serial.print(left1);
  Serial.print("  ");
  Serial.print(middle1);
  Serial.print("  ");
  Serial.print(right1);
  Serial.print("  ");
  Serial.println(rightm1);
  delay(100);
}

void linefollow()
{
  // white 1
  // black 0

  int speed = 50;
  int left1 = analogRead(S1[1]) > 800 ? 1 : 0;
  int middle1 = analogRead(S1[2]) > 800 ? 1 : 0;
  int right1 = analogRead(S1[3]) > 800 ? 1 : 0;

  if (left1 == 0 && middle1 == 0 && right1 == 0)
  {
    forward(speed);
  }
  else if (left1 == 1 && middle1 == 0 && right1 == 1)
  {
    forward(speed);
  }
  else if (left1 == 0 && middle1 == 1 && right1 == 1)
  {
    left(speed);
  }
  else if (left1 == 1 && middle1 == 1 && right1 == 0)
  {
    right(speed);
  }
  else
  {
    forward(speed);
  }
}

void linefollowUntil(int strips)
{
  while (true)
  {
    int leftm1 = analogRead(MID2) > 700 ? 1 : 0;
    unsigned long currentMillis = millis();

    if (leftm1 == 0 && !is_line)
    {
      strips_count++;
      is_line = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      is_line = false;
    }

    if (strips_count < strips)
    {
      linefollow();
      Serial.print("hello: ");
      Serial.println(strips_count);
    }
    else
    {
      halt();
      strips_count = 0;
      return;
    }
  }
}

void stripCountDebug(int strips)
{
  int leftm1 = analogRead(MID2) > 700 ? 1 : 0;
  unsigned long currentMillis = millis();

  if (leftm1 == 0 && !is_line)
  {
    strips_count++;
    is_line = true;
    previousMillis = currentMillis;
  }
  else if (currentMillis - previousMillis > intervalMillis)
  {
    is_line = false;
  }

  if (strips_count < strips)
  {
    Serial.println(strips_count);
  }
  else
  {
    // halt();
    Serial.print(strips_count);
    Serial.print(" ");
    Serial.println("End");
    strips_count = 0;
    return;
  }
}

void forwardUntilMiddleSensors()
{
  int mid1_val = analogRead(MID1) > 800 ? 1 : 0;
  int mid2_val = analogRead(MID2) > 800 ? 1 : 0;

  while (mid1_val == 1 && mid2_val == 1)
  {
    forward(50);
    mid1_val = analogRead(MID1) > 800 ? 1 : 0;
    mid2_val = analogRead(MID2) > 800 ? 1 : 0;
  }
  halt();
}

void configurePins()
{
  pinMode(ENC1, INPUT);
  pinMode(ENC2, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC1), enc1_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC2), enc2_isr, RISING);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  pinMode(ARENA, INPUT_PULLUP);

  pinMode(MID1, INPUT);
  pinMode(MID2, INPUT);

  for (size_t i = 0; i < sizeof(S1) / sizeof(int); i++)
  {
    pinMode(S1[i], INPUT);
  }

  for (size_t i = 0; i < sizeof(S2) / sizeof(int); i++)
  {
    pinMode(S2[i], INPUT);
  }
}

void red()
{
  linefollowUntil(4);
  delay(1000);
  right90(80);
  delay(1000);
  linefollowUntil(3);
  while (1)
  {
    Serial.println("stuck");
  }
}

void blue()
{
}

void setup()
{
  Serial.begin(9600);

  configurePins();
}

void loop()
{
  if (digitalRead(ARENA))
  {
    // RED ARENA
    red();
    // stripCountDebug(5);
  }
  else
  {
    // BLUE ARENA
    blue();
  }
}
