#include <Arduino.h>
#include "ServoControl.h"

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
