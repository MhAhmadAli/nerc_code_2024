#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid10.h"

/*
 * Grid 10
 *
 *  grid is 3x3 the points are (1,2), (2,2) and (2,1)
 */

void blue_grid10() {
  // =================== first tree and rock start ===================
  linefollowFiveEncoder(80);
  linefollowFiveUntil(4);
  delay(500);
  leftTurnEncoder(80, 240);
  delay(500);
  frontServo.write(0);
  backLinefollowFiveEncoder(100);
  linefollowFiveUntil(2);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // rock pick up
  backLinefollowUntil(1);
  delay(500);
  leftTurnEncoder(80, 240);
  backServo.write(0);
  delay(500);
  backLinefollowFiveEncoder(80);
  backLinefollowFiveUntil(2);
  delay(500);
  backLinefollowEncoder(100);
  backServoMove(0, 90); // tree pick up
  rightTurnEncoder(170, (220 * 2), 150);
  backLinefollowFiveEncoder(450);
  backLinefollowFiveUntil(1);
  delay(500);
  linefollowFiveEncoder(420);
  frontServoMove(90, 0); // rock drop
  backLinefollowUntil(3);
  delay(500);
  right90(80);
  delay(500);
  linefollowFiveEncoder(110);
  backLinefollowFiveEncoder(260);
  backServoMove(90, 0); // tree drop
  // =================== first tree and rock end ===================

  // =================== second tree and rock start ===================
  frontServo.write(95);
  delay(500);
  linefollowUntil(1);
  delay(500);
  leftTurnEncoder(80, 240);
  delay(500);
  backLinefollowFiveEncoder(100);
  linefollowFiveUntil(3);
  delay(500);
  leftTurnEncoder(80, 240);
  delay(500);
  backLinefollowFiveEncoder(80);
  linefollowFiveUntil(2);
  delay(500);
  leftTurnEncoder(80, 240);
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
  backLinefollowFiveEncoder(405);
  backServoMove(90, 0); // tree drop
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(90, 0); // rock drop
  // =================== second tree and rock end ===================

  // =================== third tree and rock start ===================
  backLinefollowUntil(1);
  delay(500);
  leftTurnEncoder(80, 240);
  delay(500);
  backLinefollowFiveEncoder(100);
  linefollowFiveUntil(2);
  delay(500);
  leftTurnEncoder(80, 240);
  delay(500);
  backLinefollowFiveEncoder(80);
  backServoMove(0, 90); // tree pick up
  frontServo.write(0);
  delay(500);
  linefollowFiveUntil(2);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(0, 90); // rock pick up
  rightTurnEncoder(170, (220 * 2), 150);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  backLinefollowFiveEncoder(410);
  backServoMove(90, 0); // tree drop
  delay(500);
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(85);
  frontServoMove(90, 0); // rock drop
  delay(500);
  // =================== third tree and rock end ===================

  backLinefollowFiveUntil(1);
  delay(500);
  leftTurnEncoder(80, 240);
  delay(500);
  backLinefollowFiveEncoder(100);
  backLinefollowFiveUntil(4);
  backLinefollowFiveEncoder(300);

}