#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid5.h"

/*
 * Grid 5 according to the Red Arena
 *
 *  grid is 3x3 the points are (3,1), (2,1) and (3,3)
 */

void red_grid5()
{
  // ============= first tree and rock start =============
  // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(1000);
  // turn right after 3 strips
  right90(80);
  delay(1000);
  // move back to center on line
  backwardWithEncoder(50, 110);
  delay(1000);
  // move servo down for pickup
  frontServo.write(0);
  delay(1000);
  // move until first tree
  linefollowEncoder(200);
  delay(1000);
  // move servo up after pickup
  frontServoMove(0, 90); // rock pickup
  delay(1000);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(1000);
  // turn right for rock
  right90(80);
  backServo.write(0);
  delay(1000);
  // move back 3 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(3);
  delay(1000);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(1000);
  backServoMove(0, 90); // tree pickup
  delay(1000);
  // turn 180 after rock pick up
  rightTurnEncoder(60, (240 * 2) + 10);
  delay(1000);
  // adjust to line for tree drop
  backLinefollowFiveUntil(2);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0); // rock drop
  delay(1000);
  // move back 3 strip to drop rock at original tree position
  backLinefollowUntil(3);
  delay(1000);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0); // tree drop
  delay(1000);
  // ============= first tree and rock end =============
  
  // ============= second tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(1);
  delay(500);
  // move front servo up for the turn
  frontServo.write(95);
  delay(500);
  // turn right
  right90(80);
  delay(1000);
  // move forward away from tree to adjust for line
  backLinefollowEncoder(100);
  delay(1000);
  // move front servo down for tree pickup
  frontServo.write(0);
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
  linefollowEncoder(420);
  delay(1000);
  // drop tree
  frontServoMove(90, 0);
  delay(1000);
  // move back 2 strip to drop rock at original tree position
  backLinefollowUntil(2);
  delay(1000);
  backLinefollowEncoder(80);
  delay(1000);
  // drop rock
  backServoMove(90, 0);
  delay(1000);
// ============= second tree and rock =============

// ============== third tree and rock start ==============
  linefollowUntil(1);
  delay(1000);
  right90(80);
  delay(1000);
  backLinefollowEncoder(100);
  linefollowUntil(2);
  delay(1000);
  right90(80);
  delay(1000);
  backLinefollowEncoder(150);
  linefollowUntil(2);
  linefollowEncoder(100);
  frontServoMove(0, 90); // rock pickup
  delay(1000);
  backLinefollowUntil(3);
  delay(1000);

  backLinefollowEncoder(100);
  backServoMove(0, 90); // tree pickup
  rightTurnEncoder(80, (240 * 2) + 10);
  delay(1000);
  backLinefollowFiveUntil(2);
  delay(1000);
  linefollowEncoder(400);
  delay(1000);
  frontServoMove(90, 0); // rock drop
  delay(1000);
  backLinefollowUntil(3);
  delay(1000);
  backLinefollowEncoder(90);
  backServoMove(90, 0); // tree drop
  // ============== third tree and rock end ==============

  linefollowUntil(3);
  delay(1000);
  right90(80);
  delay(1000);
  linefollowEncoder(80);
  delay(1000);
  backLinefollowUntil(5);
  backLinefollowEncoder(270);

}