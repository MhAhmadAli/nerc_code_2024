#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid7.h"

/*
 * Grid 7
 *
 *  grid is 3x3 the points are (1,2), (2,2) and (2,3)
 */

void red_grid7() {
  // =================== first tree and rock start ===================
  linefollowFiveEncoder(80);
  linefollowFiveUntil(4);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  frontServo.write(0);
  delay(500);
  linefollowFiveEncoder(200);
  frontServoMove(0, 90); // rock pick up
  linefollowUntil(1);
  delay(500);
  right90(80);
  backServo.write(0);
  delay(500);
  backLinefollowFiveEncoder(60);
  backLinefollowFiveUntil(2);
  delay(500);
  backLinefollowEncoder(100);
  backServoMove(0, 90); // tree pick up
  rightTurnEncoder(170, (220 * 2), 150);
  backLinefollowFiveEncoder(350);
  backLinefollowFiveUntil(1);
  delay(500);
  backLinefollowEncoder(100);
  backServoMove(90, 0); // tree drop
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(90, 0); // rock drop
  // =================== first tree and rock end ===================

  // =================== second tree and rock start ===================
  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  frontServo.write(90);
  delay(500);
  backLinefollowFiveEncoder(80);
  delay(500);
  linefollowFiveUntil(2);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  backServoMove(0, 90); // tree pick up
  frontServo.write(0);
  delay(500);
  linefollowFiveEncoder(200);
  frontServoMove(0, 90); // rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  backLinefollowFiveEncoder(420);
  backServoMove(90, 0); // tree drop
  delay(500);
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(90, 0); // rock drop
  // =================== second tree and rock end ===================

  // =================== third tree and rock start ===================
  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  linefollowFiveUntil(2);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  backServoMove(0, 90); // tree pick up
  frontServo.write(0);
  delay(500);
  linefollowFiveUntil(3);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  linefollowFiveEncoder(150);
  frontServoMove(0, 90); // rock pick up
  delay(200);
  rightTurnEncoder(170, (220 * 2), 150);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  backLinefollowFiveEncoder(420);
  backServoMove(90, 0); // tree drop
  delay(500);
  linefollowUntil(1);
  delay(500);
  leftTurnEncoder(80,240);
  linefollowFiveEncoder(80);
  linefollowFiveUntil(3);
  delay(500);
  linefollowFiveEncoder(80);
  frontServoMove(90, 0); // rock drop
  delay(500);
  // =================== third tree and rock end ===================

  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  backLinefollowFiveUntil(4);
  backLinefollowFiveEncoder(300);
}