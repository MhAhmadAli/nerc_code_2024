#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid6.h"

/*
 * Grid 5 according to the Red Arena
 *
 *  grid is 3x3 the points are (1,1), (1,2) and (2,3)
 */

void red_grid6()
{
    // ============= first tree and rock start =============
  // move forward until 4 strips
  forwardWithEncoder(50, 80);
  linefollowFiveUntil(4);
  delay(500);
  // turn right after 4 strips
  right90(80);
  delay(500);
  // move back to center on line
  backwardWithEncoder(50, 110);
  delay(500);
  // move servo down for pickup
  frontServo.write(0);
  delay(500);
  // move until first tree
  linefollowEncoder(200);
  delay(500);
  // move servo up after pickup
  frontServo.write(90); // rock pickup
  delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  right90(80);
  backServo.write(0);
  delay(500);
  // move back 2 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(2);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(500);
  backServoMove(0, 90); // tree pickup
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2) , 150);
  // adjust to line for tree drop
  backLinefollowFiveUntil(2);
  delay(500);
  linefollowEncoder(420);
  delay(500);
  // drop tree
  frontServoMove(90, 0); // rock drop
  delay(500);
  // move back 2 strip to drop rock at original tree position
  backLinefollowUntil(2);
  delay(500);
  backLinefollowEncoder(90);
  delay(500);
  // drop rock
  backServoMove(90, 0); // tree drop
  delay(500);
  // ============= first tree and rock end =============

  // ============= second tree and rock start =============
  frontServo.write(90);
  delay(500);
  linefollowUntil(2);
  delay(500);
  right90(80);
  delay(500);
  backLinefollowEncoder(150);
  linefollowUntil(2);
  delay(500);
  right90(80);
  delay(500);
  linefollowEncoder(100);
  backLinefollowEncoder(230);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  rightTurnEncoder(170, (220 * 2) , 150);
  // delay(500);
  linefollowFiveUntil(2);
  delay(500);
  backLinefollowEncoder(420);
  delay(500);
  backServoMove(90, 0); // rock drop
  delay(500);
  linefollowUntil(1);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  delay(500);
  // ============= second tree and rock end =============

  // ============= third tree and rock start ===========
  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  frontServo.write(90);
  delay(500);
  backLinefollowEncoder(150);
  linefollowUntil(2);
  delay(500);
  right90(80);
  delay(500);
  linefollowEncoder(100);
  backLinefollowEncoder(230);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  rightTurnEncoder(170, (220 * 2), + 150);
  delay(500);
  linefollowFiveUntil(2);
  delay(500);
  backLinefollowEncoder(420);
  delay(500);
  backServoMove(90, 0); // rock drop
  delay(500);
  linefollowUntil(2);
  delay(500);
  linefollowEncoder(80);
  frontServoMove(90, 0); // tree drop
  // ================ third tree and rock end =============

  backLinefollowUntil(1);
  delay(500);
  right90(80);
  delay(500);
  linefollowEncoder(75);
  delay(500);
  backLinefollowUntil(5);
  backLinefollowEncoder(200);

}