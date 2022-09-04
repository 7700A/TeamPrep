#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor F1 = motor(PORT2, ratio6_1, false);
motor F2 = motor(PORT5, ratio6_1, true);
digital_out Injector = digital_out(Brain.ThreeWirePort.A);
motor LF = motor(PORT21, ratio18_1, false);
motor LB = motor(PORT12, ratio18_1, false);
motor RF = motor(PORT20, ratio18_1, false);
motor RB = motor(PORT4, ratio18_1, false);
motor Intake1 = motor(PORT1, ratio18_1, false);
motor turret = motor(PORT10, ratio18_1, false);
inertial gyro1 = inertial(PORT14);
rotation RotationL = rotation(PORT9, false);
rotation RotationB = rotation(PORT3, false);
inertial turretG = inertial(PORT13);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}