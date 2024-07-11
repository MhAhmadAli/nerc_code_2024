#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Red/RedGrid7.h"

/*
 * Grid 5 according to the Red Arena
 *
 *  grid is 3x3 the points are (1,1), (1,2) and (2,3)
 */

void red_grid7()
{
    // ============= first tree and rock start =============
  // move forward until 5 strips
  forwardWithEncoder(50, 80);
  linefollowFiveUntil(5);
  delay(1000);
  // turn left after 5 strips
  right90(80);
  delay(1000);
  // move back to center on line
  backwardWithEncoder(50, 110);
  delay(1000);
  // move servo down for pickup
  frontServo.write(0);
  delay(1000);
  // move until first tree
  linefollowEncoder(440);
  delay(1000);
  // move servo up after pickup
  frontServoMove(0, 90); // rock pickup
  delay(1000);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(1000);
  // turn left for rock
//   leftTurnEncoder(80, 240);
    backLinefollowEncoder(220);
  backServo.write(0);
  delay(1000);
  // move back 1 strips
  backwardWithEncoder(50, 80);
  backLinefollowUntil(1);
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
  backLinefollowFiveUntil(1);
  delay(500);
  linefollowEncoder(400);
  delay(1000);
  // drop tree
  frontServoMove(90, 0); // rock drop
  delay(1000);
  // move back 1 strip to drop rock at original tree position
  backLinefollowUntil(2);
  delay(1000);
  right90(80);
  backLinefollowEncoder(90);
  delay(1000);
  // drop rock
  backServoMove(90, 0); // tree drop
  delay(1000);
  // ============= first tree and rock end =============

}