#include "vex.h"
#include <string>

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

digital_out WingL(ThreeWirePort.A);
digital_out WingR(ThreeWirePort.C);
digital_out Foot(ThreeWirePort.B);

//Pneumatic Variable Setup
bool WingLState = false;
bool WingRState = false;
bool FootState = false;
//X both
void x_CallBack(){
  WingLState = !WingLState;
  WingRState = WingLState;
  WingL.set(WingLState);
  WingR.set(WingRState);
}
//Y left
void y_CallBack(){
  WingLState = !WingLState;
  WingL.set(WingLState);
}
//A right
void a_CallBack(){
  WingRState = !WingRState;
  WingR.set(WingRState);
}
//B Foot
void b_CallBack(){
  FootState = !FootState;
  Foot.set(FootState);
}

void LiftToggle(std::string state){
  while(true){
    if (state == "up"){
      Lift.spin(directionType::fwd, 100, velocityUnits::pct);
      Lift.setBrake(brakeType::brake);
    }else if (state == "down"){
      Lift.spin(directionType::rev, 100, velocityUnits::pct);
      Lift.setBrake(brakeType::coast);
    }

    if (Lift.torque(torqueUnits::Nm) > 1.5){
      Lift.stop();
      break;
    }
  }
}


/** 
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}