#include <Arduino.h>
#include <Servo.h>

Servo frontServo;
Servo backServo;

#define ENC1 2
#define ENC2 3

#define L1 4
#define L2 5

#define R1 7
#define R2 6

#define ARENA 32

#define MID1 A5
#define MID2 A6

#define F_SERVO 40
#define B_SERVO 44

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

void halt();

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

void forwardWithEncoder(int pwm, int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    forward(pwm);
    interrupts();
  }
  halt();
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

void backwardWithEncoder(int pwm, int ticks, int stopdelay = 0)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    backward(pwm);
    interrupts();
  }
  delay(stopdelay);
  halt();
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
  while (enc1_counter < 240)
  {
    left(pwm);
    interrupts();
  }
  halt();
}

void leftTurnEncoder(int pwm, int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
  {
    left(pwm);
    interrupts();
  }
  halt();
}

void right90(int pwm1, int pwm2 = 0)
{
  pwm2 = pwm1;
  enc1_counter = 0;
  while (enc1_counter < 240)
  {
    right(pwm1, pwm2);
    interrupts();
  }
  halt();
}

void rightTurnEncoder(int pwm, int ticks)
{
  enc1_counter = 0;
  while (enc1_counter < ticks)
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

void linefollow(int speed = 50)
{
  // white 1
  // black 0

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

void linefollowEncoder(int ticks)
{
  Serial.print("ENCODER1: ");
  Serial.println(enc1_counter);
  enc1_counter = 0;
  Serial.print("ENCODER2: ");
  Serial.println(enc1_counter);
  while (enc1_counter < ticks)
  {
    linefollow(30);
    interrupts();
  }
  halt();
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

void frontServoMove(int start, int end)
{
  if (start > end)
  {
    for (int i = start; i > end; i--)
    {
      frontServo.write(i);
      delay(30);
    }
  }
  else
  {
    for (int i = start; i < end; i++)
    {
      frontServo.write(i);
      delay(30);
    }
  }
}

void backServoMove(int start, int end)
{
  if (start > end)
  {
    for (int i = start; i > end; i--)
    {
      backServo.write(i);
      delay(30);
    }
  }
  else
  {
    for (int i = start; i < end; i++)
    {
      backServo.write(i);
      delay(30);
    }
  }
}

void backLinefollow(int speed = 50)
{
  // white 1
  // black 0

  // S2[3] == left
  // S2[2] == middle
  // S2[1] == right

  int left1 = analogRead(S2[3]) > 800 ? 1 : 0;
  int middle1 = analogRead(S2[2]) > 800 ? 1 : 0;
  int right1 = analogRead(S2[1]) > 800 ? 1 : 0;

  if (left1 == 0 && middle1 == 0 && right1 == 0)
  {
    backward(speed);
  }
  else if (left1 == 1 && middle1 == 0 && right1 == 1)
  {
    backward(speed);
  }
  else if (left1 == 0 && middle1 == 1 && right1 == 1)
  {
    right(speed);
  }
  else if (left1 == 1 && middle1 == 1 && right1 == 0)
  {
    left(speed);
  }
  else
  {
    backward(speed);
  }
}

void backLinefollowUntil(int strips)
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
      backLinefollow();
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

void backLinefollowEncoder(int ticks)
{
  Serial.print("ENCODER1: ");
  Serial.println(enc1_counter);
  enc1_counter = 0;
  Serial.print("ENCODER2: ");
  Serial.println(enc1_counter);
  while (enc1_counter < ticks)
  {
    backLinefollow(30);
    interrupts();
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

  frontServo.attach(F_SERVO);
  backServo.attach(B_SERVO);

  frontServo.write(95);
  backServo.write(95);

  for (size_t i = 0; i < sizeof(S1) / sizeof(int); i++)
  {
    pinMode(S1[i], INPUT);
  }

  for (size_t i = 0; i < sizeof(S2) / sizeof(int); i++)
  {
    pinMode(S2[i], INPUT);
  }

  delay(1000);
}

void red()
{
  // start
  linefollowUntil(4);
  delay(1000);
  // first right turn
  right90(80);
  delay(1000);
  // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(1000);
  // turn right after 3 strips
  right90(80);
  delay(1000);
  // move back to center on line
  backwardWithEncoder(50, 150, 200);
  delay(1000);
  // move servo down for pickup
  // frontServoMove(95, 0);
  frontServo.write(0);

  delay(1000);

  // ============= first tree and rock =============
  // move until first tree
  linefollowEncoder(280);
  delay(1000);
  // move servo up after pickup
  frontServoMove(0, 90);
  delay(1000);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(1000);
  // turn right for rock
  right90(83);
  backServo.write(0);
  // backServoMove(95, 0);
  delay(1000);
  // move back 3 strips
  backwardWithEncoder(50, 60);
  backLinefollowUntil(3);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90);
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 5);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 3 strip to drop rock at original tree position
  backLinefollowUntil(3);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);
  // ============= first tree and rock =============

  // ============= second tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServoMove(0, 95);
  delay(500);
  // turn right
  right90(80);
  delay(1000);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(1000);
  // move front servo down for tree pickup
  frontServoMove(95, 0);
  delay(500);
  // move forward to tree
  linefollowEncoder(200);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(1000);
  // turn right for rock
  right90(80);
  delay(1000);
  // move back 2 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90);
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 5);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 2 strip to drop rock at original tree position
  backLinefollowUntil(2);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);
  // ============= second tree and rock =============

  // ============= third tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServoMove(0, 95);
  delay(500);
  // turn right
  right90(80);
  delay(1000);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(1000);
  // move front servo down for tree pickup
  frontServoMove(95, 0);
  delay(500);
  // move forward to tree
  linefollowEncoder(200);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(1000);
  // turn right for rock
  right90(80);
  delay(1000);
  // move back 1 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90);
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 5);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 1 strip to drop rock at original tree position
  backLinefollowUntil(1);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);

  /// waqas code
  frontServo.write(100);
  delay(1000);
  linefollowUntil(1);
  linefollowEncoder(10);

  delay(1000);
  left90(80);
  delay(1000);
  linefollowEncoder(60);
  linefollowUntil(4);
  linefollowEncoder(250);
  delay(1000);

  // ============= third tree and rock =============
  while (1)
  {
    Serial.println("END");
  }
}

void blue()
{
  // start
  linefollowUntil(4);
  delay(1000);
  // first right turn
  left90(80);
  delay(1000);
  // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(1000);
  // turn right after 3 strips
  left90(80);
  delay(1000);
  // move back to center on line
  backwardWithEncoder(50, 150, 200);
  delay(500);
  // move servo down for pickup
  frontServoMove(95, 0);
  frontServo.write(0);

  delay(500);

  // ============= first tree and rock =============
  // move until first tree
  linefollowEncoder(280);
  delay(500);
  // move servo up after pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(1000);
  // turn left for rock
  left90(80);
  backServo.write(0);
  // backServoMove(95, 0);
  delay(1000);
  // move back 3 strips
  backwardWithEncoder(50, 60);
  backLinefollowUntil(3);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90);
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 5);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 3 strip to drop rock at original tree position
  backLinefollowUntil(3);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);
  //============= first tree and rock =============

  // ============= second tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServoMove(0, 95);
  delay(500);
  // turn right
  left90(80);
  delay(1000);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(1000);
  // move front servo down for tree pickup
  frontServoMove(95, 0);
  delay(500);
  // move forward to tree
  linefollowEncoder(200);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(1000);
  // turn right for rock
  left90(80);
  delay(1000);
  // move back 2 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90);
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 10);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 2 strip to drop rock at original tree position
  backLinefollowUntil(2);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);
  // ============= second tree and rock =============

  // ============= third tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServoMove(0, 95);
  delay(500);
  // turn right
  left90(80);
  delay(1000);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(1000);
  // move front servo down for tree pickup
  frontServoMove(95, 0);
  delay(500);
  // move forward to tree
  linefollowEncoder(200);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(1000);
  // turn right for rock
  left90(80);
  delay(1000);
  // move back 1 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90);
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 10);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 1 strip to drop rock at original tree position
  backLinefollowUntil(1);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);

  /// waqas code
  frontServo.write(100);
  delay(1000);
  linefollowUntil(1);
  linefollowEncoder(10);

  delay(1000);
  right90(80);
  delay(1000);
  linefollowEncoder(60);
  linefollowUntil(4);
  linefollowEncoder(250);
  delay(1000);

  // ============= third tree and rock =============
  while (1)
  {
    Serial.println("END");
  }
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
  }
  else
  {
    // BLUE ARENA
    blue();
  }
}