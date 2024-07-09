#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/ForwardDiagonal.h"

void forwardDiagonal() {
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
}
