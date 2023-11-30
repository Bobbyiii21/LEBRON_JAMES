#include "vex.h"
#include <string>

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor leftFront(PORT1, gearSetting::ratio6_1, true);
motor leftMiddle(PORT2, gearSetting::ratio6_1, true);
motor leftBack(PORT3, gearSetting::ratio18_1, true);

motor rightFront(PORT10, gearSetting::ratio6_1, false);
motor rightMiddle(PORT9, gearSetting::ratio6_1, false);
motor rightBack(PORT8, gearSetting::ratio18_1, false);

motor_group driveMotor(leftFront, leftMiddle, leftBack, rightFront, rightMiddle, rightBack);

motor_group leftDrive(leftFront, leftMiddle, leftBack);
motor_group rightDrive(rightFront, rightMiddle, rightBack);

controller Controller1(primary);

motor Lift(PORT20, gearSetting::ratio36_1, false);
motor Puncher(PORT11, gearSetting::ratio36_1, false);
inertial Inertial(PORT6);

motor Intake(PORT12, gearSetting::ratio6_1, false);
distance intakeDistance(PORT13);

void ArcadeControl(int forward, int turn, int deadzone)
{
  int left = forward + turn;
  int right = forward - turn;
  if (abs(left) < deadzone)
  {
    left = 0;
  }
  if (abs(right) < deadzone)
  {
    right = 0;
  }

  leftDrive.spin(directionType::fwd, left, velocityUnits::pct);
  rightDrive.spin(directionType::fwd, right, velocityUnits::pct);
}

triport ThreeWirePort = triport(PORT7);

digital_out left_wing(Brain.ThreeWirePort.C);
digital_out right_wing(Brain.ThreeWirePort.A);
digital_out rear_jack(Brain.ThreeWirePort.B);
digital_out liftLocker(ThreeWirePort.D);
digital_out hanger(ThreeWirePort.E);

// Pneumatic Variable Setup
bool WingLState = false;
bool WingRState = false;
bool FootState = false;
// X both
void X_CallBack()
{
  WingLState = !WingLState;
  WingRState = WingLState;
  left_wing.set(WingLState);
  right_wing.set(WingRState);
}
// Y left
void Y_CallBack()
{
  WingLState = !WingLState;
  left_wing.set(WingLState);
}
// A right
void A_CallBack()
{
  WingRState = !WingRState;
  right_wing.set(WingRState);
}
// B rear_jack
void B_CallBack()
{
  FootState = !FootState;
  rear_jack.set(FootState);
}

void wingValve(bool state)
{
  left_wing.set(state);
  right_wing.set(state);
}

void phoneHome()
{
  while (true)
  {
    printf("X: %f    Y: %f   Theta: %f\n", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
    task::sleep(1000);
  }
}
vex::event telemetry(phoneHome);

void LiftToggle(std::string state)
{
  if (state == "up")
  {
    Lift.spin(directionType::fwd, 100, velocityUnits::pct);
    Lift.setBrake(brakeType::brake);
  }
  else if (state == "down")
  {
    Lift.spin(directionType::rev, 100, velocityUnits::pct);
    Lift.setBrake(brakeType::coast);
    liftLocker.set(false);
  }
  while (true)
  {
    if ((Lift.torque(torqueUnits::Nm) > 1.5) && (state == "down"))
    {
      Lift.stop();
      break;
    }
    else if (Lift.torque(torqueUnits::Nm) > 2.1 && (state == "up"))
    {
      Lift.stop();
      liftLocker.set(true);
      break;
    }
  }
}

void intakeUntilObject()
{
  while (true)
  {
    Intake.spin(directionType::fwd, 400, velocityUnits::rpm);
    if (intakeDistance.objectDistance(distanceUnits::mm) < 10)
    {
      Intake.spin(directionType::fwd, 0, velocityUnits::rpm);
      // task::sleep(5000);
      break;
    }
    task::sleep(20);
  }
}

void intakeFunctions(void* arg) {
  if (arg == "in")
    while (1)
    {
      Intake.spin(directionType::fwd, 400, velocityUnits::rpm);
      if (intakeDistance.objectDistance(distanceUnits::mm) < 10)
      {
        Intake.spin(directionType::fwd, 0, velocityUnits::rpm);
        // task::sleep(5000);
        break;
      }
      task::sleep(20);
    }
  if (arg == "out")
    while (1)
    {
      Intake.spin(directionType::rev, 400, velocityUnits::rpm);
      if (intakeDistance.objectDistance(distanceUnits::mm) > 10)
      {
        Intake.spin(directionType::fwd, 0, velocityUnits::rpm);
        // task::sleep(5000);
        break;
      }
      task::sleep(20);
    }
}
    
  std::string in = "in";
  std::string out = "out";
  event intakeInEvent = event(intakeFunctions, &in);
  event intakeOutEvent = event(intakeFunctions, &out);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}