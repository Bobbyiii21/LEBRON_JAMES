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
    printf("Lift: %f\n", Lift.torque(torqueUnits::Nm));
    printf("Intake: %f\n", intakeDistance.objectDistance(distanceUnits::mm));
    task::sleep(500);
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

// void intakeIn(){
//     while (1)
//     {
//       Intake.spin(directionType::rev, 400, velocityUnits::rpm);
//       if (intakeDistance.objectDistance(distanceUnits::mm) < 30)
//       {
//         Intake.setBrake(brakeType::brake);
//         Intake.stop();
//         // task::sleep(5000);
//         break;
//       }
//       task::sleep(20);
//     }
bool quitEvent_b = false;
void quitEvent()
{
  quitEvent_b = true;
}

void intakeIn()
{
  if (quitEvent_b == true)
  {
    quitEvent_b = false;
  }
  while (1)
  {
    while (intakeDistance.objectDistance(distanceUnits::mm) > 2)
    {
      Intake.spin(directionType::rev, 400, velocityUnits::rpm);
      vex::task::sleep(10);

      if (quitEvent_b == true)
      {
        break;
      }
    }

    Intake.setBrake(brakeType::hold);
    Intake.stop();
    if (quitEvent_b == true)
    {
      break;
    }
    vex::task::sleep(10);
  }
}
void intakeOut()
{
  if (quitEvent_b == true)
  {
    quitEvent_b = false;
  }
  while (1)
  {
    while (intakeDistance.objectDistance(distanceUnits::mm) < 15)
    {
      Intake.spin(directionType::fwd, 400, velocityUnits::rpm);
      vex::task::sleep(10);

      if (quitEvent_b == true)
      {
        break;
      }
    }
    Intake.setBrake(brakeType::brake);
    Intake.stop();
    if (quitEvent_b == true)
    {
      break;
    }
    vex::task::sleep(10);
  }
}

event intakeInEvent = event(intakeIn);
event intakeOutEvent = event(intakeOut);

void intakeControl(std::string value){
  if(value == "in"){
    while (1)
    {
      Intake.spin(directionType::rev, 400, velocityUnits::rpm);
      if (intakeDistance.objectDistance(distanceUnits::mm) < 30)
      {
        Intake.setBrake(brakeType::brake);
        Intake.stop();
        break;
      }
      vex::task::sleep(10);
    }
  }else if(value == "out"){
    while (1)
    {
      Intake.spin(directionType::fwd, 400, velocityUnits::rpm);
      if (intakeDistance.objectDistance(distanceUnits::mm) < 30)
      {
        Intake.setBrake(brakeType::brake);
        Intake.stop();
        break;
      }
      vex::task::sleep(10);
    }
  }
}

void spinChassisMAX(int time)
{
  rightDrive.spin(directionType::fwd, 12, voltageUnits::volt);
  leftDrive.spin(directionType::fwd, 12, voltageUnits::volt);
  wait(time, timeUnits::msec);
  rightDrive.stop();
  leftDrive.stop();
}
void spinChassisReverseMAX(int time)
{
  rightDrive.spin(directionType::rev, 12, voltageUnits::volt);
  leftDrive.spin(directionType::rev, 12, voltageUnits::volt);
  wait(time, timeUnits::msec);
  rightDrive.stop();
  leftDrive.stop();
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  rear_jack.set(true);
  // nothing to initialize
}