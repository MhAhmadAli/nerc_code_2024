#include <Arduino.h>
#include "ServoControl.h"
#include "LineFollow.h"
#include "EncoderControl.h"
#include "Blue/BlueGrid9.h"

void blue_grid9()
{
 // move forward until 3 strips
  forwardWithEncoder(50, 80);
  linefollowUntil(3);
  delay(500);
  // turn left after 3 strips
  left90(80);
  delay(500);
  // move back to center on line
  backwardWithEncoder(50, 150);
  delay(500);
  // move servo down for pickup
  frontServo.write(0);
  delay(500);

  // ============= first tree and rock =============
  // move until first tree
  linefollowEncoder(280);
  // delay(500);
  // move servo up after pickup
  frontServoMove(0, 90);
  // delay(500);
  // move forward for 1 strip
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  left90(80);
  backServo.write(0);
  // backServoMove(95, 0);
  delay(500);
  // move back 3 strips
  backLinefollowFiveEncoder(80);
  backLinefollowFiveUntil(3);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(100);
  // delay(500);
  backServoMove(0, 90);
  // delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2) , 150);
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowUntil(1);
  delay(500);
  linefollowEncoder(410);
  // delay(500);
  // drop tree
  frontServoMove(90, 0);
  // delay(500);
  // move back 3 strip to drop rock at original tree position
  backLinefollowUntil(3);
  delay(500);
  backLinefollowEncoder(90);
  // delay(500);
  // drop rock
  backServoMove(90, 0);
  // delay(500);
  // ============= first tree and rock =============

  // ============= second tree and rock =============
  // move back to intersection after rock drop
  linefollowUntil(2);
  // delay(500);
  // move front servo up for the turn
  frontServo.write(95);
  delay(500);
  // turn right
  left90(80);
  delay(500);
  // move forward away from tree to adjust for line
  backLinefollowFiveEncoder(100);
  delay(500);
  // move front servo down for tree pickup
  frontServo.write(0);
  delay(500);
  // move forward to tree
  linefollowFiveEncoder(250);
  delay(500);
  // move front servo up after tree pickup
  frontServoMove(0, 90);
  delay(500);
  // move forward to intersection
  linefollowUntil(1);
  delay(500);
  // turn right for rock
  left90(80);
  delay(500);
  // move back 2 strips
  backLinefollowFiveEncoder(80);
  backLinefollowFiveUntil(1);
  delay(500);
  // move to pick up rock
  backLinefollowEncoder(100);
  delay(500);
  backServoMove(0, 90);
  delay(500);
  // turn 180 after rock pick up
  rightTurnEncoder(170, (220 * 2) , 150);
  // delay(500);
  // adjust to line for tree drop
  backLinefollowFiveEncoder(350);
  backLinefollowUntil(1);
  delay(500);
  linefollowEncoder(410);
  // delay(500);
  // drop tree
  frontServoMove(90, 0);
  delay(500);
  // move back 2 strip to drop rock at original tree position
  backLinefollowUntil(1);
  delay(500);
  backLinefollowEncoder(90);
  // delay(500);
  // drop rock
  backServoMove(90, 0);
  // delay(500);
  // ============= second tree and rock =============

  // ============= third tree and rock start ===========
  linefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  frontServo.write(90);
  delay(500);
  backLinefollowFiveEncoder(150);
  linefollowFiveUntil(2);
  delay(500);
  left90(80);
  delay(500);
  linefollowFiveEncoder(100);
  backLinefollowFiveEncoder(230);
  backServoMove(0, 90); // rock pickup
  frontServo.write(0);
  delay(500);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(100);
  frontServoMove(0, 90); // tree pickup
  rightTurnEncoder(170, (220 * 2) , 150);
  // delay(500);
  linefollowFiveEncoder(350);
  linefollowFiveUntil(1);
  delay(500);
  backLinefollowEncoder(410);
  // delay(500);
  backServoMove(90, 0); // rock drop
  // delay(500);
  linefollowUntil(3);
  delay(500);
  linefollowEncoder(90);
  frontServoMove(90, 0); // tree drop
  // ================ third tree and rock end =============

  backLinefollowUntil(1);
  delay(500);
  left90(80);
  delay(500);
  linefollowEncoder(75);
  delay(500);
  backLinefollowUntil(5);
  backLinefollowEncoder(200);
   

   
}