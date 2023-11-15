#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront(PORT1, gearSetting::ratio6_1, true);
motor leftMiddle(PORT2, gearSetting::ratio6_1, true);
motor leftBack(PORT3, gearSetting::ratio18_1, true);

motor rightFront(PORT10, gearSetting::ratio6_1, false);
motor rightMiddle(PORT9, gearSetting::ratio6_1, false);
motor rightBack(PORT8, gearSetting::ratio18_1, false);

motor_group leftDrive(leftFront, leftMiddle, leftBack);
motor_group rightDrive(rightFront, rightMiddle, rightBack);

controller Controller1(primary);

motor Lift(PORT20, gearSetting::ratio36_1, false);
motor Puncher(PORT11, gearSetting::ratio36_1, false);
inertial Inertial(PORT6);

motor Intake(PORT12, gearSetting::ratio6_1, false);

void ArcadeControl(int forward, int turn, int deadzone){
  int left = forward + turn;
  int right = forward - turn;
  if (abs(left) < deadzone) {
    left = 0;
  }
  if (abs(right) < deadzone) {
    right = 0;
  }
  
  leftDrive.spin(directionType::fwd, left, velocityUnits::pct);
  rightDrive.spin(directionType::fwd, right, velocityUnits::pct);

}

triport ThreeWirePort(PORT7);

digital_out Wing(ThreeWirePort.A);
digital_out Foot(ThreeWirePort.B);


// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}