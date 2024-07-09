#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid2.h"

/*
 * Grid 2
 *
 *  grid is 3x3 the points are (1,1), (2,2) and (3,3)
 */

void red_grid2()
{
  // ============== first tree and rock start ==============
  linefollowEncoder(80);
  linefollowUntil(5);
  delay(1000);
  right90(80);
  delay(1000);
  backLinefollowEncoder(80);
  frontServo.write(0); // front servo
  delay(1000);
  linefollowEncoder(150);
  delay(1000);
  frontServoMove(0, 90); // tree pick up
  linefollowUntil(1);
  delay(1000);
  right90(80);
  backServo.write(0); // back servo down for pick up
  delay(1000);
  backLinefollowEncoder(60);
  backLinefollowUntil(1);
  delay(200);
  backLinefollowEncoder(100);
  backServoMove(0, 90);                // rock pick up
  rightTurnEncoder(80, (240 * 2) + 5); // 180 turn
  delay(1000);
  backLinefollowUntil(2);
  delay(1000);
  linefollowEncoder(410);
  delay(1000);
  frontServoMove(90, 0); // rock drop
  backLinefollowUntil(1);
  delay(1000);
  backLinefollowEncoder(80);
  backServoMove(90, 0); // tree drop
  delay(1000);
  // ============== first tree and rock end ==============

  // ============== second tree and rock start ==============
  frontServo.write(90);
  delay(1000);
  linefollowUntil(1);
  delay(1000);
  right90(80);
  delay(1000);
  backLinefollowEncoder(80);
  delay(1000);
  linefollowUntil(2);
  delay(1000);
  right90(80);
  delay(1000);
  linefollowEncoder(150);
  backLinefollowEncoder(280);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(1000);
  linefollowUntil(2);
  delay(1000);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  rightTurnEncoder(80, (240 * 2) + 5);
  delay(1000);
  linefollowUntil(2);
  delay(1000);
  backLinefollowEncoder(410);
  delay(1000);
  backServoMove(90, 0); // rock drop
  delay(1000);
  linefollowUntil(2);
  delay(1000);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  // ============== second tree and rock end ==============

  // ============== third tree and rock start ==============
  backLinefollowUntil(1);
  delay(1000);
  right90(80);
  delay(1000);
  backLinefollowEncoder(80);
  linefollowUntil(2);
  delay(1000);
  right90(80);
  delay(1000);
  linefollowEncoder(150);
  backLinefollowEncoder(280);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(1000);
  linefollowUntil(3);
  delay(1000);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  rightTurnEncoder(80, (240 * 2) + 10);
  delay(1000);
  linefollowUntil(3);
  delay(1000);
  backLinefollowEncoder(700);
  delay(1000);
  backServoMove(90, 0); // rock drop
  delay(1000);
  linefollowUntil(3);
  delay(1000);
  linefollowEncoder(90);
  frontServoMove(90, 0); // tree drop
  // ============== third tree and rock end ==============

  backLinefollowUntil(1);
  delay(1000);
  right90(80);
  delay(1000);
  linefollowEncoder(80);
  delay(1000);
  backLinefollowUntil(5);
  backLinefollowEncoder(200);
}