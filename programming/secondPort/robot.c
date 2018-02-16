#include "defs.h"
// Returns TRUE if robot current position is identical to map finish position
int robot_finished() {
  // Compares robot current position with map finish position
  if(robot.pos.x == robot.map.finish.x &&
    robot.pos.y == robot.map.finish.y) {
    return TRUE;
  }
  return FALSE;
}

void robot_init() {
  // First queue and stack element must be initialized to NULL
  robot.unchecked = NULL;
  robot.checked = NULL;
  robot.movement = NULL;
  robot.pos.x = 0;
  robot.pos.y = 0;
  robot.map.start.x = 0;
  robot.map.start.y = 0;

  //TODO give values to everything, even if they are only 0   --Daniel
}