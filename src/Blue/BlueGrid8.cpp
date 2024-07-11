#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid8.h"

/*
 * Grid 5 according to the Red Arena
 *
 *  grid is 3x3 the points are (1,1), (1,2) and (1,3)
 */

void blue_grid8()
{
  // ============== first tree and rock start ==============
  linefollowEncoder(80);
  linefollowUntil(5);
  delay(1000);
  left90(80);
  delay(1000);
  backLinefollowEncoder(80);
  frontServo.write(0); // front servo
  delay(1000);
  linefollowEncoder(150);
  delay(1000);
  frontServoMove(0, 90); // tree pick up
  linefollowUntil(1);
  delay(1000);
  left90(80);
  backServo.write(0); // back servo down for pick up
  delay(1000);
  backLinefollowEncoder(60);
  backLinefollowUntil(1);
  delay(200);
  backLinefollowEncoder(100);
  backServoMove(0, 90);                // rock pick up
  rightTurnEncoder(170, (220 * 2) ,150); // 180 turn
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
  delay(500);
  linefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowFiveEncoder(80);
  delay(500);
  linefollowFiveUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(150);
  backLinefollowFiveEncoder(280);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  rightTurnEncoder(170, (220 * 2) , 150);;
  // delay(500);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  // delay(500);
  backLinefollowEncoder(410);
  delay(500);
  backServoMove(90, 0); // rock drop
  // delay(500);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  // ============== second tree and rock end ==============

  // ============= third tree and rock =============
  // move back to intersection after rock drop
  backLinefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  delay(500);
  
  // turn right
  left90(80);
  delay(500);
  frontServo.write(0);

  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowFiveEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  // frontServo.write(95);
  delay(500);
  // move forward to tree
  linefollowFiveUntil(2);
  // linefollowFiveEncoder(250);
  delay(500);
  left90(80);
  delay(500);
  backLinefollowFiveEncoder(100);
  backServoMove(0,95);
  // move front servo up after tree pickup
  linefollowUntil(1);
  linefollowEncoder(100);
  frontServoMove(0, 90);
  // delay(500);
  // move forward to intersection
  rightTurnEncoder(170,(220 * 2), 150);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  backLinefollowEncoder(420);
  // turn right for rock
  backServoMove(95,0);
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90,0);
  backLinefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  /// waqas code
  frontServo.write(100);
  
  delay(500);
  linefollowEncoder(100);
  backLinefollowUntil(5);
  backLinefollowEncoder(300);
  delay(500);
}